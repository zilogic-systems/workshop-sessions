git-sessions =			\
	git-basics		\
	git-internals		\
	git-remotes

git-resources =	git-resources

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
	kernel-dt-syntax	\
	kernel-display		\
	kernel-boot		\
	kernel-dt-drivers	\
	dt-debugging		\
	kernel-ethernet		\
	kernel-flash		\
	kernel-soc		\
	kernel-dt-by-example	\
	kernel-gpio		\
	kernel-pinctrl		\
	kernel-i2c

sessions = $(git-sessions) $(git-resources) $(yocto-sessions) $(kp-sessions)

all:
	for dir in $(sessions); do make -C $$dir; done

install:
	rm -fr build
	mkdir build
	for dir in $(sessions); do make -C $$dir $@ install-extra; done
	cd build; tar --gzip -c --transform "s|^|kp-slides/|" -f kp-slides.tar.gz $(kp-sessions)
	cd build; tar --gzip -c --transform "s|^|yocto-slides/|" -f yocto-slides.tar.gz $(yocto-sessions)
	cd build; tar --gzip -c --transform "s|^|git-slides/|" -f git-slides.tar.gz $(git-sessions)

clean:
	for dir in $(sessions); do make -C $$dir clean; done
