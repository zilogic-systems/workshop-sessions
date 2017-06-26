TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)
datauris = 					\
		code/lang.py.datauri


code/lang.py.datauri: MIMETYPE="text/plain;charset=us-ascii"

all: fobj-py-split iexamples-py-split slides.html

fobj-py-split:
	python $(TOPDIR)/scripts/split.py code/fobj.py

iexamples-py-split:
	python $(TOPDIR)/scripts/split.py code/iexamples.py

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
	find . -name "*~" -delete
	find . -name "*.pyc" -delete
	find . -name __pycache__ -prune -exec rm -rf {} ";"

include $(TOPDIR)/stylesheets/Makefile.rules
