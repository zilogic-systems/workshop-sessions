sessions = 			\
	autotools		\
	bitbake-data-model	\
	bitbake-intro		\
	bitbake-layers		\
	bitbake-packages	\
	bitbake-rootfs		\
	debian-packaging	\
	manual-rootfs		\
	yocto-customization	\
	yocto-getting-started	\
	yocto-internals		\
	yocto-intro

all:
	for dir in $(sessions); do make -C $$dir; done

install:
	rm -fr build
	mkdir build
	for dir in $(sessions); do make -C $$dir $@ install-extra; done
