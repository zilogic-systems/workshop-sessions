obj-m := y.o

export KERNEL_DIR=~/linux-4.4.39
export ARCH=arm
export CROSS_COMPILE=arm-none-linux-gnueabi-

all:
	make -C $(KERNEL_DIR) M=`pwd` modules

install:
	cp *.ko /tftpboot


