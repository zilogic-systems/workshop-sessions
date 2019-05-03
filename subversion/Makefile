TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

datauris = svn.tar.gz.datauri

all: slides.html

svn.tar.gz.datauri: MIMETYPE="application/gzip"

%.png: %.svg
	inkscape --without-gui --export-background=white --export-area-drawing --export-png=$@ $<

slides.html: $(images_png) $(datauris)

clean:
	rm -f $(images_png)
	rm -f slides.html

include $(TOPDIR)/stylesheets/Makefile.rules
