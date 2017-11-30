#!/bin/bash

vboxmanage controlvm debian-i386-wheezy poweroff
vboxmanage unregistervm debian-i386-wheezy  --delete
rm -rf machines tmp vboximage
rm -f workshop-box.tar.gz
