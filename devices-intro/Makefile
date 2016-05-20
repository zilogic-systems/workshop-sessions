TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

all: slides.html

figures/io-controller.png: figures/usb.png

figures/usb.png:
	wget --no-check-certificate -O $@ -c 'https://upload.wikimedia.org/wikipedia/commons/thumb/6/65/Usbdrive_icon.svg/480px-Usbdrive_icon.svg.png'

slides.html: $(images_png) 

clean:
	rm -f $(images_png)
	rm -f slides.html
	rm -fr code/simple
	rm -f figures/usb.png

include $(TOPDIR)/stylesheets/Makefile.rules
