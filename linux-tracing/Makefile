TOPDIR = ../
-include ~/.zdeck

ZDECK_HOME ?= /usr/share/zdeck
ZDECK_CLASS = lecture

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

all: slides.html

slides.html: $(images_png) $(datauris)

linux-tracing-resources:
	mkdir -p linux-tracing
	mkdir -p linux-tracing/a1
	cp code/fibonacci.c linux-tracing/a1
	echo 'CFLAGS = "-pg"' > linux-tracing/a1/Makefile
	echo 'all: fibonacci' >> linux-tracing/a1/Makefile
	cp code/libprof.so linux-tracing/a1
	mkdir -p linux-tracing/b1
	cp code/foobar.c linux-tracing/b1
	echo 'CFLAGS = "-pg"' > linux-tracing/b1/Makefile
	echo 'all: foobar' >> linux-tracing/b1/Makefile
	mkdir -p linux-tracing/b2
	cp code/foobar.c linux-tracing/b2
	echo 'CFLAGS = "-pg"' > linux-tracing/b2/Makefile
	echo 'all: foobar' >> linux-tracing/b2/Makefile
	mkdir -p linux-tracing/b3
	cp code/lfoobar.c linux-tracing/b3
	echo 'CFLAGS = "-pg"' > linux-tracing/b3/Makefile
	echo 'all: lfoobar' >> linux-tracing/b3/Makefile
	mkdir -p linux-tracing/b4
	cp code/new-delete.cpp linux-tracing/b4
	echo 'CXXFLAGS = "-pg"' > linux-tracing/b4/Makefile
	echo 'all: new-delete' >> linux-tracing/b4/Makefile
	mkdir -p linux-tracing/b5
	cp code/new-delete.cpp linux-tracing/b5
	echo 'CXXFLAGS = "-pg"' > linux-tracing/b5/Makefile
	echo 'all: new-delete' >> linux-tracing/b5/Makefile
	mkdir -p linux-tracing/b6
	cp code/sleeptest.c linux-tracing/b6
	echo 'CFLAGS = "-pg"' > linux-tracing/b6/Makefile
	echo 'all: sleeptest' >> linux-tracing/b6/Makefile
	mkdir -p linux-tracing/b7
	cp code/sleeptest.c linux-tracing/b7
	echo 'CFLAGS = "-pg"' > linux-tracing/b7/Makefile
	echo 'all: sleeptest' >> linux-tracing/b7/Makefile
	mkdir -p linux-tracing/b8
	cp code/hello.c linux-tracing/b8
	echo 'CFLAGS = "-g -pg"' > linux-tracing/b8/Makefile
	echo 'all: hello' >> linux-tracing/b8/Makefile
	mkdir -p linux-tracing/b9
	cp code/foobar.c linux-tracing/b9
	echo 'all: foobar' >> linux-tracing/b9/Makefile
	mkdir -p linux-tracing/b10
	cp code/fibonacci.c linux-tracing/b10
	echo 'CFLAGS = "-pg"' > linux-tracing/b10/Makefile
	echo 'all: fibonacci' >> linux-tracing/b10/Makefile
	mkdir -p linux-tracing/b11
	cp code/hello.c linux-tracing/b11

clean:
	rm -f $(images_png)
	rm -f slides.html

include $(ZDECK_HOME)/stylesheets/Makefile.rules
include $(TOPDIR)/stylesheets/Makefile.zdeck.rules
