set -a
source versions.sh
set +a

mkdir -p ~/yp/zepto-v1
mkdir -p ~/yp/zepto-v1/conf
mkdir -p ~/yp/zepto-v1/classes

cat <<"EOF" | envsubst '$BITBAKE_VER' > ~/yp/zepto-v1/setup-bitbake.sh
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

cat > ~/yp/zepto-v1/conf/bitbake.conf <<"EOF"
TMPDIR = "${TOPDIR}/tmp"
CACHE = "${TMPDIR}/cache"
STAMP = "${TMPDIR}/stamps/${PN}"
T = "${TMPDIR}/work"
B = "${TMPDIR}"

BB_NUMBER_THREADS = "2"
ROOTFS = "${TMPDIR}/rootfs"
EOF

cat > ~/yp/zepto-v1/classes/base.bbclass <<"EOF"
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

cat <<"EOF" | envsubst '$BASH_VER' > ~/yp/zepto-v1/bash.bb
cat > ~/yp/zepto-v1/bash.bb <<"EOF"
PN = "bash"

do_fetch() {
	cd ~/yp/dl; wget -c http://ftp.gnu.org/gnu/bash/bash-$BASH_VER.tar.gz
}

do_unpack() {
	tar -x -f ~/yp/dl/bash-$BASH_VER.tar.gz
}

do_configure() {
	cd bash-$BASH_VER
        ./configure --prefix=/usr           \
            --host=arm-linux-gnueabi   \
            --build=i686-pc-linux-gnu
}

do_compile() {
	cd bash-$BASH_VER
        make
}

do_install() {
	cd bash-$BASH_VER
        make install DESTDIR=${ROOTFS}
	mkdir -p ${ROOTFS}/bin
	ln -f -s /usr/bin/bash ${ROOTFS}/bin/bash
	ln -f -s /usr/bin/bash ${ROOTFS}/bin/sh
}
EOF

cat <<"EOF" | envsubst '$COREUTILS_VER' > ~/yp/zepto-v1/coreutils.bb
PN = "coreutils"

do_fetch() {
	cd ~/yp/dl; wget -c http://ftp.gnu.org/gnu/coreutils/coreutils-$COREUTILS_VER.tar.xz
}

do_unpack() {
	tar -x -f ~/yp/dl/coreutils-$COREUTILS_VER.tar.xz
}

do_configure() {
	cd coreutils-$COREUTILS_VER
        ./configure --prefix=/usr           \
            --host=arm-linux-gnueabi   \
            --build=i686-pc-linux-gnu
}

do_compile() {
	cd coreutils-$COREUTILS_VER
        make
}

do_install() {
	cd coreutils-$COREUTILS_VER
        make install DESTDIR=${ROOTFS}
	mkdir -p ${ROOTFS}/bin
}
EOF
