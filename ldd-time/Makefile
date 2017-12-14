TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

srcpath = code/led-blink-delay.c   \
	  code/led-blink-wq.c      \
	  code/led-blink-wq-param.c      \
	  code/key-scan.c

sources = $(join $(srcpath:%.c=$(basename %)/), $(patsubst %, %,$(notdir $(srcpath))))
full = $(sources:%.c=%.full.datauri)
def = $(sources:%.c=%.def.datauri)
init = $(sources:%.c=%.init.datauri)
exit = $(sources:%.c=%.exit.datauri)
datauris = $(full) $(def) $(init) $(exit)

code/%.datauri: MIMETYPE="text/plain;charset=us-ascii"

all: split slides.html

split:
	for i in $(srcpath);do	python $(TOPDIR)/scripts/split.py $$i; done;

slides.html: $(images_png) $(datauris)

clean:
	rm -f $(images_png) $(datauris) $(dl-files)
	rm -f slides.html

include $(TOPDIR)/stylesheets/Makefile.rules
