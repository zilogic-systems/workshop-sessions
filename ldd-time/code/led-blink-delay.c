/* ### START: led-blink-delay.full */

/* ### START: led-blink-delay.def */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/delay.h>

#define LED_PIN1 64
#define LED_PIN2 65
#define LED_PIN3 70
#define SIZE 3

static struct gpio led_gpio[SIZE] = {
	{ LED_PIN1, GPIOF_OUT_INIT_LOW, "LED1"},
	{ LED_PIN2, GPIOF_OUT_INIT_LOW, "LED2"},
	{ LED_PIN3, GPIOF_OUT_INIT_LOW, "LED3"}
};
/* ### END: led-blink-delay.def */

/* ### START: led-blink-delay.init */
static int led_init(void)
{
        int ret, i;
	
	if (ret = gpio_request_array(led_gpio, SIZE)) {
		printk("Error Requesting GPIO");
		return ret;
	}
	for (i = 0; i < SIZE; i++) {
		gpio_set_value(LED_PIN1, 1);
		mdelay(1000);
		gpio_set_value(LED_PIN1, 0);
		mdelay(1000);
	}
        return 0;
}

/* ### END: led-blink-delay.init */

/* ### START: led-blink-delay.exit */


static void led_exit(void)
{
	gpio_free_array(led_gpio, SIZE);	
}

module_init(led_init);
module_exit(led_exit);
MODULE_LICENSE("GPL");

/* ### END: led-blink-delay.exit */
/* ### END: led-blink-delay.full */
