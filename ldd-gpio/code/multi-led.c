/* ### START: multi-led.full */
/* ### START: multi-led.def */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/gpio.h>

#define SIZE 3
#define LED_PIN1 64
#define LED_PIN2 65
#define LED_PIN3 70


static struct gpio led_gpio[SIZE] = {
  /*      PIN     , STATE             , NAME */ 
	{ LED_PIN1, GPIOF_OUT_INIT_LOW, "LED1"},
	{ LED_PIN2, GPIOF_OUT_INIT_LOW, "LED2"},
	{ LED_PIN3, GPIOF_OUT_INIT_LOW, "LED3"}
};

/* ### END: multi-led.def */

/* ### START: multi-led.init */
	
static int led_init(void)
{
        int ret;

	ret = gpio_request_array(led_gpio, SIZE);
	if (ret) {
		printk("error requesting GPIO");
		return ret;
	}

	gpio_set_value(LED_PIN1, 1);
	gpio_set_value(LED_PIN2, 0);
	gpio_set_value(LED_PIN3, 1);

	return 0;
}

/* ### END: multi-led.init */

/* ### START: multi-led.exit */

static void led_exit(void)
{
	gpio_free_array(led_gpio, SIZE);
}

module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");
/* ### END: multi-led.exit */
/* ### END: multi-led.full */
