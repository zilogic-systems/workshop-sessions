TOPDIR = ../
-include ~/.zdeck

ZDECK_HOME ?= /usr/share/zdeck
ZDECK_CLASS = lecture

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

all: code/versions.sh slides.html

slides.html: code/versions.adoc $(images_png)

code/versions.sh code/versions.adoc: versions.yaml $(TOPDIR)/scripts/gen-versions.py
	mkdir -p $(@D)
	python3 $(TOPDIR)/scripts/gen-versions.py versions.yaml $@

clean:
	rm -f $(images_png)
	rm -f slides.html
	rm -fr code/zepto
	rm -f code/versions.sh code/versions.adoc

include $(ZDECK_HOME)/stylesheets/Makefile.rules
include $(TOPDIR)/stylesheets/Makefile.zdeck.rules
