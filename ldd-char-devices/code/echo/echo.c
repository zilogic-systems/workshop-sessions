/* ### START: all */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/kfifo.h>

#include <asm/uaccess.h>

#define DRV_NAME "echo"
#define BUF_SIZE 256

/* ### START: global */
DEFINE_KFIFO(echo_fifo, char, 16);
static int major;
/* ### END: global */

/* ### START: open */
static int echo_open(struct inode * inode, struct file * filp)
{
	if ((filp->f_flags & O_ACCMODE) == O_WRONLY) {
		if (!(filp->f_flags & O_APPEND)) {
			kfifo_reset(&echo_fifo);
		}
	}

	return 0;
}
/* ### END: open */

/* ### START: write */
static ssize_t echo_write(struct file * file, const char __user * buf,
			  size_t len, loff_t *ppos)
{
	size_t i;
	for (i = 0; i < len; i++) {
		char ch;
		if (get_user(ch, buf + i))
			return -EFAULT;
		ch = tolower(ch);
		if (kfifo_put(&echo_fifo, &ch) != 1)
			break;
	}

	return i;
}
/* ### END: write */

/* ### START: read */
static ssize_t echo_read(struct file *file, char __user * buf,
			 size_t len, loff_t * ppos)
{
	size_t i;
	for (i = 0; i < len; i++) {
		char ch;
		if (kfifo_get(&echo_fifo, &ch) != 1)
			break;
		if (put_user(ch, buf + i))
			return -EFAULT;
	}

	if (i == 0)
		return -EAGAIN;

	return i;
}
/* ### END: read */

/* ### START: fops */
static const struct file_operations echo_fops = {
	.owner         = THIS_MODULE,
	.open          = echo_open,
	.read          = echo_read,
	.write         = echo_write
};
/* ### END: fops */

/* ### START: init */
static int echo_init(void)
{
	major = register_chrdev(0, "echo", &echo_fops);
	if (major < 0)
		return major;

	return 0;
}
/* ### END: init */

/* ### START: exit */
static void echo_exit(void)
{
	unregister_chrdev(major, "echo");
}
/* ### END: exit */

module_init(echo_init);
module_exit(echo_exit);
MODULE_LICENSE("GPL");
/* ### END: all */
