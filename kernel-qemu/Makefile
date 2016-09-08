TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)
photos = figures/gumstix.jpg

all: slides.html

figures/gumstix.jpg:
	wget -O $@ 'https://upload.wikimedia.org/wikipedia/commons/thumb/9/91/Gumstix.agr.jpg/1280px-Gumstix.agr.jpg'

slides.html: $(images_png) $(photos)

clean:
	rm -f $(images_png)
	rm -f $(photos)
	rm -f slides.html

include $(TOPDIR)/stylesheets/Makefile.rules
