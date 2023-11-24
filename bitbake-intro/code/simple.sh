#!/bin/bash

set -e -x -u

source sandwich.sh

### START: bbsetup.sh
cd ~/yp/sandwich
source setup-bitbake.sh
### END: bbsetup.sh

### START: bbpath.sh
export BBPATH=~/yp/sandwich
### END: bbpath.sh

cd ~/yp/sandwich
rm -fr tmp
### START: run-get.sh
bitbake -c get bread
cat ~/yp/sandwich/tmp/bread.txt
### END: run-get.sh

bitbake -c cook bread
cat ~/yp/sandwich/tmp/bread.txt

cat > ~/yp/sandwich/bread.bb <<"EOF"
PN = "bread"

do_get() {
        echo ${PN}: wheat > ${TMPDIR}/bread.txt
        echo ${PN}: salt  >> ${TMPDIR}/bread.txt
        echo ${PN}: sugar >> ${TMPDIR}/bread.txt
        echo ${PN}: water >> ${TMPDIR}/bread.txt
        sleep 1
}
addtask get

do_cook() {
        echo "${PN}: bake for 20 - 25 minutes" >> ${TMPDIR}/bread.txt
        sleep 2
        echo "${PN}: ready" >> ${TMPDIR}/bread.txt
}
addtask cook after do_get
EOF

cd ~/yp/sandwich
rm -fr tmp
bitbake -c cook bread
cat ~/yp/sandwich/tmp/bread.txt

cat > ~/yp/sandwich/omelet.bb <<"EOF"
### START: omelet.bb
PN = "omelet"

do_get() {
        echo ${PN}: egg > ${TMPDIR}/omelet.txt
        echo ${PN}: pepper  >> ${TMPDIR}/omelet.txt
        sleep 1
}
addtask get

do_cook() {
        echo ${PN}: fry >> ${TMPDIR}/omelet.txt
        sleep 2
        echo ${PN}: ready >> ${TMPDIR}/omelet.txt
}
addtask cook after do_get
### END: omelet.bb
EOF

cd ~/yp/sandwich
rm -fr tmp
bitbake -c cook omelet
cat ~/yp/sandwich/tmp/omelet.txt

cat > ~/yp/sandwich/sandwich.bb <<"EOF"
### START: sandwich.bb
PN = "sandwich"

do_get() {
        cat bread.txt > ${TMPDIR}/sandwich.txt
        cat omelet.txt  >> ${TMPDIR}/sandwich.txt
        sleep 1
}
addtask get

do_cook() {
        echo "${PN}: toast bread and serve" >> ${TMPDIR}/sandwich.txt
        sleep 2
        echo "${PN}: ready" >> ${TMPDIR}/sandwich.txt
}
addtask cook after do_get
### END: sandwich.bb
EOF

set +e
cd ~/yp/sandwich
rm -fr tmp
bitbake -c cook sandwich
set -e

cat > ~/yp/sandwich/sandwich.bb <<"EOF"
PN = "sandwich"

DEPENDS = "bread omelet"
do_get[deptask] = "do_cook"

do_get() {
        cat bread.txt > ${TMPDIR}/sandwich.txt
        cat omelet.txt  >> ${TMPDIR}/sandwich.txt
        sleep 1
}
addtask get

do_cook() {
        echo "${PN}: toast bread and serve" >> ${TMPDIR}/sandwich.txt
        sleep 2
        echo "${PN}: ready" >> ${TMPDIR}/sandwich.txt
}
addtask cook after do_get
EOF

cd ~/yp/sandwich
rm -fr tmp
bitbake -c cook sandwich
cat ~/yp/sandwich/tmp/sandwich.txt

#
# Discuss BB_NUMBER_THREADS
# Discuss base.bbclass
#
#
# Give recipes for bash, coreutils, image,
# Simplify recipes using autotools class
# Ask student to add recipe for libncurses
# Ask student to add recipe for less
#

