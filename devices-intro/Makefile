TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)
datauris = u-boot.bin.datauri

all: slides.html

u-boot.bin.datauri: MIMETYPE="binary/octet-stream"

u-boot.bin:
	wget --no-check-certificate -O $@ https://downloads.gumstix.com/feeds/u-boot/u-boot-connex-400-r1604.bin

slides.html: $(images_png) $(datauris)

clean:
	rm -f $(images_png)
	rm -f slides.html
	rm -fr code/simple
	rm -f figures/usb.png
	rm -f u-boot.bin
	rm -f $(datauris)

include $(TOPDIR)/stylesheets/Makefile.rules
