#include <linux/init.h>
#include <linux/module.h>
#include <asm/io.h>
#include <linux/platform_device.h>

enum {
	RTC_BASE = 0x40900000,
	RTC_SIZE = 0x100000,
};

static struct resource pxa_rtc_resources[] = {
       {
	.start	= RTC_BASE,
	.end	= RTC_BASE + RTC_SIZE,
	.flags	= IORESOURCE_MEM,
	.name	= "rtc-mem"
	},
	{
	.start	= 47,
	.end	= 47,
	.flags	= IORESOURCE_IRQ,
	.name	= "rtc_irq",
	}
};

static struct platform_device rtc_device = {
	.name = "pxa_rtc",
	.id = -1,
	.resource = pxa_rtc_resources,
	.num_resources = sizeof(pxa_rtc_resources) / sizeof (struct resource),
};

static int rtc_dev_init(void)
{
	platform_device_register(&rtc_device);
	return 0;
}

static void rtc_dev_exit(void)
{
	platform_device_unregister(&rtc_device);
	return;
}

module_init(rtc_dev_init);
module_exit(rtc_dev_exit);

MODULE_LICENSE("GPL");
