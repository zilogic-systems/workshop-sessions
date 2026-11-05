#!/bin/bash

set -e -x -u

export PROJ_DIR=~/bitbake-builds/poky-wrynose
bitbake-layers create-layer $PROJ_DIR/layers/meta-zepto-fs

mkdir -p $PROJ_DIR/layers/meta-zepto-fs/recipes-core/images

cat > $PROJ_DIR/layers/meta-zepto-fs/recipes-core/images/core-image-tiny.bb  <<"EOF"
SUMMARY = "A tiny image just capable of allowing a device to boot."
IMAGE_INSTALL = " bash coreutils less "
inherit core-image
EOF

mkdir -p $PROJ_DIR/layers/meta-zepto-fs/conf/distro

cat > $PROJ_DIR/layers/meta-zepto-fs/conf/distro/zebian.conf <<"EOF"
require conf/distro/poky.conf

DISTRO = "zebian"
DISTRO_VERSION = "1.0"
DISTRO_FEATURES_OPTED_OUT = "wayland vulkan opengl"
EOF

cat >> $PROJ_DIR/build/conf/local.conf <<"EOF"
DISTRO = "zebian"
EOF

bitbake-config-build disable-fragment distro/poky
bitbake-config-build disable-fragment core/yocto/root-login-with-empty-password
bitbake-layers add-layer $PROJ_DIR/layers/meta-zepto-fs
bitbake core-image-tiny
