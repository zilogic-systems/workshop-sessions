TOPDIR = ../
-include ~/.zdeck

ZDECK_HOME ?= /usr/share/zdeck
ZDECK_CLASS = lecture

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

all: slides.html tryout.tar.gz

figures/git-repo.png: EXPORT_WIDTH=800
figures/branch-1.png: EXPORT_WIDTH=800
figures/branch-2.png: EXPORT_WIDTH=800
figures/merged.png: EXPORT_WIDTH=800
figures/bug-fix.png: EXPORT_WIDTH=800
figures/terminology.png: EXPORT_WIDTH=800
figures/merged-2.png: EXPORT_WIDTH=800
figures/merged-3.png: EXPORT_WIDTH=800
slides.html: $(images_png) $(datauris)

tryout.tar.gz:
	make -C git-resources
	GIT_RES_DIR=../../git-resources make -C tryout reset
	tar --gzip -c -f tryout.tar.gz tryout/ex*

install-extra:
	cp tryout.tar.gz $(TOPDIR)/build/git-basics

clean:
	rm -f $(images_png)
	rm -f slides.html

include $(ZDECK_HOME)/stylesheets/Makefile.rules
include $(TOPDIR)/stylesheets/Makefile.zdeck.rules
