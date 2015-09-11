mkdir -p ~/yp/zepto-v1
mkdir -p ~/yp/zepto-v1/conf
mkdir -p ~/yp/zepto-v1/classes

cat > ~/yp/zepto-v1/setup-bitbake.sh <<"EOF"
pushd ~/yp/dl
wget -c -O bitbake-1.17.0.tar.gz \
    https://github.com/openembedded/bitbake/archive/1.17.0.tar.gz
popd

tar -x -f ~/yp/dl/bitbake-1.17.0.tar.gz

pushd bitbake-1.17.0
python setup.py build
popd

pushd ~/yp/zepto-v1/bitbake-1.17.0/build/scripts*
export PATH=$PWD:$PATH
popd

pushd ~/yp/zepto-v1/bitbake-1.17.0/build/lib*
export PYTHONPATH=$PWD:$PYTHONPATH
popd

pushd ~/yp/zepto-v1/bitbake-1.17.0/lib
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

do_configure[deptask] = "do_install"

PF = "${PN}"
EOF

cat > ~/yp/zepto-v1/bash.bb <<"EOF"
PN = "bash"

do_fetch() {
	cd ~/yp/dl; wget -c http://ftp.gnu.org/gnu/bash/bash-4.3.tar.gz
}

do_unpack() {
	tar -x -f ~/yp/dl/bash-4.3.tar.gz
}

do_configure() {
	cd bash-4.3
        ./configure --prefix=/usr           \
            --host=arm-none-linux-gnueabi   \
            --build=i686-pc-linux-gnu
}

do_compile() {
	cd bash-4.3
        make
}

do_install() {
	cd bash-4.3
        make install DESTDIR=${ROOTFS}
	mkdir -p ${ROOTFS}/bin
	ln -f -s /usr/bin/bash ${ROOTFS}/bin/bash
	ln -f -s /usr/bin/bash ${ROOTFS}/bin/sh
}
EOF

cat > ~/yp/zepto-v1/coreutils.bb <<"EOF"
PN = "coreutils"

do_fetch() {
	cd ~/yp/dl; wget -c http://ftp.gnu.org/gnu/coreutils/coreutils-6.7.tar.bz2
}

do_unpack() {
	tar -x -f ~/yp/dl/coreutils-6.7.tar.bz2
}

do_configure() {
	cd coreutils-6.7
        ./configure --prefix=/usr           \
            --host=arm-none-linux-gnueabi   \
            --build=i686-pc-linux-gnu
}

do_compile() {
	cd coreutils-6.7
        make
}

do_install() {
	cd coreutils-6.7
        make install DESTDIR=${ROOTFS}
	mkdir -p ${ROOTFS}/bin
}
EOF
