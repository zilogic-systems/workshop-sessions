/* ### START: led.full */

/* ### START: led.def */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/leds.h>

#define LED_PIN1 70
set_led_brightness()
{
	gpio_set_value(LED_PIN1, 1);
	printk("Set Brightness");
}

set_led_blink()
{
        printk("Set Blink");
}

/* ### END: led.def */
/* ### START: led.init */
static int led_init(void)
{
        int ret;
	struct led_classdev led_cl;

	ret = gpio_request(LED_PIN1, "hello-led");
	if (ret) {
		printk("error requesting GPIO %u", LED_PIN1);
		return ret;
	}
	gpio_direction_output(LED_PIN1, 0);

	led_cl.name = "tricolor-led";
        led_cl.brightness = LED_OFF;
        led_cl.brightness_set = set_led_brightness;
        led_cl.blink_set = NULL;

        ret = led_classdev_register(NULL, &led_cl);
        if (ret < 0) {
	  printk("couldn't register LED %s\n", led_cl.name);
	  return -1;;
        }
		
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
