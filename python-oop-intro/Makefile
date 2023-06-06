TOPDIR = ../
-include ~/.zdeck

ZDECK_HOME ?= /usr/share/zdeck
ZDECK_CLASS = lecture

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)
datauris = code/bitarray1.py.datauri

all: slides.html advanced.html

code/bitarray1.py.datauri: MIMETYPE = "text/python"

slides.html: $(images_png) $(datauris)

test:
	python3 -m doctest -o IGNORE_EXCEPTION_DETAIL 	\
		code/strint.py

clean:
	rm -f $(images_png)
	rm -f slides.html
	rm -f advanced.html
	find . -name "*~" -delete
	find . -name "*.pyc" -delete
	rm -fr code/__pycache__

include $(ZDECK_HOME)/stylesheets/Makefile.rules
include $(TOPDIR)/stylesheets/Makefile.zdeck.rules
