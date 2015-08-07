TOPDIR = ../

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

figures/git-repo.png: EXPORT_WIDTH=400
figures/branch-1.png: EXPORT_WIDTH=400
figures/branch-2.png: EXPORT_WIDTH=450
figures/merged.png: EXPORT_WIDTH=450

all: slides.html $(images_png)

clean:
	rm -f $(images_png)
	rm -f slides.html

include $(TOPDIR)/stylesheets/Makefile.rules
