-include ~/.zdeck
TOPDIR = ../

ZDECK_HOME ?= /usr/share/zdeck
ZDECK_CLASS = lecture

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

all: slides.html

slides.html: simple-split code/yocto-build.sh $(images_png)

simple-split:
	python3 $(TOPDIR)/scripts/split.py code/yocto-build.sh

clean:
	rm -f $(images_png)
	rm -f slides.html
	rm -fr code/yocto-build

include $(ZDECK_HOME)/stylesheets/Makefile.rules
include $(TOPDIR)/stylesheets/Makefile.zdeck.rules
