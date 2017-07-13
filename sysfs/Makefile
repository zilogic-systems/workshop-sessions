TOPDIR = ../


images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)
datauris = code/ifconfig.py.datauri \
	   code/disk.py.datauri

code/ifconfig.py.datauri: MIMETYPE = "text/python"
code/disk.py.datauri: MIMETYPE = "text/python"

figures/git-repo.png: EXPORT_WIDTH=800
figures/branch-1.png: EXPORT_WIDTH=800
figures/branch-2.png: EXPORT_WIDTH=800
figures/merged.png: EXPORT_WIDTH=800
figures/bug-fix.png: EXPORT_WIDTH=800

all: slides.html

slides.html: $(images_png) $(datauris)

clean:
	rm -f $(images_png)
	rm -f slides.html
	rm -f $(datauris)

include $(TOPDIR)/stylesheets/Makefile.rules
