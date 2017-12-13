/* ### START: all */
#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/gpio.h>

#define KEY_GPIO 4

/* ### START: handler */
static irqreturn_t key_handler(int irq, void *dev)
{
	if (gpio_get_value(KEY_GPIO) == 0)
		printk("Key pressed\n");
	else
		printk("Key released\n");
	
	return IRQ_HANDLED;
}
/* ### END: handler */

static int key_init(void)
{
	int err;
	int irq;

	err = gpio_request(KEY_GPIO, "key");
	if (err) {
		printk(KERN_ERR "error requesting GPIO pin");
		return err;
	}

	gpio_direction_input(KEY_GPIO);
	
	irq = gpio_to_irq(KEY_GPIO);
	err = request_irq(irq, key_handler, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING, "key", 0);
	if (err) {
		gpio_free(KEY_GPIO);
		printk(KERN_ERR "error request IRQ");
		return err;
	}

       return 0;
}

/* ### START: exit */
static void key_exit(void)
{
	int irq;

	irq = gpio_to_irq(KEY_GPIO);
	free_irq(irq, 0);
	gpio_free(KEY_GPIO);
}
/* ### END: exit */

module_init(key_init);
module_exit(key_exit);
MODULE_LICENSE("GPL");
/* ### END: all */
