#!/bin/bash

set -e -x -u

SHARED=~/mr/shared

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
cp ~/mr/pre-built/zImage $SHARED
cp ~/mr/pre-built/disk.img $SHARED
cp ~/mr/pre-built/versatile-pb.dtb $SHARED
### END: copy-prebuilt.sh

### START: run-qemu.sh
cd $SHARED
bash run-qemu.sh
### END: run-qemu.sh

### START: setup-env.sh
ROOTFS=~/mr/manual/rootfs
DISKIMG=~/mr/manual/disk.img
### END: setup-env.sh

cat > ~/mr/manual/hello.c <<EOF
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
cd ~/mr/manual
arm-linux-gnueabi-gcc -static hello.c -o hello
### END: build-hello.sh

### START: copy-hello.sh
mkdir -p ~/mr/manual/rootfs/bin
cp hello ~/mr/manual/rootfs/bin/sh
### END: copy-hello.sh

### START: create-hello-rootfs.sh
genext2fs -b 131072 -d ~/mr/manual/rootfs ~/mr/manual/disk.img
### END: create-hello-rootfs.sh

cp ~/mr/manual/disk.img $SHARED

### START: boot-hello-rootfs.sh
cd $SHARED
bash run-qemu.sh
### END: boot-hello-rootfs.sh

### START: download-bash.sh
cd ~/mr/dl
wget -c http://ftp.gnu.org/gnu/bash/bash-4.3.tar.gz
### END: download-bash.sh

### START: unpack-bash.sh
cd ~/mr/manual
tar -x -f ~/mr/dl/bash-4.3.tar.gz
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
make install DESTDIR=~/mr/manual/rootfs
### END: install-bash.sh

### START: check-bash-deps.sh
arm-linux-gnueabi-readelf -d ~/mr/manual/rootfs/usr/bin/bash
### END: check-bash-deps.sh

rm -f ~/mr/manual/rootfs/bin/sh

### START: link-bash.sh
ln -s /usr/bin/bash ~/mr/manual/rootfs/bin/bash
ln -s /usr/bin/bash ~/mr/manual/rootfs/bin/sh
### END: link-bash.sh

### START: cp-bash-deps.sh
mkdir ~/mr/manual/rootfs/lib
TOOLCHAIN="/usr/arm-linux-gnueabi"
cp $TOOLCHAIN/lib/libc.so.6 \
   ~/mr/manual/rootfs/lib
cp $TOOLCHAIN/lib/libdl.so.2 \
   ~/mr/manual/rootfs/lib
### END: cp-bash-deps.sh

### START: copy-ld.sh
cp $TOOLCHAIN/lib/ld-linux.so.3 \
   ~/mr/manual/rootfs/lib
### END: copy-ld.sh

### START: make-dev-tmp.sh
mkdir ~/mr/manual/rootfs/dev ~/mr/manual/rootfs/tmp
### END: make-dev-tmp.sh

### START: create-bash-rootfs.sh
genext2fs -b 131072 -d ~/mr/manual/rootfs ~/mr/manual/disk.img
### END: create-bash-rootfs.sh

cp ~/mr/manual/disk.img $SHARED

### START: boot-bash-rootfs.sh
cd $SHARED
bash run-qemu.sh
### END: boot-bash-rootfs.sh

### START: build-coreutils.sh
cd ~/mr/dl
wget -c http://ftp.gnu.org/gnu/coreutils/coreutils-8.32.tar.xz
cd ~/mr/manual
tar -x -f ~/mr/dl/coreutils-8.32.tar.xz
cd coreutils-8.32
./configure --prefix=/usr                 \
            --host=arm-linux-gnueabi \
            --build=i686-pc-linux-gnu
make
make install DESTDIR=~/mr/manual/rootfs
### END: build-coreutils.sh

### START: create-ls-rootfs.sh
genext2fs -b 131072 -d ~/mr/manual/rootfs ~/mr/manual/disk.img
### END: create-ls-rootfs.sh

