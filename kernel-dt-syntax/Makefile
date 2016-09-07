TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)
datauris = code/planets-v1.dts.datauri  \
	   code/planets-v2/full.datauri \
           code/inner.dtsi.datauri      \
           code/planets-v3.dts.datauri  \
           code/planets-v4.dts.datauri  \
	   code/planets-v5.dts.datauri  \
	   code/planets-v6.dts.datauri  \
	   code/planets-v7.dts.datauri  \
           code/simple-v7.dts.datauri

all: planets-v2-dts-split planets-v8-dts-split slides.html

planets-v2-dts-split:
	python $(TOPDIR)/scripts/split.py code/planets-v2.dts

planets-v8-dts-split:
	python $(TOPDIR)/scripts/split.py code/planets-v8.dts

code/planets-v1.dts.datauri: MIMETYPE="text/plain;charset=us-ascii"
code/planets-v2/full.datauri: MIMETYPE="text/plain;charset=us-ascii"
code/inner.dtsi.datauri: MIMETYPE="text/plain;charset=us-ascii"
code/planets-v3.dts.datauri: MIMETYPE="text/plain;charset=us-ascii"
code/planets-v4.dts.datauri: MIMETYPE="text/plain;charset=us-ascii"
code/planets-v5.dts.datauri: MIMETYPE="text/plain;charset=us-ascii"
code/planets-v6.dts.datauri: MIMETYPE="text/plain;charset=us-ascii"
code/planets-v7.dts.datauri: MIMETYPE="text/plain;charset=us-ascii"
code/simple-v7.dts.datauri: MIMETYPE="text/plain;charset=us-ascii"

slides.html: $(images_png) $(photos) $(datauris)

clean:
	rm -f $(images_png)
	rm -f $(datauris)
	rm -fr code/planets-v2
	rm -f slides.html

include $(TOPDIR)/stylesheets/Makefile.rules
