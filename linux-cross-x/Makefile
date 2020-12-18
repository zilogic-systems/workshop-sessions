TOPDIR = ../
-include ~/.zdeck

ZDECK_HOME ?= /usr/share/zdeck
ZDECK_CLASS = lecture

images_dia = $(wildcard figures/*.dia)
images_png = $(images_dia:.dia=.png)

all: slides.html

slides.html: $(images_png) $(datauris)

linux-cross-x-resources:
	rm -fr linux-cross-x
	mkdir -p linux-cross-x
	rm -fr tmp
	mkdir -p tmp

	mkdir -p linux-cross-x/a1
	cd tmp/; git clone https://github.com/zilogic-systems/tiny-rootfs.git
	cp -r tmp/tiny-rootfs linux-cross-x/a1
	cp code/config-x86 linux-cross-x/a1/tiny-rootfs

	mkdir -p linux-cross-x/a2
	cp -r tmp/tiny-rootfs linux-cross-x/a2
	cp code/config-x86 linux-cross-x/a2/tiny-rootfs
	cd linux-cross-x/a2/tiny-rootfs; ./mkrootfs.sh config-x86

	mkdir -p linux-cross-x/a3
	cd tmp; git clone https://github.com/macagua/example.java.helloworld.git
	cd tmp/example.java.helloworld; javac HelloWorld/Main.java
	cd tmp/example.java.helloworld; jar cfme Main.jar Manifest.txt HelloWorld.Main HelloWorld/Main.class
	cp tmp/example.java.helloworld/Main.jar linux-cross-x/a3/helloworld.jar

	mkdir -p linux-cross-x/a4
	cp code/helloworld.c linux-cross-x/a4

	mkdir -p linux-cross-x/a5
	cp -r tmp/tiny-rootfs linux-cross-x/a5
	cp code/config-arm linux-cross-x/a5/tiny-rootfs
	cd linux-cross-x/a5/tiny-rootfs; ./mkrootfs.sh config-arm
	cp /usr/bin/qemu-arm-static linux-cross-x/a5/tiny-rootfs/build-arm/rootfs/usr/bin

clean:
	rm -f $(images_png)
	rm -fr linux-cross-x
	rm -fr tmp
	rm -f slides.html

include $(ZDECK_HOME)/stylesheets/Makefile.rules
include $(TOPDIR)/stylesheets/Makefile.zdeck.rules
