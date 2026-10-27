TOPDIR = ../
-include ~/.zdeck

ZDECK_HOME ?= /usr/share/zdeck
ZDECK_CLASS = lecture

EXPORT_WIDTH  = 1600

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

#images_svg = $(wildcard figures/*.svg)
#images_png += $(images_svg:.svg=.png)

all: slides.html

figures/datastore.png: EXPORT_WIDTH = 2048

slides.html: $(images_png) 

clean:
	rm -f $(images_png)
	rm -f slides.html

include $(ZDECK_HOME)/stylesheets/Makefile.rules
include $(TOPDIR)/stylesheets/Makefile.zdeck.rules
