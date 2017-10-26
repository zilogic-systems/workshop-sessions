TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)
usr_dia = $(sort $(wildcard figures/uart-shift-register-*.dia))
register_images = $(usr_dia:.dia=.png)
serialgif = figures/uart-shift-register.gif

all: slides.html

slides.html: $(images_png) serialgif

serialgif:
	convert -delay 100 $(register_images) figures/uart-shift-register.gif

clean:
	rm -f $(images_png)
	rm -f $(serialgif)
	rm -f slides.html
	rm -fr code/simple

include $(TOPDIR)/stylesheets/Makefile.rules
