#!/bin/bash

set -e -x -u

SHARED=~/yp/shared

cd $SHARED
cat <<EOF > run-qemu.sh
### START: boot-prebuilt.sh
qemu-system-arm -M versatilepb \
                -hda disk.img  \
		-kernel zImage \
                -dtb versatile-pb.dtb \
		-append "root=/dev/sda rw"
### END: boot-prebuilt.sh
EOF

### START: copy-prebuilt.sh
cp ~/yp/pre-built/zImage $SHARED
cp ~/yp/pre-built/disk.img $SHARED
cp ~/yp/pre-built/versatile-pb.dtb $SHARED
### END: copy-prebuilt.sh

### START: run-qemu.sh
cd $SHARED
bash run-qemu.sh
### END: run-qemu.sh

### START: setup-env.sh
ROOTFS=~/yp/manual/rootfs
DISKIMG=~/yp/manual/disk.img
### END: setup-env.sh

cat > ~/yp/manual/hello.c <<EOF
/* ### START: hello.c */
#include <stdio.h>
#include <unistd.h>

int main()
{
    while (1) {
        printf("Hello World\n");
	sleep(1);
    }
}
/* ### END: hello.c */
EOF

### START: build-hello.sh
cd ~/yp/manual
arm-linux-gnueabi-gcc -static hello.c -o hello
### END: build-hello.sh

### START: copy-hello.sh
mkdir -p $ROOTFS/bin
cp hello $ROOTFS/bin/sh
### END: copy-hello.sh

### START: create-hello-rootfs.sh
genext2fs -b 131072 -d $ROOTFS $DISKIMG
### END: create-hello-rootfs.sh

cp $DISKIMG $SHARED

### START: boot-hello-rootfs.sh
cd $SHARED
bash run-qemu.sh
### END: boot-hello-rootfs.sh

### START: download-bash.sh
cd ~/yp/dl
wget -c http://ftp.gnu.org/gnu/bash/bash-4.3.tar.gz
### END: download-bash.sh

### START: unpack-bash.sh
cd ~/yp/manual
tar -x -f ~/yp/dl/bash-4.3.tar.gz
### END: unpack-bash.sh

### START: configure-bash.sh
cd bash-4.3
./configure --prefix=/usr                \
            --host=arm-linux-gnueabi \
            --build=i686-pc-linux-gnu
### END: configure-bash.sh

### START: build-bash.sh
make
### END: build-bash.sh

### START: install-bash.sh
make install DESTDIR=$ROOTFS
### END: install-bash.sh

### START: check-bash-deps.sh
arm-linux-gnueabi-readelf -d $ROOTFS/usr/bin/bash
### END: check-bash-deps.sh

rm -f $ROOTFS/bin/sh

### START: link-bash.sh
ln -s /usr/bin/bash $ROOTFS/bin/bash
ln -s /usr/bin/bash $ROOTFS/bin/sh
### END: link-bash.sh

### START: cp-bash-deps.sh
mkdir $ROOTFS/lib
TOOLCHAIN="/usr/arm-linux-gnueabi"
cp $TOOLCHAIN/lib/libc.so.6 \
   $ROOTFS/lib
cp $TOOLCHAIN/lib/libdl.so.2 \
   $ROOTFS/lib
### END: cp-bash-deps.sh

### START: copy-ld.sh
cp $TOOLCHAIN/lib/ld-linux.so.3 \
   $ROOTFS/lib
### END: copy-ld.sh

### START: make-dev-tmp.sh
mkdir $ROOTFS/dev $ROOTFS/tmp
### END: make-dev-tmp.sh

### START: create-bash-rootfs.sh
genext2fs -b 131072 -d $ROOTFS $DISKIMG
### END: create-bash-rootfs.sh

cp $DISKIMG $SHARED

### START: boot-bash-rootfs.sh
cd $SHARED
bash run-qemu.sh
### END: boot-bash-rootfs.sh

### START: build-coreutils.sh
cd ~/yp/dl
wget -c http://ftp.gnu.org/gnu/coreutils/coreutils-8.32.tar.xz
cd ~/yp/manual
tar -x -f ~/yp/dl/coreutils-8.32.tar.xz
cd coreutils-8.32
./configure --prefix=/usr                 \
            --host=arm-linux-gnueabi \
            --build=i686-pc-linux-gnu
