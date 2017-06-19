TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)
datauris = 					\
		code/cbuf-v1/cbuf.py.datauri 	\
		code/cbuf-v3/cbuf.py.datauri	\
		code/cbuf-v6/cbuf.py.datauri

code/cbuf-v1/cbuf.py.datauri: MIMETYPE="text/plain;charset=us-ascii"
code/cbuf-v3/cbuf.py.datauri: MIMETYPE="text/plain;charset=us-ascii"
code/cbuf-v6/cbuf.py.datauri: MIMETYPE="text/plain;charset=us-ascii"

all: cbuf-v1-py-split cbuf-v3-py-split cbuf-v4-py-split cbuf-v6-py-split stack-py-split strlist-py-split strint-py-split slides.html

cbuf-v1-py-split:
	python $(TOPDIR)/scripts/split.py code/cbuf-v1.py

cbuf-v3-py-split:
	python $(TOPDIR)/scripts/split.py code/cbuf-v3.py

cbuf-v4-py-split:
	python $(TOPDIR)/scripts/split.py code/cbuf-v4.py

cbuf-v6-py-split:
	python $(TOPDIR)/scripts/split.py code/cbuf-v6.py

stack-py-split:
	python $(TOPDIR)/scripts/split.py code/stack.py

strlist-py-split:
	python $(TOPDIR)/scripts/split.py code/strlist.py

strint-py-split:
	python $(TOPDIR)/scripts/split.py code/strint.py

slides.html: $(images_png) $(datauris)

test:
	python3 -m doctest -o IGNORE_EXCEPTION_DETAIL 	\
		code/cbuf-v1.py 			\
		code/cbuf-v3.py 			\
		code/cbuf-v4.py 			\
		code/cbuf-v6.py				\
		code/stack.py 				\
		code/strlist.py				\
		code/strint.py

clean:
	rm -f $(images_png)
	rm -f slides.html
	rm -fr code/cbuf-v1
	rm -fr code/cbuf-v3
	rm -fr code/cbuf-v4
	rm -fr code/cbuf-v6
	rm -fr code/stack
	rm -fr code/strlist
	rm -fr code/strint
	find . -name *~ -delete
	find . -name *.pyc -delete
	rm -fr code/__pycache__

include $(TOPDIR)/stylesheets/Makefile.rules
