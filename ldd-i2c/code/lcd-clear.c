/* ### START: lcd-clear.full */
/* ### START: lcd-clear.def */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/i2c.h>

static struct i2c_client * client;

static void display_msg(void)
{
	int i;
	char buf[2];
	char *msg = "Hello World";
	int ret;

	for (i = 0; i < strlen(msg); i++) {
		buf[0] = 0x0;
		buf[1] = msg[i];
		ret = i2c_master_send(client, buf, sizeof(buf));
		if (ret != sizeof(buf))
			printk("lcd: error sending data");
	}
}

static void clear_msg(void)
{
	int i;
	char buf[2];
	int ret;

	buf[0] = 0x1;
	buf[1] = 1;

	ret = i2c_master_send(client, buf, sizeof(buf));
	if (ret != sizeof(buf))
		printk("lcd: error sending data");
	}
}
/* ### END: lcd-clear.def */
/* ### START: lcd-clear.init */
static int lcd_init(void)
{
	struct i2c_adapter * adapter;
	struct i2c_board_info board_info = { .type = "lcd", .addr = 0x40 };

	if (adapter = i2c_get_adapter(0) == NULL) {
		printk("lcd: error getting adapter");
		return -ENODEV;
	}

	if (client = i2c_new_device(adapter, &board_info) == NULL) {
		printk("lcd: error creating client");
		return -EBUSY;
	}
	display_msg();
	
	return 0;
}
/* ### END: lcd-clear.init */
/* ### START: lcd-clear.exit */
static void lcd_exit(void)
{
        clear_msg()
	i2c_unregister_device(client);
}

module_init(lcd_init);
module_exit(lcd_exit);
MODULE_LICENSE("GPL");
/* ### END: lcd-clear.exit */
/* ### END: lcd-clear.full */
