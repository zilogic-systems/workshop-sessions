TOPDIR = ../
-include ~/.zdeck

ZDECK_HOME ?= /usr/share/zdeck
ZDECK_CLASS = lecture

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)
datauris   = code/app.c.datauri

all: $(images_png) $(datauris) slides.html
code/app.c.datauri: MIMETYPE="text/plain;charset=us-ascii"

clean:
	rm -f $(images_png)
	rm -f slides.html

include $(ZDECK_HOME)/stylesheets/Makefile.rules
include $(TOPDIR)/stylesheets/Makefile.zdeck.rules
