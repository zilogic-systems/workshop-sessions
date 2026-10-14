#!/bin/bash

set -e -x -u

cat <<EOF > ~/mr/run-qemu.sh
### START: boot-prebuilt.sh
qemu-system-arm -M versatilepb \
                -hda disk.img  \
		-kernel zImage \
                -dtb versatile-pb.dtb \
		-append "root=/dev/sda rw"
### END: boot-prebuilt.sh
EOF

# ### START: copy-prebuilt.sh
# cp ~/mr/pre-built/zImage $SHARED
# cp ~/mr/pre-built/disk.img $SHARED
# cp ~/mr/pre-built/versatile-pb.dtb $SHARED
# ### END: copy-prebuilt.sh

### START: run-qemu.sh
cd ~/mr
bash run-qemu.sh
### END: run-qemu.sh

### START: setup-env.sh
BUILD=~/mr/build
ROOTFS=~/mr/rootfs
DISKIMG=~/mr/disk.img
### END: setup-env.sh

mkdir -p $BUILD
mkdir -p $ROOTFS

cat > ~/mr/build/hello.c <<EOF
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
cd ~/mr/build
arm-linux-gnueabi-gcc -static hello.c -o hello
### END: build-hello.sh

### START: copy-hello.sh
mkdir -p ~/mr/rootfs/bin
cp hello ~/mr/rootfs/bin/sh
### END: copy-hello.sh

### START: create-hello-rootfs.sh
genext2fs -b 131072 -d ~/mr/rootfs ~/mr/disk.img
### END: create-hello-rootfs.sh

### START: boot-hello-rootfs.sh
cd ~/mr
bash run-qemu.sh
### END: boot-hello-rootfs.sh

mkdir -p ~/mr/dl

### START: download-bash.sh
cd ~/mr/dl
wget -c http://ftp.gnu.org/gnu/bash/bash-5.3.tar.gz
### END: download-bash.sh

### START: unpack-bash.sh
cd ~/mr/build
tar -x -f ~/mr/dl/bash-5.3.tar.gz
### END: unpack-bash.sh

### START: configure-bash.sh
cd bash-5.3
./configure --prefix=/usr                \
            --host=arm-linux-gnueabi \
            --build=i686-pc-linux-gnu
### END: configure-bash.sh

### START: build-bash.sh
make
### END: build-bash.sh

### START: install-bash.sh
make install DESTDIR=~/mr/rootfs
### END: install-bash.sh

### START: check-bash-deps.sh
arm-linux-gnueabi-readelf -d ~/mr/rootfs/usr/bin/bash
### END: check-bash-deps.sh

rm -f ~/mr/rootfs/bin/sh

### START: link-bash.sh
ln -s /usr/bin/bash ~/mr/rootfs/bin/bash
ln -s /usr/bin/bash ~/mr/rootfs/bin/sh
### END: link-bash.sh

### START: cp-bash-deps.sh
mkdir ~/mr/rootfs/lib
TOOLCHAIN="/usr/arm-linux-gnueabi"
cp $TOOLCHAIN/lib/libc.so.6 \
   ~/mr/rootfs/lib
### END: cp-bash-deps.sh

### START: copy-ld.sh
cp $TOOLCHAIN/lib/ld-linux.so.3 \
   ~/mr/rootfs/lib
### END: copy-ld.sh

### START: make-dev-tmp.sh
mkdir ~/mr/rootfs/dev ~/mr/rootfs/tmp
### END: make-dev-tmp.sh

### START: create-bash-rootfs.sh
genext2fs -b 131072 -d ~/mr/rootfs ~/mr/disk.img
### END: create-bash-rootfs.sh

### START: boot-bash-rootfs.sh
cd ~/mr
bash run-qemu.sh
### END: boot-bash-rootfs.sh

### START: build-coreutils.sh
cd ~/mr/dl
wget -c http://ftp.gnu.org/gnu/coreutils/coreutils-9.12.tar.xz
cd ~/mr/build
tar -x -f ~/mr/dl/coreutils-9.12.tar.xz
cd coreutils-9.12
./configure --prefix=/usr                 \
            --host=arm-linux-gnueabi \
            --build=i686-pc-linux-gnu
make
make install DESTDIR=~/mr/rootfs
### END: build-coreutils.sh

### START: create-ls-rootfs.sh
genext2fs -b 131072 -d ~/mr/rootfs ~/mr/disk.img
### END: create-ls-rootfs.sh

cd ~/mr
bash run-qemu.sh

set +e
### START: build-less-fail.sh
cd ~/mr/dl
wget -c http://www.greenwoodsoftware.com/less/less-710.tar.gz
cd ~/mr/build
tar -x -f ~/mr/dl/less-710.tar.gz
cd less-710
./configure --prefix=/usr                 \
            --host=arm-linux-gnueabi \
            --build=i686-pc-linux-gnu
### END: build-less-fail.sh
set -e

### START: build-ncurses.sh
cd ~/mr/dl
wget -c http://ftp.gnu.org/gnu/ncurses/ncurses-6.2.tar.gz
cd ~/mr/build
tar -x -f ~/mr/dl/ncurses-6.2.tar.gz
cd ncurses-6.2
./configure --prefix=/usr             \
            --host=arm-linux-gnueabi  \
            --build=i686-pc-linux-gnu \
	    --without-progs           \
	    --disable-ext-funcs       \
      --without-cxx
make
make install DESTDIR=~/mr/rootfs
### END: build-ncurses.sh

set +e
### START: build-less-fail-2.sh
cd ~/mr/build/less-710
./configure --prefix=/usr                 \
            --host=arm-linux-gnueabi \
            --build=i686-pc-linux-gnu
### END: build-less-fail-2.sh
set -e

cat > ~/mr/build/hello-ncurses.c <<EOF
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
cd ~/mr/build
arm-linux-gnueabi-gcc hello-ncurses.c -o hello-ncurses
### END: build-hello-ncurses.sh

set -e

### START: check-ncurses-location.sh
ls ~/mr/rootfs/usr/include
ls ~/mr/rootfs/usr/lib
### END: check-ncurses-location.sh

### START: build-hello-ncurses-2.sh
arm-linux-gnueabi-gcc hello-ncurses.c \
    -I ~/mr/rootfs/usr/include             \
    -L ~/mr/rootfs/usr/lib                 \
    -lncurses
### END: build-hello-ncurses-2.sh

### START: build-less.sh
cd ~/mr/build/less-710
./configure --prefix=/usr                 \
            --host=arm-linux-gnueabi \
            --build=i686-pc-linux-gnu     \
            LDFLAGS="-L /home/user/mr/rootfs/usr/lib"  \
            CPPFLAGS="-I /home/user/mr/rootfs/usr/include"
make
make install DESTDIR=~/mr/rootfs
### END: build-less.sh

genext2fs -b 131072 -d ~/mr/rootfs ~/mr/disk.img

qemu-system-arm                 \
  -M versatilepb                \
  -kernel ~/mr/zImage \
  -append "root=/dev/sda rw"    \
  -dtb ~/mr/versatile-pb.dtb         \
  -hda ~/mr/disk.img
