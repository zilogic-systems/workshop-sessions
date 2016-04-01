TOPDIR = ../

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

all: $(images_png) slides.html

clean:
	rm -f $(images_png)
	rm -f slides.html

include $(TOPDIR)/stylesheets/Makefile.rules
