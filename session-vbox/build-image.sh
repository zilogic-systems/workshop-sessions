#!/bin/bash

set -e

# Now create the virtualbox images.
BOX_NAME="debian-i386-jessie"
VERSION="1.1"
BASE_DIR="${PWD}/machines"
BOX_DIR="${BASE_DIR}/${BOX_NAME}"
EXPORT_DIR="${PWD}/vboximage"
SHR_DIR="shared"
SSHKEY="$HOME/.ssh/id_rsa"
SSHOPTION="-o StrictHostKeyChecking=no"

function usage() {
    echo "Usage:"
    echo -e "\t $SCRIPT [options]\n"
    echo "Options:"
    echo -e "\t --usbpassthrough\t enable|disable\n"
    echo -e "\t\t\t\t Switches Host USB to be accessed by Guest OS.\n\n"
    echo -e "\t --guestadditions\t enable|disable\n"
    echo -e "\t\t\t\t Installs Guest additions for shared folder access"
    echo -e "\t\t\t\t in Guest OS.\n\n"
    echo -e "\t --yoctodeps     \t enable|disable\n"
    echo -e "\t\t\t\t Installs Yocto build dependencies in the Guest OS.\n\n"
    echo -e "\t --baremetaldeps     \t enable|disable\n"
    echo -e "\t\t\t\t Installs dependency packages for bare metal programming"
    echo -e "\t\t\t\t sessions.\n\n"
    echo -e "\t --linuxprogdeps     \t enable|disable\n"
    echo -e "\t\t\t\t Installs dependency packages for linux programming"
    echo -e "\t\t\t\t sessions.\n\n"
    echo -e "\t --linuxkernelporting\t enable|disable\n"
    echo -e "\t\t\t\t Installs dependency packages for linux kernel porting workshop"
    echo -e "\t\t\t\t sessions."
    echo -e "\t --devicedrivers\t enable|disable\n"
    echo -e "\t\t\t\t Installs dependency packages for linux device drivers workshop"
    echo -e "\t\t\t\t sessions."
}

if [ "x$1" == "x-h" ] || [ "x$1" == "x--help" ]; then
    SCRIPT=$(basename $0)
    usage
    exit 0
fi

USBPASSTHROUGH="--usbpassthrough"
USBPASSTHROUGHENABLE="enable"
GUESTADDITIONS="--guestadditions"
GUESTADDITIONSENABLE="enable"
YOCTODEPS="--yoctodeps"
YOCTODEPSENABLE="disable"
BAREMETALDEPS="--baremetaldeps"
BAREMETALDEPSENABLE="disable"
LINUXPROGDEPS="--linuxprogdeps"
LINUXPROGDEPSENABLE="disable"
LINUXKERNELPORTING="--linuxkernelporting"
LINUXKERNELPORTINGENABLE="disable"
LINUXDEVICEDRIVERS="--linuxdevicedrivers"
LINUXDEVICEDRIVERSENABLE="enable"

while test $# -gt 0;do
    case $1 in
	$USBPASSTHROUGH)
	    PREV=$USBPASSTHROUGH
	    shift
	    ;;

	$GUESTADDITIONS)
	    PREV=$GUESTADDITIONS
	    shift
	    ;;

	$YOCTODEPS)
	    PREV=$YOCTODEPS
	    shift
	    ;;

	$BAREMETALDEPS)
	    PREV=$BAREMETALDEPS
	    shift
	    ;;

	$LINUXPROGDEPS)
	    PREV=$LINUXPROGDEPS
	    shift
	    ;;

	$LINUXKERNELPORTING)
	    PREV=$LINUXKERNELPORTING
	    shift
	    ;;

	$LINUXDEVICEDRIVERS)
	    PREV=$LINUXDEVICEDRIVERS
	    shift
	    ;;

	"enable" | "disable")
	    if [ "x$PREV" == "x$USBPASSTHROUGH" ] ;then
		USBPASSTHROUGHENABLE=$1
	    elif [ "x$PREV" == "x$YOCTODEPS" ] ;then
		YOCTODEPSENABLE=$1
	    elif [ "x$PREV" == "x$BAREMETALDEPS" ] ;then
		BAREMETALDEPSENABLE=$1
	    elif [ "x$PREV" == "x$LINUXPROGDEPS" ] ;then
		LINUXPROGDEPSENABLE=$1
	    elif [ "x$PREV" == "x$LINUXKERNELPORTING" ] ;then
		LINUXKERNELPORTINGENABLE=$1
	    elif [ "x$PREV" == "x$LINUXDEVICEDRIVERS" ] ;then
		LINUXDEVICEDRIVERS=$1
	    else
		GUESTADDITIONSENABLE=$1
	    fi
	    shift
	    ;;
	*)
	    usage
	    exit 1
	;;

    esac
done

