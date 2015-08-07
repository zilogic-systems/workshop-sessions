TOPDIR = ../

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

figures/git-repo.png: EXPORT_WIDTH=800
figures/branch-1.png: EXPORT_WIDTH=800
figures/branch-2.png: EXPORT_WIDTH=800
figures/merged.png: EXPORT_WIDTH=800
figures/bug-fix.png: EXPORT_WIDTH=800

all: slides.html $(images_png)

clean:
	rm -f $(images_png)
	rm -f slides.html

include $(TOPDIR)/stylesheets/Makefile.rules
