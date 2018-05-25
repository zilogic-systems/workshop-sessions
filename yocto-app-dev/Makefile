TOPDIR = ../

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)
datauris   = code/app.c.datauri

all: slides.html $(images_png) $(datauris)
code/app.c.datauri: MIMETYPE="text/plain;charset=us-ascii"

clean:
	rm -f $(images_png)
	rm -f slides.html

include $(TOPDIR)/stylesheets/Makefile.rules
