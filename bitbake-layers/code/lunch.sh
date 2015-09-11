mkdir -p ~/yp/lunch
mkdir -p ~/yp/lunch/conf
mkdir -p ~/yp/lunch/meta/conf
mkdir -p ~/yp/lunch/meta/classes

cat > ~/yp/lunch/setup-bitbake.sh <<"EOF"
pushd ~/yp/dl
wget -c -O bitbake-1.17.0.tar.gz \
    https://github.com/openembedded/bitbake/archive/1.17.0.tar.gz
popd

tar -x -f ~/yp/dl/bitbake-1.17.0.tar.gz

pushd bitbake-1.17.0
python setup.py build
popd

pushd ~/yp/lunch/bitbake-1.17.0/build/scripts*
export PATH=$PWD:$PATH
popd

pushd ~/yp/lunch/bitbake-1.17.0/build/lib*
export PYTHONPATH=$PWD:$PYTHONPATH
popd

pushd ~/yp/lunch/bitbake-1.17.0/lib
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
        echo ${PN}: wheat > bread.txt
        echo ${PN}: salt  >> bread.txt
        echo ${PN}: sugar >> bread.txt
        echo ${PN}: water >> bread.txt
        sleep 1
}

do_cook() {
        echo "${PN}: bake for 20 - 25 minutes" >> bread.txt
        sleep 2
        echo "${PN}: ready" >> bread.txt
}
EOF

cat > ~/yp/lunch/meta/omelet.bb <<"EOF"
PN = "omelet"

do_get() {
        echo ${PN}: egg > omelet.txt
        echo ${PN}: pepper  >> omelet.txt
        sleep 1
}

do_cook() {
        echo ${PN}: fry >> omelet.txt
        sleep 2
        echo ${PN}: ready >> omelet.txt
}
EOF

cat > ~/yp/lunch/meta/sandwich.bb <<"EOF"
PN = "sandwich"

DEPENDS = "bread omelet"

do_get() {
        cat bread.txt > sandwich.txt
        cat omelet.txt  >> sandwich.txt
        sleep 1
}

do_cook() {
        echo "${PN}: toast bread and serve" >> sandwich.txt
        sleep 2
        echo "${PN}: ready" >> sandwich.txt
}
EOF
