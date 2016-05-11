TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)
datauris = code/csum/csum.full.datauri code/startup/startup.full.datauri

code/csum/csum.full.datauri: MIMETYPE="text/plain;charset=us-ascii"
code/startup/startup.full.datauri: MIMETYPE="text/plain;charset=us-ascii"

all: csum-lds-split startup-split slides.html

csum-lds-split:
	python $(TOPDIR)/scripts/split.py code/csum.lds

startup-split:
	python $(TOPDIR)/scripts/split.py code/startup.s

slides.html: $(images_png) $(datauris)

clean:
	rm -f $(images_png)
	rm -f $(datauris)
	rm -f slides.html
	rm -f code/csum
	rm -f code/startup

include $(TOPDIR)/stylesheets/Makefile.rules
