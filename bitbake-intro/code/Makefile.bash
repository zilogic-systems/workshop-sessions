ROOTFS = ~/yp/make/rootfs
BDIR = ~/yp/make/bash-4.3

all: install

fetch:
	cd ~/yp/dl; wget -c http://ftp.gnu.org/gnu/bash/bash-4.3.tar.gz

unpack: fetch
	mkdir -p ~/yp/make
	cd ~/yp/make; tar -x -f ~/yp/dl/bash-4.3.tar.gz

configure: unpack
	cd $(BDIR); ./configure --prefix=/usr   \
            --host=arm-none-linux-gnueabi       \
            --build=i686-pc-linux-gnu

compile: configure
	cd $(BDIR); make

install: compile
	cd $(BDIR); make install DESTDIR=$(ROOTFS)
	mkdir -p $(ROOTFS)/bin
	ln -f -s /usr/bin/bash $(ROOTFS)/bin/bash
	ln -f -s /usr/bin/bash $(ROOTFS)/bin/sh
