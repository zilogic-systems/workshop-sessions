/* ### START: ikey.full */
/* ### START: ikey.def */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/i2c.h>

#define REG_STAT_ADDR  0x0
#define REG_DATA_ADDR  0x1

static struct i2c_client * client;
static int scan_stop = 0;

static void scan_keys(struct work_struct *work);
DECLARE_DELAYED_WORK(scan_keys_work, scan_keys);

static void ikey_reg_read(char addr, char *data)
{
	i2c_master_send(client, &addr, 1);
        i2c_master_recv(client, data, 1);
}

static bool ikey_get(char * ikey)
{
	char key_avail;

	ikey_reg_read(REG_STAT_ADDR, &key_avail);
	if (!key_avail)
		return false;

	ikey_reg_read(REG_DATA_ADDR, ikey);
	return true;
}

static void scan_keys(struct work_struct *work)
{
  static char key_no;

     if (ikey_get(&key_no))
          printk("Key %d - Pressed\n", key_no);
    
     if (!scan_stop)
          schedule_delayed_work(&scan_keys_work, 15);
}
/* ### END: ikey.def */
/* ### START: ikey.init */
static int ikey_init(void)
{
	struct i2c_adapter * adapter;
	struct i2c_board_info board_info = { .type = "ikey", .addr = 0x20 };

	if ((adapter = i2c_get_adapter(0)) == NULL) {
		printk("ikey: error getting adapter");
		return -ENODEV;
	}

	if ((client = i2c_new_device(adapter, &board_info)) == NULL) {
		printk("ikey: error creating client");
		return -EBUSY;
	}
	schedule_delayed_work(&scan_keys_work, 20);
	return 0;
}
/* ### END: ikey.init */

/* ### START: ikey.exit */
static void ikey_exit(void)
{
     scan_stop = 1;
     
     cancel_delayed_work_sync(&scan_keys_work);
     i2c_unregister_device(client);
}

module_init(ikey_init);
module_exit(ikey_exit);
MODULE_LICENSE("GPL");

/* ### END: ikey.exit */
/* ### END: ikey.full */
