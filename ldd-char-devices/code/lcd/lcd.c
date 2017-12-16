#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/i2c.h>

#include <asm/uaccess.h>

static int major;
static struct i2c_client * client;

static ssize_t lcd_write(struct file * file, const char __user * buf,
			 size_t len, loff_t *ppos)
{
	size_t i;

	for (i = 0; i < len; i++) {
		char ch;
		char msg[2];
		int ret;

		if (get_user(ch, buf + i))
			return -EFAULT;
		
		msg[0] = 0x0;      /* Register Address: 0x0 */
		msg[1] = ch;       /* Register Data: ch */

		ret = i2c_master_send(client, msg, sizeof(msg));
		if (ret != sizeof(msg)) {
			printk("lcd: error sending data");
			return -EIO;
		}
	}

	return len;
}

static const struct file_operations lcd_fops = {
	.owner         = THIS_MODULE,
	.write         = lcd_write
};

static int lcd_init(void)
{
	int ret;
	struct i2c_adapter * adapter;
	struct i2c_board_info board_info = { .type = "lcd", .addr = 0x40 };

	adapter = i2c_get_adapter(0);
	if (adapter == NULL) {
		printk("lcd: error getting adapter");
		ret = -ENODEV;
		goto out;
	}

	client = i2c_new_device(adapter, &board_info);
	if (client == NULL) {
		printk("lcd: error creating client");
		ret = -EBUSY;
		goto out;
	}

	ret = register_chrdev(0, "lcd", &lcd_fops);
	if (ret < 0) {
		printk("lcd: error registering char. device");
		goto out_free_device;
	}

	major = ret;

	return 0;

out_free_device:
	i2c_unregister_device(client);

out:
	return ret;
}

static void lcd_exit(void)
{
	unregister_chrdev(major, "lcd");
	i2c_unregister_device(client);
}

module_init(lcd_init);
module_exit(lcd_exit);
MODULE_LICENSE("GPL");
