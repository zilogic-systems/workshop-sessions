TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

figures/dts-inheritance.png: EXPORT_WIDTH = 2048

all: v2-dts-split v3-dts-split v4-dts-split v5-dts-split v6-dts-split v7-dts-split slides.html

v2-dts-split:
	python $(TOPDIR)/scripts/split.py code/v2.dts

v3-dts-split:
	python $(TOPDIR)/scripts/split.py code/v3.dts

v4-dts-split:
	python $(TOPDIR)/scripts/split.py code/v4.dts

v5-dts-split:
	python $(TOPDIR)/scripts/split.py code/v5.dts

v6-dts-split:
	python $(TOPDIR)/scripts/split.py code/v6.dts

v7-dts-split:
	python $(TOPDIR)/scripts/split.py code/v7.dts

slides.html: $(images_png) 

clean:
	rm -f $(images_png)
	rm -f slides.html
	rm -fr code/v2 code/v3 code/v4 code/v5 code/v6 code/v7

include $(TOPDIR)/stylesheets/Makefile.rules