cat > ~/yp/simple/bash.bb <<EOF
PN = "bash"

do_download() {
        cd ~/yp/dl; wget -c http://ftp.gnu.org/gnu/bash/bash-4.3.tar.gz
}
addtask download

do_unpack() {
        tar -x -f ~/yp/dl/bash-4.3.tar.gz
}
addtask unpack after do_download
EOF

cd ~/yp/simple
rm -fr tmp
bitbake -c download bash
bitbake -c unpack bash
ls ~/yp/simple/tmp/

cat > ~/yp/simple/bash.bb <<"EOF"
PN = "bash"
TOOLCHAIN = "/usr/share/gcc-arm-linux"
ROOTFS = "~/yp/simple/tmp/rootfs"
DISKIMG = "~/yp/simple/tmp/disk.img"

do_download() {
	cd ~/yp/dl; wget -c http://ftp.gnu.org/gnu/bash/bash-4.3.tar.gz
}
addtask download

do_unpack() {
	tar -x -f ~/yp/dl/bash-4.3.tar.gz
}
addtask unpack after do_download

do_configure() {
	cd bash-4.3
        ./configure --prefix=/usr           \
            --host=arm-none-linux-gnueabi   \
            --build=i686-pc-linux-gnu
}
addtask configure after do_unpack

do_compile() {
	cd bash-4.3
        make
}
addtask compile after do_configure

do_install() {
	cd bash-4.3
        make install DESTDIR=${ROOTFS}
	mkdir -p ${ROOTFS}/bin
	ln -f -s /usr/bin/bash ${ROOTFS}/bin/bash
	ln -f -s /usr/bin/bash ${ROOTFS}/bin/sh
}
addtask install after do_compile

do_rootfs() {
	mkdir -p ${ROOTFS}/lib
	cp ${TOOLCHAIN}/arm-none-linux-gnueabi/libc/lib/libc.so.6 \
	   ${ROOTFS}/lib
	cp ${TOOLCHAIN}/arm-none-linux-gnueabi/libc/lib/libdl.so.2 \
	   ${ROOTFS}/lib
	cp ${TOOLCHAIN}/arm-none-linux-gnueabi/libc/lib/ld-linux.so.3 \
	   ${ROOTFS}/lib

	mkdir -p ${ROOTFS}/dev ${ROOTFS}/tmp
	genext2fs -b 131072 -d ${ROOTFS} ${DISKIMG}
}
addtask rootfs after do_install
EOF

cd ~/yp/simple
rm -fr tmp
bitbake -c rootfs bash
ls ~/yp/simple/tmp/rootfs

qemu-system-arm                 \
  -M versatilepb                \
  -kernel ~/yp/pre-built/zImage \
  -append "root=/dev/sda rw"    \
  -hda ~/yp/simple/tmp/disk.img

cat >> ~/yp/simple/conf/bitbake.conf <<"EOF"
TOOLCHAIN = "/usr/share/gcc-arm-linux"
ROOTFS = "~/yp/simple/tmp/rootfs"
DISKIMG = "~/yp/simple/tmp/disk.img"
EOF

cat > ~/yp/simple/bash.bb <<"EOF"
do_download() {
	cd ~/yp/dl; wget -c http://ftp.gnu.org/gnu/bash/bash-4.3.tar.gz
}
addtask download

do_unpack() {
	tar -x -f ~/yp/dl/bash-4.3.tar.gz
}
addtask unpack after do_download

do_configure() {
	cd bash-4.3
        ./configure --prefix=/usr           \
            --host=arm-none-linux-gnueabi   \
            --build=i686-pc-linux-gnu
}
addtask configure after do_unpack

do_compile() {
	cd bash-4.3
        make
}
addtask compile after do_configure

do_install() {
	cd bash-4.3
        make install DESTDIR=${ROOTFS}
	mkdir -p ${ROOTFS}/bin
	ln -f -s /usr/bin/bash ${ROOTFS}/bin/bash
	ln -f -s /usr/bin/bash ${ROOTFS}/bin/sh
}
addtask install after do_compile
EOF

