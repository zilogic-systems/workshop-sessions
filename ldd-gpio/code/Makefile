obj-m += led.o 
obj-m += led-params.o
export KERNEL_DIR=~/projects/linux
all:
	make -C $(KERNEL_DIR) ARCH=arm CROSS_COMPILE=arm-none-linux-gnueabi- M=`pwd`
