-include ~/.zdeck

ZDECK_HOME ?= /usr/share/zdeck
ZDECK_CLASS = lecture

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

all: slides.html

figures/mainframe.png: EXPORT_WIDTH=800
figures/virtual-terminal.png: EXPORT_WIDTH=800

slides.html: $(images_png) $(datauris)

.PHONY: clean
clean:
	rm -f slides.html

include $(ZDECK_HOME)/stylesheets/Makefile.rules
