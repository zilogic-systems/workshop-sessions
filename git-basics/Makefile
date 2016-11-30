TOPDIR = ../

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

all: slides.html

slides.html: $(images_png)

figures/git-repo.png: EXPORT_WIDTH=800
figures/branch-1.png: EXPORT_WIDTH=800
figures/branch-2.png: EXPORT_WIDTH=800
figures/merged.png: EXPORT_WIDTH=800
figures/bug-fix.png: EXPORT_WIDTH=800
figures/terminology.png: EXPORT_WIDTH=800

clean:
	rm -f $(images_png)
	rm -f slides.html

include $(TOPDIR)/stylesheets/Makefile.rules
