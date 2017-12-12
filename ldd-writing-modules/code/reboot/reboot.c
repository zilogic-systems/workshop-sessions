#include <linux/init.h>
#include <linux/module.h>
#include <linux/reboot.h>

int reboot_handler(struct notifier_block *nb, unsigned long event, void *ptr)
{
	printk("My reboot handler called\n");
	return 0;
}

static struct notifier_block reboot_nb;

static int reboot_init(void)
{
	reboot_nb.notifier_call = reboot_handler;
	return register_reboot_notifier(&reboot_nb);
}

static void reboot_exit(void)
{
	unregister_reboot_notifier(&reboot_nb);
}

module_init(reboot_init);
module_exit(reboot_exit);
MODULE_LICENSE("GPL");
