TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)
datauris = code/nor-support.patch.datauri

all: slides.html

slides.html: $(images_png) $(datauris)
code/nor-support.patch.datauri: MIMETYPE="text/plain;charset=us-ascii"

clean:
	rm -f $(images_png)
	rm -f $(datauris)
	rm -f slides.html

include $(TOPDIR)/stylesheets/Makefile.rules
