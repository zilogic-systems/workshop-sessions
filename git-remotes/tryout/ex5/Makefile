currdir = $(dir $(realpath $(firstword $(MAKEFILE_LIST))))
git_url = file://$(currdir)/public/book.git

check: start commit-userA verify-origin verify-userB
	@echo "All Checks Passed!"
	@rm -f log.txt

reset: clean
	mkdir public userA userB
	tar -x -f $(GIT_RES_DIR)/book.git.tar.gz -C public
	git clone $(git_url) userA/book
	sed -i 's/fredom/freedom/' userA/book/chapter-1.txt
	sed -i 's/fredom/freedom/' userA/book/chapter-2.txt
	git -C userA/book commit -a -m "Fixed spelling freedom"
	git -C userA/book push origin master:master
	git clone $(git_url) userB/book

start:
	@echo "Running checks ..."

commit-userA:
	@echo -n "Check fixed missing year 1984 in userA ... "
	@test $$(grep 1984 userA/book/chapter-3.txt | wc -l) -eq 1
	@test $$(git -C userA/book log | grep "^commit" | wc -l) -eq 3
	@echo "OK"

verify-origin:
	@echo -n "Verify fixed missing year 1984 in userB origin/master ... "
	@git -C userB/book checkout origin/master > log.txt 2>&1
	@test $$(grep 1984 userB/book/chapter-3.txt | wc -l) -eq 1
	@test $$(git -C userB/book log | grep "^commit" | wc -l) -eq 3
	@echo "OK"

verify-userB:
	@echo -n "Verify fixed missing year 1984 in userB ... "
	@git -C userB/book checkout master > log.txt 2>&1
	@test $$(grep 1984 userB/book/chapter-3.txt | wc -l) -eq 1
	@test $$(git -C userB/book log | grep "^commit" | wc -l) -eq 3
	@echo "OK"

test:
	@sed -i '0,/????/s//1984/' userA/book/chapter-3.txt
	@git -C userA/book commit -a -m "Fixed missing year 1984"
	@git -C userA/book push origin master:master
	@git -C userB/book fetch origin master
	@git -C userB/book checkout master
	@git -C userB/book merge origin/master

clean:
	rm -fr public userA userB
	rm -f log.txt
