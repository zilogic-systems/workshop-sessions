currdir = $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
git_url = file://$(currdir)/public/book.git

check: start git-clone
	@echo "All Checks Passed!"
	@rm -f log.txt

reset: clean
	mkdir public userA userB
	tar -x -f $(GIT_RES_DIR)/book.git.tar.gz -C public

start:
	@echo "Running checks ..."

git-clone:
	@echo -n "Check git clone from remote repo ... "
	@git -C userA/book log > log.txt 2>&1
	@test $$(git -C userA/book log | grep "^commit" | wc -l) -eq 1
	@echo "OK"

test:
	@git clone $(git_url) userA/book

clean:
	rm -fr public userA userB
	rm -f log.txt
