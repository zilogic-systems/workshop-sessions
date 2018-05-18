TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

all: slides.html

slides.html: $(images_png)

clean:
	rm -f $(images_png)
	rm -f $(datauris)
	rm -f slides.html

distclean: clean
	find . -name "*.pyc" -delete
	find . -name "*~" -delete
	find . -name "*.ttf" -delete

include $(TOPDIR)/stylesheets/Makefile.rules
