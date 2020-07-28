check: start create-branch merge-commit
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

merge-commit:
	@echo -n "Check merge commit ... "
	@test $$(git -C book log | grep "^commit" | wc -l) -eq 4
	@echo "OK"

test:
	@git -C book checkout -b year-fix
	@sed -i 's/????/1984/' book/chapter-3.txt
	@git -C book commit -a -m "Fixed missing year 1984"
	@git -C book checkout master
	@sed -i 's/????/1983/' book/chapter-3.txt
	@git -C book commit -a -m "Fixed missing year 1983"
	@git -C book merge year-fix

clean:
	rm -fr book
	rm -f log.txt