echo "USB Pass through                                   : ${USBPASSTHROUGHENABLE}d"
echo "Guest Additions                                    : ${GUESTADDITIONSENABLE}d"
echo "Yocto Workshop Dependencies                        : ${YOCTODEPSENABLE}d"
echo "ARM Bare Metal Programming Workshop Dependencies   : ${BAREMETALDEPSENABLE}d"
echo "Linux Programming Course Dependencies              : ${LINUXPROGDEPSENABLE}d"
echo "Linux Kernel Porting Workshop Dependencies         : ${LINUXKERNELPORTINGENABLE}d"
echo "Linux Device Driver Workshop Dependencies          : ${LINUXDEVICEDRIVERSENABLE}d"

if [ ! -f "${BOX_NAME}.vmdk" ];then
    echo -n "Extracting Base Box Image..."
    tar -xf ${BOX_NAME}.tar.xz
    echo "Done."
fi

mkdir -p ${BASE_DIR}
mkdir -p tmp
rm -fr tmp/clone.vdi

vboxmanage createvm --name "${BOX_NAME}" --ostype Debian --basefolder \
	   ${BASE_DIR}

vboxmanage registervm "${BOX_DIR}/${BOX_NAME}.vbox"

vboxmanage clonehd ${BOX_NAME}.vmdk tmp/clone.vdi --format VDI

vboxmanage modifyhd tmp/clone.vdi --type writethrough

vboxmanage clonehd tmp/clone.vdi "${BOX_DIR}/${BOX_NAME}.vmdk" --format VMDK

vboxmanage -q closemedium disk tmp/clone.vdi

rm -fr tmp

vboxmanage storagectl "${BOX_NAME}" --name LsiLogic --add scsi \
	   --controller LsiLogic

vboxmanage storageattach "${BOX_NAME}" --storagectl LsiLogic --port 0 \
	   --device 0 --type hdd --medium "${BOX_DIR}/${BOX_NAME}.vmdk"

vboxmanage modifyvm "${BOX_NAME}" --natpf1 "ssh,tcp,,22222,,22"

if [ "x$GUESTADDITIONSENABLE" == "xenable" ];then
    vboxmanage storagectl "${BOX_NAME}" --name IDE --add ide

    # Download VirtualBox GuestAdditions
    wget -c http://download.virtualbox.org/virtualbox/5.1.8/VBoxGuestAdditions_5.1.8.iso

    vboxmanage storageattach "${BOX_NAME}" --storagectl IDE --port 0 \
	       --device 0 --type dvddrive --medium \
	       VBoxGuestAdditions_5.1.8.iso
fi

if [ "x$USBPASSTHROUGHENABLE" == "xenable" ];then
    vboxmanage modifyvm "${BOX_NAME}" --usb on --usbehci on
fi

vboxmanage modifyvm "${BOX_NAME}" --memory 2048

# Set bidirectional shared clipboard
vboxmanage modifyvm "${BOX_NAME}" --clipboard bidirectional

vboxmanage startvm "${BOX_NAME}" --type headless

sleep 10

if [ ! -f "$SSHKEY" ];then
    echo -e "y\n" | ssh-keygen -t rsa -b 2048 -N "" -f ~/.ssh/id_rsa
fi

# Copy sshconfig to user ssh config for allowing password-less copy of ssh-key.
cp files/sshconfig $HOME/.ssh/config

# Copy ssh-key for password-less access of machine.
sshpass -p "vagrant" ssh-copy-id $SSHOPTION -i "$SSHKEY.pub" -p 22222 vagrant@localhost

if [ "x$GUESTADDITIONSENABLE" == "xenable" ];then
    ssh $SSHOPTION -p 22222 vagrant@localhost < scripts/guestadditions.sh
fi

if [ "x$LINUXKERNELPORTINGENABLE" == "xenable" ];then
    scp $SSHOPTION -P 22222 playbooks/linux-kernel-porting.yml vagrant@localhost:playbook.yml
    scp $SSHOPTION -P 22222 files/hosts.txt vagrant@localhost:
    ssh $SSHOPTION -p 22222 vagrant@localhost < scripts/ansible-setup.sh
fi

if [ "x$LINUXDEVICEDRIVERSENABLE" == "xenable" ];then
    scp $SSHOPTION -P 22222 playbooks/linux-device-drivers.yml vagrant@localhost:playbook.yml
    scp -r $SSHOPTION -P 22222 files vagrant@localhost:
    # ccache.tar should be available locally
    cat ccache.tar.xz | ssh $SSHOPTION -p 22222 vagrant@localhost "tar -xJf - -C ~/"
fi

# Provisioning through ansible
scp $SSHOPTION -P 22222 files/hosts.txt vagrant@localhost:
ssh $SSHOPTION -p 22222 vagrant@localhost < scripts/ansible-setup.sh

ssh $SSHOPTION -p 22222 vagrant@localhost < scripts/temporary-fix-resize.sh
ssh $SSHOPTION -p 22222 vagrant@localhost < scripts/remove-holes-fs.sh

vboxmanage controlvm "${BOX_NAME}" poweroff

sleep 5

mkdir "${EXPORT_DIR}"

vboxmanage export "${BOX_NAME}" -o "${EXPORT_DIR}/${BOX_NAME}_${VERSION}.ovf"

vagrant package --base "${BOX_NAME}" --vagrantfile vagrantfiles/linux-device-drivers --output workshop-box.tar.gz
