check: start create-branch year-fix fast-forward
	@echo "All Checks Passed!"
	@rm -f log.txt

reset: clean
	tar -x -f $(GIT_RES_DIR)/book.tar.gz

start:
	@echo "Running checks ..."

create-branch:
	@echo -n "Check year-fix branch created ... "
	@git -C book branch > log.txt 2>&1
	@test $$(git -C book branch | grep "year-fix" | wc -l) -eq 1
	@echo "OK"

year-fix:
	@echo -n "Check missing year 1984 fixed in year-fix branch ... "
	@git -C book checkout year-fix > log.txt 2>&1
	@test $$(grep 1984 book/chapter-3.txt | wc -l) -eq 1
	@test $$(git -C book log | grep "^commit" | wc -l) -eq 2
	@echo "OK"

fast-forward:
	@echo -n "Check Fast-forward merge ... "
	@git -C book checkout master > log.txt 2>&1
	@git -C book reflog > log.txt 2>&1
	@test $$(git -C book reflog | grep "Fast-forward"| wc -l) -eq 1
	@echo "OK"

test:
	@git -C book checkout -b year-fix
	@sed -i '0,/????/s//1984/' book/chapter-3.txt
	@git -C book commit -a -m "Fixed missing year 1984"
	@git -C book checkout master
	@git -C book merge year-fix

clean:
	rm -fr book
	rm -f log.txt
