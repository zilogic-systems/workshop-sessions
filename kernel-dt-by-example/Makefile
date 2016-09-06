TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

all: v2-dts-split v3-dts-split v4-dts-split slides.html

v2-dts-split:
	python $(TOPDIR)/scripts/split.py code/v2.dts

v3-dts-split:
	python $(TOPDIR)/scripts/split.py code/v3.dts

v4-dts-split:
	python $(TOPDIR)/scripts/split.py code/v4.dts


slides.html: $(images_png) 

clean:
	rm -f $(images_png)
	rm -f slides.html

include $(TOPDIR)/stylesheets/Makefile.rules
