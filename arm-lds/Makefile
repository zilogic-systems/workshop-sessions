TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)
datauris = code/add-ram.s.datauri code/add-ram.lds.datauri

figures/sections.png: EXPORT_WIDTH=2048
code/add-ram.s.datauri: MIMETYPE="text/plain;charset=us-ascii"
code/add-ram.lds.datauri: MIMETYPE="text/plain;charset=us-ascii"

all: slides.html

slides.html: $(images_png) $(datauris)

clean:
	rm -f $(images_png)
	rm -f $(datauris)
	rm -f slides.html

include $(TOPDIR)/stylesheets/Makefile.rules
