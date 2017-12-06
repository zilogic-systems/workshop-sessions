/* ### START: led-params.full */
/* ### START: led-params.def */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/moduleparam.h>

static int led_color = 3;
module_param(led_color, int, 0664);
MODULE_PARM_DESC(led_color,"Changes LED color");

#define SIZE 3
#define LED_PIN1 64
#define LED_PIN2 65
#define LED_PIN3 70

static struct gpio led_gpio[SIZE] = {
	{ LED_PIN1, GPIOF_OUT_INIT_LOW, "LED1"},
	{ LED_PIN2, GPIOF_OUT_INIT_LOW, "LED2"},
	{ LED_PIN3, GPIOF_OUT_INIT_LOW, "LED3"}
};

/* ### END: led-params.def */

/* ### START: led-params.init */
	
static int led_init(void)
{
        int ret;

	ret = gpio_request_array(led_gpio, SIZE);
	if (ret) {
		printk("error requesting GPIO");
		return ret;
	}

	gpio_set_value(LED_PIN1, led_color & 1);
	gpio_set_value(LED_PIN2, (led_color & 2) >> 1);
	gpio_set_value(LED_PIN3, (led_color & 4) >> 2);

	return 0;
}

/* ### END: led-params.init */

/* ### START: led-params.exit */

static void led_exit(void)
{
	gpio_free_array(led_gpio, SIZE);
}

module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");
/* ### END: led-params.exit */
/* ### END: led-params.full */
