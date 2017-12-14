TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

datauris = cdist/key.tar.gz.datauri cdist/ikey.tar.gz.datauri

all: key-split ikey-split slides.html

%.tar.gz.datauri: MIMETYPE="application/gzip"

cdist/key.tar.gz:
	mkdir -p cdist/key
	cp code/key/key/all cdist/key/key.c
	cp code/key/Makefile cdist/key/
	tar --gzip -C cdist -c -f cdist/key.tar.gz key

cdist/ikey.tar.gz:
	mkdir -p cdist/ikey
	cp code/ikey/ikey/all cdist/ikey/ikey.c
	cp code/ikey/Makefile cdist/ikey/
	tar --gzip -C cdist -c -f cdist/ikey.tar.gz ikey

key-split:
	python $(TOPDIR)/scripts/split.py code/key/key.c

ikey-split:
	python $(TOPDIR)/scripts/split.py code/ikey/ikey.c

%.tar.gz.datauri: MIMETYPE="application/gzip"

%.png: %.svg
	inkscape --without-gui --export-background=white --export-area-drawing --export-png=$@ $<

slides.html: $(images_png) $(srcs_zip) $(datauris)

distclean: clean
	find . -name "*~" -delete

clean:
	rm -f $(images_png) $(srcs_zip)
	rm -fr cdist
	rm -f slides.html

include $(TOPDIR)/stylesheets/Makefile.rules
