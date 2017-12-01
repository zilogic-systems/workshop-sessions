sudo apt-get update &&

sudo apt-get install apt-transport-https ca-certificates --no-install-recommends -y &&

# FIXME: Why is this required?
sudo dpkg --configure -a &&

sudo apt-get -f install &&

sudo apt-get install ansible --no-install-recommends -y  &&

sudo mv ~/playbook.yml /tmp/playbook.yml &&
sudo mv ~/hosts.txt /tmp/hosts.txt &&
sudo mv ~/files /tmp/ &&

sudo ansible-playbook -i /tmp/hosts.txt --connection=local /tmp/playbook.yml &&

sudo sync
