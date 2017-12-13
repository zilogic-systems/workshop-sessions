/* ### START: all */
#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/fs.h>
#include <linux/i2c.h>
#include <linux/wait.h>
#include <linux/kfifo.h>
#include <asm/uaccess.h>

#define REG_STAT_ADDR  0x0
#define REG_DATA_ADDR  0x1

static struct i2c_client * client;
static int major;

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

/* ### START: read */
static ssize_t ikey_read(struct file *file, char __user * buf,
			size_t count, loff_t * ppos)
{
	int i;

	for (i = 0; i < count; i++) {
		char ikey;

		if (ikey_get(&ikey) == false)
			break;
		if (put_user(ikey + '0', buf + i))
			return -EFAULT;
	}

	if (i == 0)
		return -EAGAIN;

	return i;
}
/* ### END: read */

static const struct file_operations ikey_fops = {
	.owner          = THIS_MODULE,
	.read           = ikey_read
};

static int ikey_init(void)
{
	struct i2c_adapter * adapter;
	struct i2c_board_info board_info = { .type = "ikey", .addr = 0x54 };
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

	major = register_chrdev(0, "ikey", &ikey_fops);
	if (major < 0) {
		printk("ikey: could not register char. device\n");
		err = major;
		goto err_free_client;
	}
	
	return 0;

err_free_client:
	i2c_unregister_device(client);

err_exit:
	return err;
}

static void ikey_exit(void)
{
	unregister_chrdev(major, "ikey");
	i2c_unregister_device(client);
}

module_init(ikey_init);
module_exit(ikey_exit);
MODULE_LICENSE("GPL");
/* ### END: all */
