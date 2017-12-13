TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

datauris = cdist/ikey-v1.tar.gz.datauri cdist/ikey-v2.tar.gz.datauri cdist/ikey-v3.tar.gz.datauri

all: ikey-v1-split ikey-v2-split ikey-v3-split slides.html

%.tar.gz.datauri: MIMETYPE="application/gzip"

cdist/ikey-v1.tar.gz:
	mkdir -p cdist/ikey-v1
	cp code/ikey-v1/ikey/all cdist/ikey-v1/ikey.c
	cp code/ikey-v1/Makefile cdist/ikey-v1/
	tar --gzip -C cdist -c -f cdist/ikey-v1.tar.gz ikey-v1

cdist/ikey-v2.tar.gz:
	mkdir -p cdist/ikey-v2
	cp code/ikey-v2/ikey/all cdist/ikey-v2/ikey.c
	cp code/ikey-v2/Makefile cdist/ikey-v2/
	tar --gzip -C cdist -c -f cdist/ikey-v2.tar.gz ikey-v2

cdist/ikey-v3.tar.gz:
	mkdir -p cdist/ikey-v3
	cp code/ikey-v3/ikey/all cdist/ikey-v3/ikey.c
	cp code/ikey-v3/Makefile cdist/ikey-v3/
	tar --gzip -C cdist -c -f cdist/ikey-v3.tar.gz ikey-v3

key-split:
	python $(TOPDIR)/scripts/split.py code/key/key.c

ikey-v1-split:
	python $(TOPDIR)/scripts/split.py code/ikey-v1/ikey.c

ikey-v2-split:
	python $(TOPDIR)/scripts/split.py code/ikey-v2/ikey.c

ikey-v3-split:
	python $(TOPDIR)/scripts/split.py code/ikey-v3/ikey.c

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
