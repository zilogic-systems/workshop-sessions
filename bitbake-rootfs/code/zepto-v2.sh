mkdir -p ~/yp/zepto-v2
mkdir -p ~/yp/zepto-v2/conf
mkdir -p ~/yp/zepto-v2/classes

cat > ~/yp/zepto-v2/setup-bitbake.sh <<"EOF"
BITBAKE_VER=yocto-4.0
mkdir -p ~/yp/dl
pushd ~/yp/dl
wget -c -O bitbake-$BITBAKE_VER.tar.gz \
    https://github.com/openembedded/bitbake/archive/$BITBAKE_VER.tar.gz
popd

tar -x -f ~/yp/dl/bitbake-$BITBAKE_VER.tar.gz

pushd ~/yp/sandwich/bitbake-$BITBAKE_VER/bin
export PATH=$PWD:$PATH
popd

pushd ~/yp/sandwich/bitbake-$BITBAKE_VER/lib
export PYTHONPATH=$PWD:$PYTHONPATH
popd
EOF

cat > ~/yp/zepto-v2/conf/bitbake.conf <<"EOF"
TMPDIR = "${TOPDIR}/tmp"
CACHE = "${TMPDIR}/cache"
STAMP = "${TMPDIR}/stamps/${PN}"
T = "${TMPDIR}/work"
B = "${TMPDIR}"

BB_NUMBER_THREADS = "2"
ROOTFS = "${TMPDIR}/rootfs"
EOF

cat > ~/yp/zepto-v2/classes/base.bbclass <<"EOF"
addtask fetch
addtask unpack after do_fetch
addtask configure after do_unpack
addtask compile after do_configure
addtask install after do_compile
addtask rootfs after do_install

do_fetch[network] = "1"
do_configure[deptask] = "do_install"

PF = "${PN}"
EOF

cat > ~/yp/zepto-v2/classes/autotools.bbclass <<"EOF"
do_configure() {
	cd ${PN}-${PV}
        ./configure --prefix=/usr               \
            --host=arm-linux-gnueabi            \
            --build=i686-pc-linux-gnu           \
            LDFLAGS=-L${ROOTFS}/usr/lib         \
            CPPFLAGS=-I${ROOTFS}/usr/include
}

do_compile() {
	cd ${PN}-${PV}
        make
}

do_install() {
	cd ${PN}-${PV}
        make install DESTDIR=${ROOTFS}
}
EOF

cat > ~/yp/zepto-v2/bash.bb <<"EOF"
PN = "bash"
PV = "4.3"

inherit autotools

do_fetch() {
	cd ~/yp/dl; wget -c http://ftp.gnu.org/gnu/bash/${PN}-${PV}.tar.gz
}

do_unpack() {
	tar -x -f ~/yp/dl/${PN}-${PV}.tar.gz
}

do_install:append() {
	mkdir -p ${ROOTFS}/bin
	ln -f -s /usr/bin/bash ${ROOTFS}/bin/bash
	ln -f -s /usr/bin/bash ${ROOTFS}/bin/sh
}

EOF

cat > ~/yp/zepto-v2/coreutils.bb <<"EOF"
PN = "coreutils"
PV = "8.32"

inherit autotools

do_fetch() {
	cd ~/yp/dl; wget -c http://ftp.gnu.org/gnu/coreutils/${PN}-${PV}.tar.xz
}

do_unpack() {
	tar -x -f ~/yp/dl/${PN}-${PV}.tar.xz
}

EOF
