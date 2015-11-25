mkdir -p ~/yp/sandwich
mkdir -p ~/yp/sandwich/conf
mkdir -p ~/yp/sandwich/classes

cat > ~/yp/sandwich/setup-bitbake.sh <<"EOF"
pushd ~/yp/dl
wget -c -O bitbake-1.17.0.tar.gz \
    https://github.com/openembedded/bitbake/archive/1.17.0.tar.gz
popd

tar -x -f ~/yp/dl/bitbake-1.17.0.tar.gz

pushd bitbake-1.17.0
python setup.py build
popd

pushd ~/yp/sandwich/bitbake-1.17.0/build/scripts*
export PATH=$PWD:$PATH
popd

pushd ~/yp/sandwich/bitbake-1.17.0/build/lib*
export PYTHONPATH=$PWD:$PYTHONPATH
popd

pushd ~/yp/sandwich/bitbake-1.17.0/lib
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

