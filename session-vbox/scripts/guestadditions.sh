sudo mount /dev/dvd /mnt &&

# Delay is required due to some race condition which causes GPG
# signature verification error when updating package lists.
sleep 10 &&

sudo apt-get update &&

sudo apt-get install build-essential bzip2 \
    linux-headers-586 \
    ncurses-base --no-install-recommends -y &&

sudo sh /mnt/VBoxLinuxAdditions.run --nox11 &&

sudo umount /mnt &&

sudo apt-get clean

sudo usermod -aG vboxsf vagrant &&

# sudo echo "shared /media/sf_shared vboxsf uid=1000,gid=1000,rw,nodev 0 0" >> /etc/fstab &&

sudo sync
