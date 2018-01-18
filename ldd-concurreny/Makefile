TOPDIR = ../

EXPORT_WIDTH  = 1024

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

srcpath = code/ikey-mutex.c

sources = $(join $(srcpath:%.c=$(basename %)/), $(patsubst %, %,$(notdir $(srcpath))))
full = $(sources:%.c=%.full.datauri)
def = $(sources:%.c=%.def.datauri)
init = $(sources:%.c=%.init.datauri)
exit = $(sources:%.c=%.exit.datauri)
datauris = $(full) $(def) $(init) $(exit)

code/%.datauri: MIMETYPE="text/plain;charset=us-ascii"
cdist/%.tar.gz.datauri: MIMETYPE="application/gzip"

all: split buildtar slides.html

split:
	for i in $(srcpath);do	python $(TOPDIR)/scripts/split.py $$i; done;

slides.html: $(images_png) $(datauris)

buildtar:
	echo $(tar)
	mkdir -p cdist;
	for i in $(srcpath);\
	do mkdir -p cdist/`basename $$i .c`;\
	cp $$i cdist/`basename $$i .c`;\
	echo "obj-m = `basename $$i .c`.o" > cdist/`basename $$i .c`/Makefile;\
	cat code/Makefile.mod >> cdist/`basename $$i .c`/Makefile;\
	tar -czf "cdist/`basename $$i .c`.tar.gz" -Ccdist `basename $$i .c`;done  

clean:
	rm -f $(images_png) $(datauris) $(dl-files) 
	rm -rf cdist
	rm -f slides.html

include $(TOPDIR)/stylesheets/Makefile.rules
