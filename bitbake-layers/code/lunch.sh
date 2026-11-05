mkdir -p ~/yp/lunch
mkdir -p ~/yp/lunch/conf
mkdir -p ~/yp/lunch/meta/conf
mkdir -p ~/yp/lunch/meta/classes

cat > ~/yp/lunch/setup-bitbake.sh <<"EOF"
BITBAKE_VER=yocto-6.0
pushd ~/yp/dl
wget -c -O bitbake-$BITBAKE_VER.tar.gz \
    https://github.com/openembedded/bitbake/archive/$BITBAKE_VER.tar.gz
popd

tar -x -f ~/yp/dl/bitbake-$BITBAKE_VER.tar.gz

pushd ~/yp/lunch/bitbake-$BITBAKE_VER/bin
export PATH=$PWD:$PATH
popd

pushd ~/yp/lunch/bitbake-$BITBAKE_VER/lib
export PYTHONPATH=$PWD:$PYTHONPATH
popd
EOF

cat > ~/yp/lunch/conf/bblayers.conf <<"EOF"
BBLAYERS = "         \
  ${TOPDIR}/meta     \
"
EOF

cat > ~/yp/lunch/meta/conf/layer.conf <<"EOF"
BBPATH .= ":${LAYERDIR}"

BBFILES += "${LAYERDIR}/*.bb"

BBFILE_COLLECTIONS += "core"
BBFILE_PATTERN_core := "^${LAYERDIR}/"
EOF

cat > ~/yp/lunch/meta/conf/bitbake.conf <<"EOF"
TMPDIR = "${TOPDIR}/tmp"
CACHE = "${TMPDIR}/cache"
STAMP = "${TMPDIR}/stamps/${PN}"
T = "${TMPDIR}/work"
B = "${TMPDIR}"
EOF

cat > ~/yp/lunch/meta/classes/base.bbclass <<"EOF"
addtask get
addtask cook after do_get
do_get[deptask] = "do_cook"

PF = "${PN}"

EOF

cat > ~/yp/lunch/meta/bread.bb <<"EOF"
PN = "bread"

do_get() {
        echo ${PN}: wheat > ${TMPDIR}/bread.txt
        echo ${PN}: salt  >> ${TMPDIR}/bread.txt
        echo ${PN}: sugar >> ${TMPDIR}/bread.txt
        echo ${PN}: water >> ${TMPDIR}/bread.txt
        sleep 1
}

do_cook() {
        echo "${PN}: bake for 20 - 25 minutes" >> ${TMPDIR}/bread.txt
        sleep 2
        echo "${PN}: ready" >> ${TMPDIR}/bread.txt
}
EOF

cat > ~/yp/lunch/meta/omelet.bb <<"EOF"
PN = "omelet"

do_get() {
        echo ${PN}: egg > ${TMPDIR}/omelet.txt
        echo ${PN}: pepper  >> ${TMPDIR}/omelet.txt
        sleep 1
}

do_cook() {
        echo ${PN}: fry >> ${TMPDIR}/omelet.txt
        sleep 2
        echo ${PN}: ready >> ${TMPDIR}/omelet.txt
}
EOF

cat > ~/yp/lunch/meta/sandwich.bb <<"EOF"
PN = "sandwich"

DEPENDS = "bread omelet"

do_get() {
        cat ${TMPDIR}/bread.txt > ${TMPDIR}/sandwich.txt
        cat ${TMPDIR}/omelet.txt  >> ${TMPDIR}/sandwich.txt
        sleep 1
}

do_cook() {
        echo "${PN}: toast bread and serve" >> ${TMPDIR}/sandwich.txt
        sleep 2
        echo "${PN}: ready" >> ${TMPDIR}/sandwich.txt
}
EOF
