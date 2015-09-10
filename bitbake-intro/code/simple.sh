#!/bin/bash

set -e -x -u

cd ~/yp/dl
wget -c http://git.openembedded.org/bitbake/snapshot/bitbake-1.17.0.tar.gz

mkdir -p ~/yp/bitbake
cd ~/yp/bitbake
tar -x -f ~/yp/dl/bitbake-1.17.0.tar.gz
cd bitbake-1.17.0
python setup.py build

cd ~/yp/bitbake/bitbake-1.17.0/build/scripts*
export PATH=$PWD:$PATH

set +u
cd ~/yp/bitbake/bitbake-1.17.0/build/lib*
export PYTHONPATH=$PWD:$PYTHONPATH
set -u

mkdir -p ~/yp/simple
mkdir -p ~/yp/simple/conf
mkdir -p ~/yp/simple/classes

cat > ~/yp/simple/conf/bitbake.conf <<"EOF"
TMPDIR = "${TOPDIR}/tmp"
CACHE = "${TMPDIR}/cache"
STAMP = "${TMPDIR}/stamps/"
T = "${TMPDIR}/work"
B = "${TMPDIR}"
EOF

touch ~/yp/simple/classes/base.bbclass

cat > ~/yp/simple/bash.bb <<EOF
PN = "bash"

do_unpack() {
        tar -x -f ~/yp/dl/bash-4.3.tar.gz
}
addtask unpack
EOF

export BBPATH=~/yp/simple

cd ~/yp/simple
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

do_install_deps() { 
	mkdir -p ${ROOTFS}/lib
	cp ${TOOLCHAIN}/arm-none-linux-gnueabi/libc/lib/libc.so.6 \
	   ${ROOTFS}/lib
	cp ${TOOLCHAIN}/arm-none-linux-gnueabi/libc/lib/libdl.so.2 \
	   ${ROOTFS}/lib
	cp ${TOOLCHAIN}/arm-none-linux-gnueabi/libc/lib/ld-linux.so.3 \
	   ${ROOTFS}/lib
}
addtask install_deps after do_compile

do_install() {
	cd $BDIR; make install DESTDIR=${ROOTFS}
	mkdir -p ${ROOTFS}/bin
	ln -f -s /usr/bin/bash ${ROOTFS}/bin/bash
	ln -f -s /usr/bin/bash ${ROOTFS}/bin/sh
}
addtask install after do_install_deps

do_disk_image() {
	mkdir -p ${ROOTFS}/dev ${ROOTFS}/tmp
	genext2fs -b 131072 -d ${ROOTFS} ${DISKIMG}
}
addtask disk_image after do_install
EOF

cd ~/yp/simple
bitbake -c disk_image bash
ls ~/yp/simple/tmp/rootfs

qemu-system-arm                 \
  -M versatilepb                \
  -kernel ~/yp/pre-built/zImage \
  -append "root=/dev/sda rw"    \
  -hda ~/yp/simple/tmp/disk.img