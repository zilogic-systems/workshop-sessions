/* ### START: led.full */


/* ### START: led.def */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/delay.h>

#define LED_PIN1 64
	
/* ### END: led.def */
/* ### START: led.init */
static int led_init(void)
{
        int ret;

	ret = gpio_request(LED_PIN1, "hello-led");
	if (ret) {
		printk("error requesting GPIO %u", LED_PIN1);
		return ret;
	}
	gpio_direction_output(LED_PIN1, 0);
		
        return 0;
}
/* ### END: led.init */

/* ### START: led.exit */
static void led_exit(void)
{
	gpio_set_value(LED_PIN1, 1);
	gpio_free(LED_PIN1);
}

module_init(led_init);
module_exit(led_exit);
MODULE_LICENSE("GPL");

/* ### END: led.exit */
/* ### END: led.full */
