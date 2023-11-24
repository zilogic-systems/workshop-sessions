mkdir -p ~/yp/sandwich
mkdir -p ~/yp/sandwich/conf
mkdir -p ~/yp/sandwich/classes

cat > ~/yp/sandwich/setup-bitbake.sh <<"EOF"
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

cat > ~/yp/sandwich/conf/bitbake.conf <<"EOF"
### START: bitbake.conf
TMPDIR = "${TOPDIR}/tmp"
CACHE = "${TMPDIR}/cache"
STAMP = "${TMPDIR}/stamps/${PN}"
T = "${TMPDIR}/work"
B = "${TMPDIR}"
### END: bitbake.conf
EOF

cat > ~/yp/sandwich/classes/base.bbclass <<"EOF"
PF = "${PN}"
EOF

cat > ~/yp/sandwich/bread.bb <<"EOF"
PN = "bread"

do_get() {
        echo ${PN}: wheat > bread.txt
        echo ${PN}: salt  >> bread.txt
        echo ${PN}: sugar >> bread.txt
        echo ${PN}: water >> bread.txt
        sleep 1
}
addtask get

do_cook() {
        echo "${PN}: bake for 20 - 25 minutes" >> bread.txt
        sleep 2
        echo "${PN}: ready" >> bread.txt
}
addtask cook
EOF

