TOPDIR = ../
-include ~/.zdeck

ZDECK_HOME ?= /usr/share/zdeck
ZDECK_CLASS = lecture

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)
datauris = 					\
		code/calc.html.datauri

code/calc.html.datauri: MIMETYPE="text/html"

all: slides.html

slides.html: $(images_png) $(datauris)

clean:
	rm -f $(images_png)
	rm -f $(datauris)
	rm -f slides.html

include $(ZDECK_HOME)/stylesheets/Makefile.rules
include $(TOPDIR)/stylesheets/Makefile.zdeck.rules
