TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

all: stack-py-split strlist-py-split strint-py-split slides.html

stack-py-split:
	python $(TOPDIR)/scripts/split.py code/stack.py

strlist-py-split:
	python $(TOPDIR)/scripts/split.py code/strlist.py

strint-py-split:
	python $(TOPDIR)/scripts/split.py code/strint.py

slides.html: $(images_png)

clean:
	rm -f $(images_png)
	rm -f slides.html

include $(TOPDIR)/stylesheets/Makefile.rules
