TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

images_svg = $(wildcard figures/*.svg)
images_png += $(images_svg:.svg=.png)

all: slides.html

figures/datastore.png: EXPORT_WIDTH = 2048

slides.html: $(images_png) 

clean:
	rm -f $(images_png)
	rm -f slides.html

include $(TOPDIR)/stylesheets/Makefile.rules
