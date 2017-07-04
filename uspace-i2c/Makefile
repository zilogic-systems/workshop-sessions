TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)
datauris   = code/smbus.py.datauri \
	     code/accelerometer.py.datauri

all: slides.html

slides.html: $(images_png) $(datauris)
code/smbus.py.datauri: MIMETYPE="text/plain;charset=us-ascii"
code/accelerometer.py.datauri: MIMETYPE="text/plain;charset=us-ascii"

clean:
	rm -f $(images_png)
	rm -f $(datauris)
	rm -f slides.html
	rm -fr code/simple

include $(TOPDIR)/stylesheets/Makefile.rules
