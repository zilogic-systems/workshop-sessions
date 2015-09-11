TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

all: slides.html

slides.html: zepto-split code/zepto.sh $(images_png) 

zepto-split:
	python $(TOPDIR)/scripts/split.py code/zepto.sh

clean:
	rm -f $(images_png)
	rm -f slides.html
	rm -fr code/zepto

include $(TOPDIR)/stylesheets/Makefile.rules
