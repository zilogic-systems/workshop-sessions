TOOLCHAIN = /usr/share/gcc-arm-linux
ROOTFS = ~/yp/make/rootfs
DISKIMG = ~/yp/make/disk.img
BDIR = ~/yp/make/bash-4.3

all: disk-image

download:
	cd ~/yp/dl; wget -c http://ftp.gnu.org/gnu/bash/bash-4.3.tar.gz

unpack: download
	mkdir -p ~/yp/make
	cd ~/yp/make; tar -x -f ~/yp/dl/bash-4.3.tar.gz

configure: unpack
	cd $(BDIR); ./configure --prefix=/usr   \
            --host=arm-none-linux-gnueabi       \
            --build=i686-pc-linux-gnu

compile: configure
	cd $(BDIR); make

install-deps: compile
	mkdir -p $(ROOTFS)/lib
	cp $(TOOLCHAIN)/arm-none-linux-gnueabi/libc/lib/libc.so.6 \
	   $(ROOTFS)/lib
	cp $(TOOLCHAIN)/arm-none-linux-gnueabi/libc/lib/libdl.so.2 \
	   $(ROOTFS)/lib
	cp $(TOOLCHAIN)/arm-none-linux-gnueabi/libc/lib/ld-linux.so.3 \
	   $(ROOTFS)/lib

install: install-deps
	cd $(BDIR); make install DESTDIR=$(ROOTFS)
	mkdir -p $(ROOTFS)/bin
	ln -f -s /usr/bin/bash $(ROOTFS)/bin/bash
	ln -f -s /usr/bin/bash $(ROOTFS)/bin/sh


disk-image: install
	mkdir -p $(ROOTFS)/dev $(ROOTFS)/tmp
	genext2fs -b 131072 -d $(ROOTFS) $(DISKIMG)

