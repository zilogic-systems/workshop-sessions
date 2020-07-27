-include ~/.zdeck
TOPDIR = ../

ZDECK_HOME ?= /usr/share/zdeck
ZDECK_CLASS = lecture

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

ZDECK_DIA_EXPORT_WIDTH = 1600

all: slides.html

slides.html: $(images_png) $(datauris)

clean:
	rm -f $(images_png)
	rm -f slides.html

include $(ZDECK_HOME)/stylesheets/Makefile.rules
include $(TOPDIR)/stylesheets/Makefile.zdeck.rules
