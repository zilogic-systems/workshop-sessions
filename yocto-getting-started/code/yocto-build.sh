#!/bin/bash

set -e -x

MACHINE="qemuarm64"
IMAGE="core-image-minimal"
PACKAGE="${PACKAGE:-strace}"


### START: bitbake-setup-init.sh
# Needs the bitbake-setup venv to be active
bitbake-setup init --non-interactive poky-wrynose poky distro/poky "machine/${MACHINE}"
### END: bitbake-setup-init.sh


### START: source-init-build-env.sh
source ~/bitbake-builds/poky-wrynose/build/init-build-env
### END: source-init-build-env.sh

# Note: The sstate-cache path has to be set before running any bitbake commands
# for proper sstate-cache matching.
### START: configure-build-cache.sh
# Reuse the download dir and sstate-cache available in ${HOME}
cat >> conf/local.conf << 'CONF'
DL_DIR = "${HOME}/downloads"
SSTATE_DIR = "${HOME}/sstate-cache"
CONF
### END: configure-build-cache.sh


### START: configure-extra-image-features.sh
# Enable root login with empty password (configuration fragment)
bitbake-config-build enable-fragment core/yocto/root-login-with-empty-password
### END: configure-extra-image-features.sh


### START: bitbake-core-image-minimal.sh
bitbake "${IMAGE}"
### END: bitbake-core-image-minimal.sh


### START: ls-deploy-images.sh
ls "tmp/deploy/images/${MACHINE}/"
### END: ls-deploy-images.sh


### START: cat-rootfs-manifest.sh
cat "tmp/deploy/images/${MACHINE}/${IMAGE}-${MACHINE}.rootfs.manifest"
### END: cat-rootfs-manifest.sh


### START: bitbake-g-core-image-minimal.sh
bitbake -g "${IMAGE}"
### END: bitbake-g-core-image-minimal.sh


### START: pn-buildlist.sh
cat pn-buildlist
### END: pn-buildlist.sh


### START: bitbake-s-grep-package.sh
# The slide uses <package> as a placeholder; strace is the example here.
bitbake -s | grep "${PACKAGE}"
### END: bitbake-s-grep-package.sh


### START: image-install-package.sh
echo "IMAGE_INSTALL:append = \" ${PACKAGE}\"" >> conf/local.conf

bitbake "${IMAGE}"

grep "^${PACKAGE} " "tmp/deploy/images/${MACHINE}/${IMAGE}-${MACHINE}.rootfs.manifest"
### END: image-install-package.sh


### START: runqemu-snapshot-nographic.sh
# Interactive; exit QEMU to return
runqemu snapshot nographic
### END: runqemu-snapshot-nographic.sh
