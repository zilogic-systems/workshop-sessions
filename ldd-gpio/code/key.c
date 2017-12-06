/* ### START: key.full */
/* ### START: key.def */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/gpio.h>

#define KEY_PIN 67
/* ### END: key.def */

/* ### START: key.init */

static int key_init(void)
{
     int ret;

     ret = gpio_request(KEY_PIN, "key1");
     if (ret)
          return ret;
    
     gpio_direction_input(KEY_PIN);

     if (!gpio_get_value(KEY_PIN))
          printk("Key 1 - Pressed\n");

     return 0;
}

/* ### END: key.init */

/* ### START: key.exit */

static void key_exit(void)
{
     gpio_free(KEY_PIN);
}

module_init(key_init);
module_exit(key_exit);
MODULE_LICENSE("GPL");

/* ### END: key.exit */
/* ### END: key.full */
