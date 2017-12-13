TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

datauris = cdist/y.tar.gz.datauri cdist/echo.tar.gz.datauri code/lcd.tar.gz.datauri

all: y-split echo-split slides.html

%.tar.gz.datauri: MIMETYPE="application/gzip"

cdist/y.tar.gz:
	mkdir -p cdist/y
	cp code/y/y/all cdist/y/y.c
	cp code/y/Makefile cdist/y/
	tar --gzip -C cdist -c -f cdist/y.tar.gz y

cdist/echo.tar.gz:
	mkdir -p cdist/echo
	cp code/echo/echo/all cdist/echo/echo.c
	cp code/echo/Makefile cdist/echo/
	tar --gzip -C cdist -c -f cdist/echo.tar.gz echo

y-split:
	python $(TOPDIR)/scripts/split.py code/y/y.c

echo-split:
	python $(TOPDIR)/scripts/split.py code/echo/echo.c

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
