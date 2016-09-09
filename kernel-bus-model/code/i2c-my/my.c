#include <linux/i2c.h>
#include <linux/module.h>
#include <linux/init.h>

static int my_probe(struct i2c_client *client,
		    const struct i2c_device_id *id)
{
	printk("Probe: detected '%s'\n", id->name);
	return 0;
}

static int my_remove(struct i2c_client *client)
{
	printk("Remove\n");
	return 0;
}

static const struct i2c_device_id my_id[] = {
	{ "my-dev-name-1", 0 },
	{ "my-dev-name-2", 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, my_id);

static struct i2c_driver my_driver = {
	.driver		= {
		.name	= "my-driver",
	},
	.probe		= my_probe,
	.remove		= my_remove,
	.id_table	= my_id,
};

static int __init my_init(void)
{
	return i2c_add_driver(&my_driver);
}

static void __exit my_exit(void)
{
	i2c_del_driver(&my_driver);
}

MODULE_LICENSE("GPL");

module_init(my_init);
module_exit(my_exit);
