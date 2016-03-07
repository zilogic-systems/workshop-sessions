all:
	make -C autotools
	make -C bitbake-data-model
	make -C bitbake-intro
	make -C bitbake-layers
	make -C bitbake-packages
	make -C bitbake-rootfs
	make -C debian-packaging
	make -C manual-rootfs
	make -C yocto-customization
	make -C yocto-getting-started
	make -C yocto-internals
	make -C yocto-intro

