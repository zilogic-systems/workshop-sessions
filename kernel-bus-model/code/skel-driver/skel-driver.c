#include <linux/i2c.h>
#include <linux/module.h>
#include <linux/init.h>

static int skel_probe(struct i2c_client *client,
		    const struct i2c_device_id *id)
{
	printk("Probe: detected '%s'\n", id->name);
	return 0;
}

static int skel_remove(struct i2c_client *client)
{
	printk("Remove\n");
	return 0;
}

static const struct i2c_device_id skel_id[] = {
	{ "skel-dev-name-1", 0 },
	{ "skel-dev-name-2", 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, skel_id);

static struct i2c_driver skel_driver = {
	.driver		= {
		.name	= "skel-driver",
	},
	.probe		= skel_probe,
	.remove		= skel_remove,
	.id_table	= skel_id,
};

static int __init skel_init(void)
{
	return i2c_add_driver(&skel_driver);
}

static void __exit skel_exit(void)
{
	i2c_del_driver(&skel_driver);
}

MODULE_LICENSE("GPL");

module_init(skel_init);
module_exit(skel_exit);