make
make install DESTDIR=$ROOTFS
### END: build-coreutils.sh

### START: create-ls-rootfs.sh
genext2fs -b 131072 -d $ROOTFS $DISKIMG
### END: create-ls-rootfs.sh

cp $DISKIMG $SHARED

cd $SHARED
bash run-qemu.sh

### START: check-ls-deps.sh
arm-linux-gnueabi-readelf -d $ROOTFS/usr/bin/ls
### END: check-ls-deps.sh

cp $TOOLCHAIN/lib/librt.so.1 \
   $ROOTFS/lib

genext2fs -b 131072 -d $ROOTFS $DISKIMG

qemu-system-arm                 \
  -M versatilepb                \
  -kernel ~/yp/pre-built/zImage \
  -append "root=/dev/sda rw"    \
  -dtb versatile-pb.dtb         \
  -hda $DISKIMG

cp $TOOLCHAIN/lib/libpthread.so.0 \
   $ROOTFS/lib

genext2fs -b 131072 -d $ROOTFS $DISKIMG

qemu-system-arm                 \
  -M versatilepb                \
  -kernel ~/yp/pre-built/zImage \
  -append "root=/dev/sda rw"    \
  -dtb versatile-pb.dtb         \
  -hda $DISKIMG


set +e
### START: build-less-fail.sh
cd ~/yp/dl
wget -c http://www.greenwoodsoftware.com/less/less-458.tar.gz
cd ~/yp/manual
tar -x -f ~/yp/dl/less-458.tar.gz
cd less-458
./configure --prefix=/usr                 \
            --host=arm-linux-gnueabi \
            --build=i686-pc-linux-gnu
### END: build-less-fail.sh
set -e

### START: build-ncurses.sh
cd ~/yp/dl
wget -c http://ftp.gnu.org/gnu/ncurses/ncurses-6.2.tar.gz
cd ~/yp/manual
tar -x -f ~/yp/dl/ncurses-6.2.tar.gz
cd ncurses-6.2
./configure --prefix=/usr             \
            --host=arm-linux-gnueabi  \
            --build=i686-pc-linux-gnu \
	    --without-progs           \
	    --disable-ext-funcs
make
make install DESTDIR=$ROOTFS
### END: build-ncurses.sh

set +e
### START: build-less-fail-2.sh
cd ~/yp/manual/less-458
./configure --prefix=/usr                 \
            --host=arm-linux-gnueabi \
            --build=i686-pc-linux-gnu
### END: build-less-fail-2.sh
set -e

cat > ~/yp/manual/hello-ncurses.c <<EOF
/* ### START: hello-ncurses.c */
#include <ncurses.h>

int main()
{
    initscr();
    printw("Hello World!");
    refresh();
    getch();
    endwin();
    return 0;
}
/* ### END: hello-ncurses.c */
EOF

set +e

### START: build-hello-ncurses.sh
cd ~/yp/manual
arm-linux-gnueabi-gcc hello-ncurses.c -o hello-ncurses
### END: build-hello-ncurses.sh

set -e

### START: check-ncurses-location.sh
ls $ROOTFS/usr/include
ls $ROOTFS/usr/lib
### END: check-ncurses-location.sh

### START: build-hello-ncurses-2.sh
arm-linux-gnueabi-gcc hello-ncurses.c \
    -I $ROOTFS/usr/include             \
    -L $ROOTFS/usr/lib                 \
    -lncurses
### END: build-hello-ncurses-2.sh

### START: build-less.sh
cd ~/yp/manual/less-458
./configure --prefix=/usr                 \
            --host=arm-linux-gnueabi \
            --build=i686-pc-linux-gnu     \
            LDFLAGS="-L $ROOTFS/usr/lib"  \
            CPPFLAGS="-I $ROOTFS/usr/inxclude"
make
make install DESTDIR=$ROOTFS
### END: build-less.sh

genext2fs -b 131072 -d $ROOTFS $DISKIMG

cd $SHARED

qemu-system-arm                 \
  -M versatilepb                \
  -kernel ~/yp/pre-built/zImage \
  -append "root=/dev/sda rw"    \
  -dtb versatile-pb.dtb         \
  -hda $DISKIMG
