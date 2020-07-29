currdir = $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
git_url = file://$(currdir)/public/book.git

check: start commit-userA verify-userB
	@echo "All Checks Passed!"
	@rm -f log.txt

reset: clean
	mkdir public userA userB
	tar -x -f $(GIT_RES_DIR)/book.git.tar.gz -C public
	git clone $(git_url) userA/book

start:
	@echo "Running checks ..."

commit-userA:
	@echo -n "Check fixed spelling freedom in userA ... "
	@cat userA/book/chapter-1.txt | grep -i freedom > log.txt 2>&1
	@test $$(git -C userA/book log | grep '^commit' | wc -l) -eq 2
	@echo "OK"

verify-userB:
	@echo -n "Verify fixed spelling freedom in userB ... "
	@cat userB/book/chapter-1.txt | grep -i freedom > log.txt 2>&1
	@test $$(git -C userB/book log | grep '^commit' | wc -l) -eq 2
	@echo "OK"

test:
	@sed -i 's/fredom/freedom/' userA/book/chapter-1.txt
	@sed -i 's/fredom/freedom/' userA/book/chapter-2.txt
	@git -C userA/book commit -a -m "Fixed spelling freedom"
	@git -C userA/book push origin master:master
	@git clone $(git_url) userB/book

clean:
	rm -fr public userA userB
	rm -f log.txt
