TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

all: cmd-split slides.html

slides.html: $(images_png) 

cmd-split:
	python $(TOPDIR)/scripts/split.py cmd.sh

clean:
	rm -f $(images_png)
	rm -f slides.html
	rm -fr cmd/

include $(TOPDIR)/stylesheets/Makefile.rules