cat > ~/yp/simple/image.bb <<"EOF"
DEPENDS = "bash"

do_rootfs() {
	mkdir -p ${ROOTFS}/dev ${ROOTFS}/tmp
	mkdir -p ${ROOTFS}/lib
	cp ${TOOLCHAIN}/arm-none-linux-gnueabi/libc/lib/libc.so.6 \
	   ${ROOTFS}/lib
	cp ${TOOLCHAIN}/arm-none-linux-gnueabi/libc/lib/libdl.so.2 \
	   ${ROOTFS}/lib
	cp ${TOOLCHAIN}/arm-none-linux-gnueabi/libc/lib/ld-linux.so.3 \
	   ${ROOTFS}/lib

	genext2fs -b 131072 -d ${ROOTFS} ${DISKIMG}
}
addtask rootfs
EOF



cat > ~/yp/simple/classes/autotools.class <<"EOF"
do_download() {
	cd ~/yp/dl
	wget -c ${SRC_URI}
}
addtask download

do_unpack() {
	tar -x -f ~/yp/dl/${PN}-${PV}.tar.bz2
}
addtask unpack after do_download

do_configure() {
	cd ${PN}-${PV}
        ./configure --prefix=/usr           \
            --host=arm-none-linux-gnueabi   \
            --build=i686-pc-linux-gnu
}
addtask configure after do_unpack

do_compile() {
	cd ${PN}-${PV}
        make
}
addtask compile after do_configure

do_install() {
	cd bash-4.3
        make install DESTDIR=${ROOTFS}
	mkdir -p ${ROOTFS}/bin
	ln -f -s /usr/bin/bash ${ROOTFS}/bin/bash
	ln -f -s /usr/bin/bash ${ROOTFS}/bin/sh
}
addtask install after do_compile

do_rootfs() {
	mkdir -p ${ROOTFS}/dev ${ROOTFS}/tmp
	genext2fs -b 131072 -d ${ROOTFS} ${DISKIMG}
}
addtask rootfs after do_install
EOF

cat > ~/yp/simple/bash.bb <<"EOF"
PN = "bash"

do_download() {
	cd ~/yp/dl; wget -c http://ftp.gnu.org/gnu/bash/bash-4.3.tar.gz
}
addtask download

do_unpack() {
	tar -x -f ~/yp/dl/bash-4.3.tar.gz
}
addtask unpack after do_download

do_configure() {
	cd bash-4.3
        ./configure --prefix=/usr           \
            --host=arm-none-linux-gnueabi   \
            --build=i686-pc-linux-gnu
}
addtask configure after do_unpack

do_compile() {
	cd bash-4.3
        make
}
addtask compile after do_configure

do_install() {
	cd bash-4.3
        make install DESTDIR=${ROOTFS}
	mkdir -p ${ROOTFS}/bin
	ln -f -s /usr/bin/bash ${ROOTFS}/bin/bash
	ln -f -s /usr/bin/bash ${ROOTFS}/bin/sh

	mkdir -p ${ROOTFS}/lib
	cp ${TOOLCHAIN}/arm-none-linux-gnueabi/libc/lib/libc.so.6 \
	   ${ROOTFS}/lib
	cp ${TOOLCHAIN}/arm-none-linux-gnueabi/libc/lib/libdl.so.2 \
	   ${ROOTFS}/lib
	cp ${TOOLCHAIN}/arm-none-linux-gnueabi/libc/lib/ld-linux.so.3 \
	   ${ROOTFS}/lib
}
addtask install after do_compile

do_rootfs() {
	mkdir -p ${ROOTFS}/dev ${ROOTFS}/tmp
	genext2fs -b 131072 -d ${ROOTFS} ${DISKIMG}
}
addtask rootfs after do_install
EOF
