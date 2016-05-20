TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)
datauris = code/Makefile.datauri
hexdumps = code/arr-align.hexdump code/arr.hexdump
nms = code/equ.nm

code/Makefile.datauri: MIMETYPE="text/plain;charset=us-ascii"

all: slides.html

slides.html: $(images_png) $(hexdumps) $(nms) $(datauris)

clean:
	rm -f $(images_png)
	rm -f slides.html
	rm -f $(hexdumps)
	rm -f $(nms)
	rm -f $(datauris)

%.hexdump: %.bin
	hexdump -v -e '/1 "%02X "' $< > $@

%.nm: %.elf
	nm $< > $@

%.bin: %.elf
	arm-none-eabi-objcopy -O binary $< $@

%.elf: %.s
	arm-none-eabi-as -o $@ $<


include $(TOPDIR)/stylesheets/Makefile.rules
