TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

datauris = code/led.c.datauri         \
	   code/led-blink.c.datauri   \
	   code/led-chcolor.c.datauri \
	   code/gpio.c.datauri        \
	   code/key.c.datauri         \
           code/key-debounce.c.datauri\
           code/key-status.c.datauri

dl-files = figures/pir.jpg 		\
	   figures/reed-switch.jpg	\
	   figures/smoke-sensor.jpg 	\
	   figures/solenoid-valve.jpg 	\
	   figures/relay.jpg

code/%.datauri: MIMETYPE="text/plain;charset=us-ascii"

all: slides.html

slides.html: $(images_png) #$(datauris)

clean:
	rm -f $(images_png) $(datauris) $(dl-files)
	rm -f slides.html

include $(TOPDIR)/stylesheets/Makefile.rules
