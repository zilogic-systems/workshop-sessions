-include ~/.zdeck
TOPDIR = ../

ZDECK_HOME ?= /usr/share/zdeck
ZDECK_CLASS = lecture

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

all: cmd-split slides.html

slides.html: $(images_png) 

cmd-split:
	python3 $(TOPDIR)/scripts/split.py cmd.sh

clean:
	rm -f $(images_png)
	rm -f slides.html
	rm -fr cmd/

include $(ZDECK_HOME)/stylesheets/Makefile.rules
