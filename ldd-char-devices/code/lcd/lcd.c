#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#include <asm/uaccess.h>

static ssize_t lcd_write(struct file * file, const char __user * buf,
			  size_t len, loff_t *ppos)
{
	/* Your I2C LCD Write Code Here */
}

static const struct file_operations lcd_fops = {
	.owner         = THIS_MODULE,
	.write         = lcd_write
};

static int lcd_init(void)
{
        /* Your I2C LCD Init Code Here */

	major = register_chrdev(0, "lcd", &lcd_fops);
	if (major < 0)
		return major;

	return 0;
}

static void lcd_exit(void)
{
        /* Your I2C LCD Exit Code Here */

	unregister_chrdev(major, "lcd");
}

module_init(lcd_init);
module_exit(lcd_exit);
MODULE_LICENSE("GPL");