cp ~/mr/manual/disk.img $SHARED

cd $SHARED
bash run-qemu.sh

### START: check-ls-deps.sh
arm-linux-gnueabi-readelf -d ~/mr/manual/rootfs/usr/bin/ls
### END: check-ls-deps.sh

cp $TOOLCHAIN/lib/librt.so.1 \
   ~/mr/manual/rootfs/lib

genext2fs -b 131072 -d ~/mr/manual/rootfs ~/mr/manual/disk.img

qemu-system-arm                 \
  -M versatilepb                \
  -kernel ~/mr/pre-built/zImage \
  -append "root=/dev/sda rw"    \
  -dtb versatile-pb.dtb         \
  -hda ~/mr/manual/disk.img

cp $TOOLCHAIN/lib/libpthread.so.0 \
   ~/mr/manual/rootfs/lib

genext2fs -b 131072 -d ~/mr/manual/rootfs ~/mr/manual/disk.img

qemu-system-arm                 \
  -M versatilepb                \
  -kernel ~/mr/pre-built/zImage \
  -append "root=/dev/sda rw"    \
  -dtb versatile-pb.dtb         \
  -hda ~/mr/manual/disk.img


set +e
### START: build-less-fail.sh
cd ~/mr/dl
wget -c http://www.greenwoodsoftware.com/less/less-458.tar.gz
cd ~/mr/manual
tar -x -f ~/mr/dl/less-458.tar.gz
cd less-458
./configure --prefix=/usr                 \
            --host=arm-linux-gnueabi \
            --build=i686-pc-linux-gnu
### END: build-less-fail.sh
set -e

### START: build-ncurses.sh
cd ~/mr/dl
wget -c http://ftp.gnu.org/gnu/ncurses/ncurses-6.2.tar.gz
cd ~/mr/manual
tar -x -f ~/mr/dl/ncurses-6.2.tar.gz
cd ncurses-6.2
./configure --prefix=/usr             \
            --host=arm-linux-gnueabi  \
            --build=i686-pc-linux-gnu \
	    --without-progs           \
	    --disable-ext-funcs       \
      --without-cxx
make
make install DESTDIR=~/mr/manual/rootfs
### END: build-ncurses.sh

set +e
### START: build-less-fail-2.sh
cd ~/mr/manual/less-458
./configure --prefix=/usr                 \
            --host=arm-linux-gnueabi \
            --build=i686-pc-linux-gnu
### END: build-less-fail-2.sh
set -e

cat > ~/mr/manual/hello-ncurses.c <<EOF
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
cd ~/mr/manual
arm-linux-gnueabi-gcc hello-ncurses.c -o hello-ncurses
### END: build-hello-ncurses.sh

set -e

### START: check-ncurses-location.sh
ls ~/mr/manual/rootfs/usr/include
ls ~/mr/manual/rootfs/usr/lib
### END: check-ncurses-location.sh

### START: build-hello-ncurses-2.sh
arm-linux-gnueabi-gcc hello-ncurses.c \
    -I ~/mr/manual/rootfs/usr/include             \
    -L ~/mr/manual/rootfs/usr/lib                 \
    -lncurses
### END: build-hello-ncurses-2.sh

### START: build-less.sh
cd ~/mr/manual/less-458
./configure --prefix=/usr                 \
            --host=arm-linux-gnueabi \
            --build=i686-pc-linux-gnu     \
            LDFLAGS="-L ~/mr/manual/rootfs/usr/lib"  \
            CPPFLAGS="-I ~/mr/manual/rootfs/usr/include"
make
make install DESTDIR=~/mr/manual/rootfs
### END: build-less.sh

genext2fs -b 131072 -d ~/mr/manual/rootfs ~/mr/manual/disk.img

cd $SHARED

qemu-system-arm                 \
  -M versatilepb                \
  -kernel ~/mr/pre-built/zImage \
  -append "root=/dev/sda rw"    \
  -dtb versatile-pb.dtb         \
  -hda ~/mr/manual/disk.img
