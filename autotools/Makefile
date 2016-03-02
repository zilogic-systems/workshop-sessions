TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

all: slides.html

clean:
	rm -f $(images_png)
	rm -f slides.html

include $(TOPDIR)/stylesheets/Makefile.rules
