== Setting up the Box through Vagrant

---------------
$ vagrant box add --name "workshop" /path/to/workshop-box.tar.gz
$ vagrant init workshop
$ vagrant up
---------------

== Setting up the Box through VirtualBox

 * Import *.ovf file from VirtualBox GUI.
 * Manually setup shared folders with Auto-mount flag set.
 * Start Box.

== Procedure to update Box after build is complete

------------
$ apt-get update
$ apt-get install <workshop-specific-packages>
$ sudo ansible-playbook -i /usr/share/ansible-setup/hosts.txt \
       			--connection=local		      \
			/usr/share/ansible-setup/playbook.yml
------------

 * In case of any changes in VirtualBox settings, this can be done
   through the `vboxmanage` command.
