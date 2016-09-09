TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)
datauris = code/i2c-my/my.c.datauri

all: slides.html

code/i2c-my/my.c.datauri: MIMETYPE="text/plain;charset=us-ascii"

slides.html: $(images_png) $(datauris)

clean:
	rm -f $(images_png)
	rm -f $(datauris)
	rm -f slides.html

include $(TOPDIR)/stylesheets/Makefile.rules
