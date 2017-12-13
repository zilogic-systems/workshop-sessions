TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

datauris = cdist/key.tar.gz.datauri cdist/i2c-key.tar.gz.datauri

all: key-split i2c-key-split slides.html

%.tar.gz.datauri: MIMETYPE="application/gzip"

cdist/key.tar.gz:
	mkdir -p cdist/key
	cp code/key/key/all cdist/key/key.c
	cp code/key/Makefile cdist/key/
	tar --gzip -C cdist -c -f cdist/key.tar.gz key

cdist/i2c-key.tar.gz:
	mkdir -p cdist/i2c-key
	cp code/i2c-key/i2c-key/all cdist/i2c-key/i2c-key.c
	cp code/i2c-key/Makefile cdist/i2c-key/
	tar --gzip -C cdist -c -f cdist/i2c-key.tar.gz i2c-key

key-split:
	python $(TOPDIR)/scripts/split.py code/key/key.c

i2c-key-split:
	python $(TOPDIR)/scripts/split.py code/i2c-key/i2c-key.c

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
