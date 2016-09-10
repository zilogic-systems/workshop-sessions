#include <linux/init.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <asm/io.h>

#if defined(CONFIG_PXA27X)
#define RTC_BASE 0x40900000
#define RTC_IRQ 47
#elif  define(CONFIG_PXA300)
#define RTC_BASE 0x40800000
#define RTC_IRQ 47
#endif

#define RTC_SIZE 0xFFFFF
#define PIAR 0x38
#define PICR 0x34
#define RTSR 0x8

static u32 __iomem *rtc_base;

irqreturn_t tick_handler(int irq, void *data)
{

	printk("RTC Interrupt occured\n");
	iowrite32(0xe00f, (unsigned char *)rtc_base + RTSR);

	return 0;
}

static int pxa_rtc_init(void)
{
	rtc_base = ioremap(RTC_BASE, RTC_SIZE);

	if (request_irq(RTC_IRQ, tick_handler, 0, "rtc-irq", NULL))
		goto err_irq;

	iowrite32(0, (unsigned char *)rtc_base + PICR);
	iowrite32(10000, (unsigned char *)rtc_base + PIAR);	
	iowrite32(0xc00c, (unsigned char *) rtc_base + RTSR);	

	printk("RTC Alarm Set for 10 Sec\n");
	return 0;
err_irq:
  	iounmap(rtc_base);
	return -1;
}

static void pxa_rtc_exit(void)
{
	iounmap(rtc_base);
        free_irq(RTC_IRQ, NULL);	
	return;
}

module_init(pxa_rtc_init);
module_exit(pxa_rtc_exit);
MODULE_LICENSE("GPL");
