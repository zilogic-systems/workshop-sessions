#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/of_device.h>
#include <linux/interrupt.h>
#include <asm/io.h>

#define PIAR 0x38
#define PICR 0x34
#define RTSR 0x8

static u32 __iomem *rtc_base;
int irq;

irqreturn_t tick_handler(int irq, void *data)
{

	printk("RTC Interrupt occured\n");
	iowrite32(0xe00f, (unsigned char *)rtc_base + RTSR);

	return 0;
}

static int pxa_rtc_probe(struct platform_device *pdev)
{
	struct resource *addr_info;

	u32 base;
	u32 size;

	addr_info = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	base = addr_info->start;
	size = addr_info->end - addr_info->start;
	
	irq = platform_get_irq(pdev, 0);

	printk("RTC Base: %lx, irq : %d", (unsigned long) base, irq);

	rtc_base = ioremap(base, size);

	if (request_irq(irq, tick_handler, 0, "rtc-irq", NULL))
		goto err_irq;

	iowrite32(0, (unsigned char *)rtc_base + PICR);
	iowrite32(10000, (unsigned char *)rtc_base + PIAR);	
	iowrite32(0xc00c, (unsigned char *) rtc_base + RTSR);	

	return 0;

err_irq:
  	iounmap(rtc_base);
	return -1;
}

static int pxa_rtc_remove(struct platform_device *pdev)
{
	iounmap(rtc_base);
	free_irq(irq, NULL);
	return 0;
}

static struct platform_driver pxa_rtc_driver = {
	.driver = {
		.owner = THIS_MODULE,
		.name = "pxa_rtc",
	},
	.probe = pxa_rtc_probe,
	.remove = pxa_rtc_remove,
};

static int pxa_rtc_init(void)
{
	platform_driver_register(&pxa_rtc_driver);
	return 0;
}

static void pxa_rtc_exit(void)
{
	platform_driver_unregister(&pxa_rtc_driver);
	return;
}

module_init(pxa_rtc_init);
module_exit(pxa_rtc_exit);
MODULE_LICENSE("GPL");
