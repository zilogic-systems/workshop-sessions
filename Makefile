yocto-sessions = 		\
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
	yocto-intro		\
	home-automation

kp-sessions =			\
	devices-intro		\
	kernel-qemu		\
	kernel-drivers		\
	kernel-modules		\
	kernel-build		\
	kernel-writing-modules	\
	kernel-bus-model	\
	kernel-dt-syntax

sessions = $(yocto-sessions) $(kp-sessions)

all:
	for dir in $(sessions); do make -C $$dir; done

install:
	rm -fr build
	mkdir build
	for dir in $(sessions); do make -C $$dir $@ install-extra; done
	cd build; tar --gzip -c --transform "s|^|kp-slides/|" -f kp-slides.tar.gz $(kp-sessions)
	cd build; tar --gzip -c --transform "s|^|yoctol-slides/|" -f yocto-slides.tar.gz $(yocto-sessions)

clean:
	for dir in $(sessions); do make -C $$dir clean; done
