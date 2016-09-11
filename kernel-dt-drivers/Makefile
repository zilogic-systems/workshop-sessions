TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)
datauris = code/rtc-raw.c.datauri \
	   code/rtc-device.c.datauri \
	   code/rtc-driver.c.datauri \
	   code/rtc-of-driver.c.datauri

code/rtc-raw.c.datauri: MIMETYPE="text/plain;charset=us-ascii"
code/rtc-device.c.datauri: MIMETYPE="text/plain;charset=us-ascii"
code/rtc-driver.c.datauri: MIMETYPE="text/plain;charset=us-ascii"
code/rtc-of-driver.c.datauri: MIMETYPE="text/plain;charset=us-ascii"

all: slides.html

slides.html: $(images_png) $(datauris)

clean:
	rm -f $(images_png)
	rm -f $(datauris)
	rm -f slides.html

include $(TOPDIR)/stylesheets/Makefile.rules
