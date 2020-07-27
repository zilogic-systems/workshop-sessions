-include ~/.zdeck
TOPDIR = ../

ZDECK_HOME ?= /usr/share/zdeck
ZDECK_CLASS = lecture

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

ZDECK_DIA_EXPORT_WIDTH = 1600

all: slides.html tryout.tar.gz

slides.html: $(images_png) $(datauris)

tryout.tar.gz:
	make -C git-resources
	GIT_RES_DIR=../../git-resources make -C tryout reset
	tar --gzip -c -f tryout.tar.gz tryout/ex*

clean:
	rm -f $(images_png)
	rm -f slides.html
	rm -f tryout.tar.gz

include $(ZDECK_HOME)/stylesheets/Makefile.rules
include $(TOPDIR)/stylesheets/Makefile.zdeck.rules
