TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)
datauris = 					\
		noto-sans-ta.zip.datauri

all: tamil-font slides.html

noto-sans-ta.zip.datauri: MIMETYPE="application/zip"
noto-sans-ta.zip.datauri: noto-sans-ta.zip

tamil-font:
	wget -O noto-sans-ta.zip \
	     -c https://noto-website.storage.googleapis.com/pkgs/NotoSansTamil-hinted.zip

slides.html: $(images_png) $(datauris)

test:
	cd code; python3 -m doctest -o IGNORE_EXCEPTION_DETAIL 	\
		-o ELLIPSIS					\
		lang.py						\
		fobj.py						\
		iexamples.py

clean:
	rm -f $(images_png)
	rm -f $(datauris)
	rm -f slides.html
	rm -fr code/fobj
	rm -fr code/iexamples
	rm -f noto-sans-ta.zip
	find . -name "*~" -delete
	find . -name "*.pyc" -delete
	find . -name __pycache__ -prune -exec rm -rf {} ";"

include $(TOPDIR)/stylesheets/Makefile.rules
