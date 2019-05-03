packages = python-pip asciidoc dia inkscape source-highlight

before_install:
	sudo apt-get update

install:
	sudo apt-get install -y --no-install-recommends $(packages)
	echo $$PIP_FIND_LINKS
	sudo -H pip install zdrive-push

script:
	make
	make install

after_success:
	zdrive-push workshop-sessions $(BUILD_TYPE) $(BUILD_VERSION) misc build/*

