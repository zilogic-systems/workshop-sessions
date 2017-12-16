TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)
srcs_dir = $(sort $(dir $(wildcard code/*/.)))
srcs_zip = $(srcs_dir:/=.tar.gz)
datauris = $(srcs_zip:.tar.gz=.tar.gz.datauri)

all: slides-kp.html slides-ldd.html

%.tar.gz.datauri: MIMETYPE="application/gzip"

code/i2c-my/my.c.datauri: MIMETYPE="text/plain;charset=us-ascii"

slides-kp.html: slides-common.asciidoc $(images_png) $(datauris)

slides-ldd.html: slides-common.asciidoc $(images_png) $(datauris)

clean:
	rm -f $(images_png)
	rm -f $(datauris)
	rm -f slides.html

include $(TOPDIR)/stylesheets/Makefile.rules
