TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)
srcs_dir = $(sort $(dir $(wildcard code/*/.)))
srcs_zip = $(srcs_dir:/=.tar.gz)
datauris = $(srcs_zip:.tar.gz=.tar.gz.datauri)

all: slides.html

%.tar.gz.datauri: MIMETYPE="application/gzip"

%.png: %.svg
	inkscape --without-gui --export-background=white --export-area-drawing --export-png=$@ $<

slides.html: $(images_png) $(srcs_zip) $(datauris)

distclean: clean
	find . -name "*~" -delete

clean:
	rm -f $(images_png) $(srcs_zip) $(datauris)
	rm -f slides.html

include $(TOPDIR)/stylesheets/Makefile.rules
