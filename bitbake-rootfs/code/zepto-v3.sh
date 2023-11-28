mkdir -p ~/yp/zepto-v3
mkdir -p ~/yp/zepto-v3/conf
mkdir -p ~/yp/zepto-v3/classes

cat > ~/yp/zepto-v3/setup-bitbake.sh <<"EOF"
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

cat > ~/yp/zepto-v3/conf/bitbake.conf <<"EOF"
TMPDIR = "${TOPDIR}/tmp"
CACHE = "${TMPDIR}/cache"
STAMP = "${TMPDIR}/stamps/${PN}"
T = "${TMPDIR}/work"
B = "${TMPDIR}"
WORKDIR = "${TMPDIR}/${PN}/${PV}"
DL_DIR = "${HOME}/yp/dl"

BB_NUMBER_THREADS = "2"
ROOTFS = "${TMPDIR}/rootfs"
EOF

cat > ~/yp/zepto-v3/classes/base.bbclass <<"EOF"
addtask fetch
addtask unpack after do_fetch
addtask configure after do_unpack
addtask compile after do_configure
addtask install after do_compile
addtask rootfs after do_install

do_fetch[network] = "1"
do_configure[deptask] = "do_install"

PF = "${PN}"

do_fetch[dirs] = "${DL_DIR}"
python do_fetch() {
    src_uri = (d.getVar('SRC_URI', True) or "").split()
    if len(src_uri) == 0:
        return

    try:
        fetcher = bb.fetch2.Fetch(src_uri, d)
        fetcher.download()
    except bb.fetch2.BBFetchException as e:
        raise bb.build.FuncFailed(e)
}

do_unpack[dirs] = "${WORKDIR}"
python do_unpack() {
    src_uri = (d.getVar('SRC_URI', True) or "").split()
    if len(src_uri) == 0:
        return

    rootdir = d.getVar('WORKDIR', True)

    try:
        fetcher = bb.fetch2.Fetch(src_uri, d)
        fetcher.unpack(rootdir)
    except bb.fetch2.BBFetchException as e:
        raise bb.build.FuncFailed(e)

}
EOF

cat > ~/yp/zepto-v3/classes/autotools.bbclass <<"EOF"
do_configure() {
	cd ${WORKDIR}/${PN}-${PV}
        ./configure --prefix=/usr               \
            --host=arm-linux-gnueabi            \
            --build=i686-pc-linux-gnu           \
            LDFLAGS=-L${ROOTFS}/usr/lib	    \
            CPPFLAGS=-I${ROOTFS}/usr/include
}

do_compile() {
    cd ${WORKDIR}/${PN}-${PV}
    make
}

do_install() {
    cd ${WORKDIR}/${PN}-${PV}
    make install DESTDIR=${ROOTFS}
}
EOF

cat > ~/yp/zepto-v3/bash.bb <<"EOF"
PN = "bash"
PV = "4.3"

SRC_URI = "http://ftp.gnu.org/gnu/bash/bash-4.3.tar.gz"

inherit autotools

do_install:append() {
	mkdir -p ${ROOTFS}/bin
	ln -f -s /usr/bin/bash ${ROOTFS}/bin/bash
	ln -f -s /usr/bin/bash ${ROOTFS}/bin/sh
}
EOF

cat > ~/yp/zepto-v3/coreutils.bb <<"EOF"
PN = "coreutils"
PV = "8.32"

SRC_URI = "http://ftp.gnu.org/gnu/coreutils/coreutils-${PV}.tar.xz"

inherit autotools

EOF
