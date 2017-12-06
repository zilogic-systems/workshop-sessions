/* ### START: led-blink-wq.full */
/* ### START: led-blink-wq.inc */

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
/* ### END: led-blink-wq.inc */

/* ### START: led-blink-wq.def */
static void blink_led(struct work_struct *work);
DECLARE_DELAYED_WORK(blink_led_work, blink_led);
static int blink_stop = 0;

static void blink_led(struct work_struct *work)
{
        static int state;
        gpio_set_value(LED_PIN1, state);
        state = !state;
        if (!blink_stop)
                schedule_delayed_work(&blink_led_work, 1 * HZ);
}
/* ### END: led-blink-wq.def */

/* ### START: led-blink-wq.init */

static int blink_init(void)
{
        int ret;
	
	if (ret = gpio_request_array(led_gpio, SIZE)) {
  		printk("error requesting GPIO");
                return ret;
	}
        schedule_delayed_work(&blink_led_work, 1 * HZ);

        return 0;
}

/* ### END: led-blink-wq.init */

/* ### START: led-blink-wq.exit */

static void blink_exit(void)
{
        blink_stop = 1;
        cancel_delayed_work_sync(&blink_led_work);
	gpio_free_array(led_gpio, SIZE);

}
module_init(blink_init);
module_exit(blink_exit);
MODULE_LICENSE("GPL");

/* ### END: led-blink-wq.exit */
/* ### END: led-blink-wq.full */
