/* ### START: key-scan.full */
/* ### START: key-scan.def */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/workqueue.h>
#include <linux/gpio.h>

#define KEY_PIN 67

static void scan_keys(struct work_struct *work);
DECLARE_DELAYED_WORK(scan_keys_work, scan_keys);

static int scan_stop = 0;


static void scan_keys(struct work_struct *work)
{
     if (!gpio_get_value(KEY_PIN))
          printk("Key 1 - Pressed\n");
    
     if (!scan_stop)
          schedule_delayed_work(&scan_keys_work, 15);
}

/* ### END: key-scan.def */
/* ### START: key-scan.init */

static int scan_init(void)
{
     int ret;

     ret = gpio_request(KEY_PIN, "key1");
     if (ret)
          return ret;
    
     gpio_direction_input(KEY_PIN);
     schedule_delayed_work(&scan_keys_work, 20);

     return 0;
}

/* ### END: key-scan.init */
/* ### START: key-scan.exit */

static void scan_exit(void)
{
     scan_stop = 1;

     cancel_delayed_work_sync(&scan_keys_work);
     gpio_free(KEY_PIN);
}

module_init(scan_init);
module_exit(scan_exit);
MODULE_LICENSE("GPL");
/* ### END: key-scan.exit */
/* ### END: key-scan.full */
