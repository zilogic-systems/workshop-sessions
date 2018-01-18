/* ### START: ikey-mutex.full */
/* ### START: ikey-mutex.def */
#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/fs.h>
#include <linux/i2c.h>
#include <linux/wait.h>
#include <linux/kfifo.h>
#include <linux/gpio.h>
#include <asm/uaccess.h>

#define REG_STAT_ADDR  0x0
#define REG_DATA_ADDR  0x1

static void ikey_bh(struct work_struct *work);

static struct i2c_client * client;
static int major;
static DEFINE_KFIFO(ikey_fifo, char, 256);
static DECLARE_WORK(ikey_work, ikey_bh);
static DECLARE_WAIT_QUEUE_HEAD(ikey_wq);

DEFINE_MUTEX(kf_lock);
/* ### END: ikey-mutex.def */
#define INT_GPIO 66

static void ikey_reg_read(char addr, char *data)
{
	i2c_master_send(client, &addr, 1);
	i2c_master_recv(client, data, 1);
}

static bool ikey_get(char * ikey)
{
	char key_avail;

	ikey_reg_read(REG_STAT_ADDR, &key_avail);
	if (!key_avail)
		return false;

	ikey_reg_read(REG_DATA_ADDR, ikey);
	return true;
}

/* ### START: ikey-mutex.handler */
static irqreturn_t ikey_handler(int irq, void * dev)
{
	schedule_work(&ikey_work);
	return IRQ_HANDLED;
}
/* ### END: ikey-mutex.handler */

/* ### START: ikey-mutex.bh */
static void ikey_bh(struct work_struct *work)
{
	int lk_sts = 0;
	bool data_available = false;
	while (1) {
		bool ret;
		char key;

		ret = ikey_get(&key);
		if (ret == false)
			break;

		lk_sts = mutex_lock_interruptible(&kf_lock);
		kfifo_put(&ikey_fifo, key);
		mutex_unlock(&kf_lock);
		data_available = true;
		
	}
	if (data_available)
		wake_up(&ikey_wq);
}
/* ### END: ikey-mutex.bh */

/* ### START: ikey-mutex.read */
static ssize_t ikey_read(struct file *file, char __user * buf,
			size_t count, loff_t * ppos)
{
	int i;
	int ret;

	ret = wait_event_interruptible(ikey_wq, !kfifo_is_empty(&ikey_fifo));
	if (ret != 0)
		return -ERESTARTSYS;

	mutex_lock(&kf_lock);
	for (i = 0; i < count; i++) {
		char ikey;
		if (kfifo_get(&ikey_fifo, &ikey) == 0)
			break;
		if (put_user(ikey + '0', buf + i))
			return -EFAULT;
	}
	mutex_unlock(&kf_lock);
	return i;
}

/* ### END: ikey-mutex.read */
static const struct file_operations ikey_fops = {
	.owner          = THIS_MODULE,
	.read           = ikey_read
};


/* ### START: ikey-mutex.init */
static int ikey_init(void)
{
	struct i2c_adapter * adapter;
	struct i2c_board_info board_info = { .type = "ikey", .addr = 0x20 };
	int irq;
	int err = 0;

	adapter = i2c_get_adapter(0);
	if (adapter == NULL) {
		printk("ikey: error getting adapter");
		err = -ENODEV;
		goto err_exit;
	}

	client = i2c_new_device(adapter, &board_info);
	if (client == NULL) {
		printk("ikey: error creating client");
		err = -ENODEV;
		goto err_exit;
	}
	
	err = gpio_request(INT_GPIO, "ikey-irq");
	if (err) {
		printk("ikey: error requesting irq gpio");
		goto err_free_client;
	}
	

	gpio_direction_input(INT_GPIO);

	irq = gpio_to_irq(INT_GPIO);
	err = request_irq(irq, ikey_handler, IRQF_TRIGGER_RISING, "ikey", 0);
	if (err) {
		printk("ikey: error requesting IRQ");
		goto err_free_gpio;
	}

	major = register_chrdev(0, "ikey", &ikey_fops);
	if (major < 0) {
		printk("ikey: could not register char. device\n");
		err = major;
		goto err_free_irq;
	}
	
	return 0;

err_free_irq:
	free_irq(irq, "ikey");

err_free_gpio:
	gpio_free(INT_GPIO);

err_free_client:
	i2c_unregister_device(client);

err_exit:
	return err;
}

/* ### END: ikey-mutex.init */

/* ### START: ikey-mutex.exit */
static void ikey_exit(void)
{
	int irq;

	unregister_chrdev(major, "ikey");
	irq = gpio_to_irq(INT_GPIO);
	free_irq(irq, 0);
	gpio_free(INT_GPIO);
	i2c_unregister_device(client);
}

module_init(ikey_init);
module_exit(ikey_exit);
MODULE_LICENSE("GPL");
/* ### END: ikey-mutex.exit */
/* ### END: ikey-mutex.full*/
