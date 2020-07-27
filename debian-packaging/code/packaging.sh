set -e

mkdir -p ~/yp/packaging
mkdir -p ~/yp/packaging/build

#
# hello-1.0.0
#

pushd ~/yp/packaging/build
mkdir -p hello/bin
cat > hello/bin/hello <<EOF
#!/bin/bash
echo Hello World!
EOF

chmod +x hello/bin/hello
popd


pushd ~/yp/packaging
fpm -s dir -t deb -n "hello" -v 1.0.0 \
    -a all -C ~/yp/packaging/build/hello \
    --description "Simple Hello World package." .
popd

#
# hello-1.1.0
#

pushd ~/yp/packaging/build
mkdir -p hello/bin
cat > hello/bin/hello <<EOF
#!/bin/bash
echo Hello World v1.1.0!
EOF
popd

pushd ~/yp/packaging
fpm -s dir -t deb -n "hello" -v 1.1.0 \
    -a all -C ~/yp/packaging/build/hello \
    --description "Simple Hello World package." .
popd

#
# abc def
#

mkdir -p ~/yp/packaging/build/dummy

pushd ~/yp/packaging
fpm -s dir -t deb -n "abc" -v 1.0.0 \
    -a all -C ~/yp/packaging/build/dummy \
    --depends def                      \
    --description "Package for understanding deps." .

fpm -s dir -t deb -n "def" -v 1.0.0 \
    -a all -C ~/yp/packaging/build/dummy \
    --description "Package for understanding deps." .
popd

#
# Test Repos
#

mkdir -p ~/yp/repos
mkdir -p ~/yp/repos/myrepo
mkdir -p ~/yp/repos/mypkgs
mkdir -p ~/yp/repos/conf

pushd ~/yp/repos

cat > conf/distributions << EOF
Codename: wheezy
Architectures: i386 amd64
Components: main
EOF

popd

pushd ~/yp/repos/mypkgs

for i in $(seq 1 5)
do
    fpm -s dir -t deb -n "mypkg$i" -v 1.0.0 \
	-a all -C ~/yp/packaging/build/dummy \
	--depends def                          \
	--description "Package $i for understanding repos." .
done

popd

pushd ~/yp/repos
rm -fr myrepo/*
rm -fr db
reprepro --outdir ./myrepo includedeb wheezy mypkgs/*.deb
rm -fr conf
rm -fr db
popd
