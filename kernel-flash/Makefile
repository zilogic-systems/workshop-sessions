TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

all: slides.html

slides.html: $(images_png)

clean:
	rm -f $(images_png)
	rm -f $(datauris)
	rm -f slides.html
	rm -rf code/csum
	rm -rf code/startup
	rm -rf code/syscalls

include $(TOPDIR)/stylesheets/Makefile.rules
