set -a
source versions.sh
set +a

mkdir -p ~/yp/zepto
mkdir -p ~/yp/zepto/conf
mkdir -p ~/yp/zepto/classes

cat <<"EOF" | envsubst '$BITBAKE_VER' > ~/yp/zepto/setup-bitbake.sh
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

cat > ~/yp/zepto/conf/bitbake.conf <<"EOF"
TMPDIR = "${TOPDIR}/tmp"
CACHE = "${TMPDIR}/cache"
STAMP = "${TMPDIR}/stamps/${PN}"
T = "${TMPDIR}/work"
B = "${TMPDIR}"
WORKDIR = "${TMPDIR}/${PN}/${PV}"

ROOTFS = "${TMPDIR}/rootfs"
DISKIMG = "${TMPDIR}/disk.img"
DL_DIR = "${HOME}/yp/dl"
TOOLCHAIN_DIR = "/usr/arm-linux-gnueabi"
BB_NUMBER_THREADS = "2"
EOF

cat > ~/yp/zepto/classes/base.bbclass <<"EOF"
addtask fetch
addtask unpack after do_fetch
addtask configure after do_unpack
addtask compile after do_configure
addtask install after do_compile
addtask rootfs after do_install

do_fetch[network] = "1"
do_configure[deptask] = "do_install"
do_rootfs[rdeptask] = "do_install"

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

cat > ~/yp/zepto/classes/autotools.bbclass <<"EOF"
do_configure() {
	cd ${WORKDIR}/${PN}-${PV}
        ./configure --prefix=/usr               \
            --host=arm-linux-gnueabi            \
            --build=i686-pc-linux-gnu           \
            ${CONFIG_OPTS}                      \
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
	mkdir -p ${ROOTFS}/bin
}
EOF

cat <<"EOF" | envsubst '$COREUTILS_VER' > ~/yp/zepto/coreutils.bb
inherit autotools

PN = "coreutils"
PV = "$COREUTILS_VER"
SRC_URI = "http://ftp.gnu.org/gnu/coreutils/coreutils-${PV}.tar.xz"
EOF

cat <<"EOF" | envsubst '$BASH_VER' > ~/yp/zepto/bash.bb
inherit autotools

PN = "bash"
PV = "$BASH_VER"
SRC_URI = "ftp://ftp.gnu.org/gnu/bash/bash-${PV}.tar.gz"

do_install:append() {
	mkdir -p ${ROOTFS}/bin
	ln -f -s /usr/bin/bash ${ROOTFS}/bin/bash
	ln -f -s /usr/bin/bash ${ROOTFS}/bin/sh
}
EOF

cat <<"EOF" | envsubst '$NCURSES_VER' > ~/yp/zepto/ncurses.bb
inherit autotools

PN = "ncurses"
PV = "$NCURSES_VER"
SRC_URI = "http://ftp.gnu.org/gnu/ncurses/ncurses-${PV}.tar.gz"
CONFIG_OPTS += "--without-progs --disable-ext-funcs --without-cxx"
EOF

cat <<"EOF" | envsubst '$LESS_VER' > ~/yp/zepto/less.bb
inherit autotools

PN = "less"
PV = "$LESS_VER"
SRC_URI = "http://www.greenwoodsoftware.com/less/less-${PV}.tar.gz"
DEPENDS = "ncurses"

EOF

cat > ~/yp/zepto/libc.bb <<"EOF"
PN = "libc"
PV = "2.5"

do_configure() {
    :
}

do_compile() {
    :
}

do_install() {
    mkdir -p ${ROOTFS}/lib
    cp ${TOOLCHAIN_DIR}/lib/libc.so.6 ${ROOTFS}/lib
    cp ${TOOLCHAIN_DIR}/lib/ld-linux.so.3 ${ROOTFS}/lib
}
EOF

cat > ~/yp/zepto/core-image-minimal.bb <<"EOF"
PN = "core-image-minimal"
PV = "1.0"
RDEPENDS = "libc bash coreutils less"

do_rootfs() {
	mkdir -p ${ROOTFS}/dev ${ROOTFS}/tmp
	genext2fs -b 131072 -d ${ROOTFS} ${DISKIMG}
}
EOF
