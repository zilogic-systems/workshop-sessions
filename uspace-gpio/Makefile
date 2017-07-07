TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

datauris = code/led.py.datauri         \
	   code/led-blink.py.datauri   \
	   code/led-chcolor.py.datauri \
	   code/gpio.py.datauri        \
	   code/key.py.datauri         \
           code/key-debounce.py.datauri\
           code/key-status.py.datauri

code/%.datauri: MIMETYPE="text/plain;charset=us-ascii"

all: slides.html

slides.html: $(images_png) $(datauris)

clean:
	rm -f $(images_png) $(datauris)
	rm -f slides.html

include $(TOPDIR)/stylesheets/Makefile.rules
