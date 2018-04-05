/* ### START: lcd.full */
/* ### START: lcd.def */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/i2c.h>

#define DATA_REG_ADDR 0x0

static struct i2c_client * client;

static void display_msg(void)
{
	int i, ret;
	char buf[2];
	char *msg = "Hello World";

	for (i = 0; i < strlen(msg); i++) {
		buf[0] = DATA_REG_ADDR;
		buf[1] = msg[i];
		ret = i2c_master_send(client, buf, sizeof(buf));
		if (ret != sizeof(buf))
			printk("lcd: error sending data");
	}
}
/* ### END: lcd.def */
/* ### START: lcd.init */
static int lcd_init(void)
{
	struct i2c_adapter * adapter;
	struct i2c_board_info board_info = { .type = "lcd", 
					     .addr = 0x40 };

	if ((adapter = i2c_get_adapter(0)) == NULL) {
		printk("lcd: error getting adapter");
		return -ENODEV;
	}

	if ((client = i2c_new_device(adapter, &board_info)) == NULL) {
		printk("lcd: error creating client");
		return -EBUSY;
	}
	display_msg();
	
	return 0;
}
/* ### END: lcd.init */

/* ### START: lcd.exit */
static void lcd_exit(void)
{
	i2c_unregister_device(client);
}

module_init(lcd_init);
module_exit(lcd_exit);
MODULE_LICENSE("GPL");
/* ### END: lcd.exit */
/* ### END: lcd.full */
