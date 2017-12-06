/* ### START: led-blink-wq-param.full */
/* ### START: led-blink-wq-param.inc */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/workqueue.h>
#include <linux/gpio.h>

#define LED_PIN1 64
#define LED_PIN2 65
#define LED_PIN3 70
#define SIZE 3

static struct gpio led_gpio[SIZE] = {
	{ LED_PIN1, GPIOF_OUT_INIT_LOW, "LED1"},
	{ LED_PIN2, GPIOF_OUT_INIT_LOW, "LED2"},
	{ LED_PIN3, GPIOF_OUT_INIT_LOW, "LED3"}
};

static int led_color = 3;
module_param(led_color, int, 0664);
MODULE_PARM_DESC(led_color,"Changes LED color");

/* ### END: led-blink-wq-param.inc */

/* ### START: led-blink-wq-param.def */
static void blink_led(struct work_struct *work);
DECLARE_DELAYED_WORK(blink_led_work, blink_led);
static int blink_stop = 0;

void set_led(int state)
{
        if (state) {
		gpio_set_value(LED_PIN1, led_color & 1);
		gpio_set_value(LED_PIN2, (led_color & 2) >> 1);
		gpio_set_value(LED_PIN3, (led_color & 4) >> 2);
	} else {
		gpio_set_value(LED_PIN1, 0);
		gpio_set_value(LED_PIN2, 0);
		gpio_set_value(LED_PIN3, 0);
	}
}

static void blink_led(struct work_struct *work)
{
        static int state;
        set_led(state)
        state = !state;
        if (!blink_stop)
                schedule_delayed_work(&blink_led_work, 1 * HZ);
}
/* ### END: led-blink-wq-param.def */

/* ### START: led-blink-wq-param.init */

static int blink_init(void)
{
        int ret;
	
	ret = gpio_request_array(led_gpio, SIZE);

        if (ret) {
		printk("error requesting GPIO");
                return ret;
	}
        gpio_direction_output(LED_PIN1, 1);
        schedule_delayed_work(&blink_led_work, 1 * HZ);
        return 0;
}

/* ### END: led-blink-wq-param.init */

/* ### START: led-blink-wq-param.exit */

static void blink_exit(void)
{
        blink_stop = 1;
        cancel_delayed_work_sync(&blink_led_work);
	gpio_set_value(LED_PIN1, 0);
	gpio_free_array(led_gpio, SIZE);

}
module_init(blink_init);
module_exit(blink_exit);
MODULE_LICENSE("GPL");

/* ### END: led-blink-wq-param.exit */
/* ### END: led-blink-wq-param.full */
