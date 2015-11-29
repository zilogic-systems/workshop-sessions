mkdir -p ~/yp/packages
mkdir -p ~/yp/packages/fpm
mkdir -p ~/yp/packages/inside-deb
mkdir -p ~/yp/packages/multistrap
mkdir -p ~/yp/packages/repo
mkdir -p ~/yp/packages/sample-pkgs

pushd ~/yp/packages/fpm
mkdir -p hello-world/bin
cat > hello-world/bin/hello << EOF
#!/bin/bash
echo Hello World!
EOF
pushd hello-world/bin
chmod +x hello
popd
popd

pushd ~/yp/packages/sample-pkgs
fpm -s dir -t deb -n "hello-world" -v 2.8 -a all -C ~/yp/packages/fpm/hello-world --description "Hello World"
cp hello-world*.deb ~/yp/packages/inside-deb
popd

pushd ~/yp/packages/repo
mkdir conf
cat > conf/distributions << EOF
Suite: stable
Codename: femto
Architectures: arm
Components: main
Description: femto deb packages
EOF
popd

pushd ~/yp/packages/multistrap
cat > multistrap.conf << EOF
[General]
noauth=true
bootstrap=Packages

[Packages]
packages=hello-world
source=copy:///$HOME/yp/packages/repo/
suite=femto
omitdebsrc=true
EOF
popd

