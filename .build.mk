packages = python-pip asciidoc dia inkscape source-highlight

before_install:
	sudo apt-get update

install:
	sudo apt-get install -y --no-install-recommends $(packages)
	sudo pip install zdrive-push

script:
	make
