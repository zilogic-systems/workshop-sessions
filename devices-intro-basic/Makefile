TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

all: slides.html

slides.html: $(images_png) $(datauris)

clean:
	rm -f $(images_png)
	rm -f slides.html
	rm -f figures/usb.png
	rm -f $(datauris)

include $(TOPDIR)/stylesheets/Makefile.rules
