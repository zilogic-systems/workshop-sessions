/* ### START: all */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

static int major;

/* ### START: read */
static ssize_t y_read(struct file *file, char __user * buf,
		      size_t count, loff_t * ppos)
{
	size_t i;

	if (count == 1)
		return -EINVAL;
	if (count % 2 != 0)
		count--;
	for (i = 0; i < count; i += 2) {
		if (put_user('y', buf + i))
			return -EFAULT;
		if (put_user('\n', buf + i + 1))
			return -EFAULT;
	}
	return count;
}
/* ### END: read */

/* ### START: fops */
static const struct file_operations y_fops = {
	.owner         = THIS_MODULE,
	.read          = y_read
};
/* ### END: fops */

/* ### START: init */
static int y_init(void)
{
	major = register_chrdev(0, "y", &y_fops);
	if (major < 0) {
		printk(KERN_ERR "y: error adding char driver\n");
		return major;
	}
	
	return 0;
}
/* ### END: init */

/* ### START: exit */
static void y_exit(void)
{
	unregister_chrdev(major, "y");
}
/* ### END: exit */

module_init(y_init);
module_exit(y_exit);
MODULE_LICENSE("GPL");
/* ### END: all */
