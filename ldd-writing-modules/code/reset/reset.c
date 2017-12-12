#include <linux/init.h>
#include <linux/module.h>
#include <asm/io.h>
#include "src_regs.h"

int init_module(void)
{
	void *base = ioremap(SRC_BASE, 16);  /* XXX: returns NULL on failure */
	void *reg = base + SCR_REG;
	iowrite32(ioread32(reg) | (1 << 12), reg);
	return 0;
}

static void cleanup_module(void) {}

MODULE_LICENSE("GPL");
