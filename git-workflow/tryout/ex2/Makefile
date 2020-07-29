check: start create-branch year-fix spell-fix rebase
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
	@echo -n "Check fixed missing year 1984 ... "
	@grep 1984 book/chapter-3.txt > log.txt 2>&1
	@test $$(grep 1984 book/chapter-3.txt | wc -l) -eq 1
	@echo "OK"

spell-fix:
	@echo -n "Check fixed spelling long ... "
	@grep long book/chapter-3.txt > log.txt 2>&1
	@test $$(grep long book/chapter-3.txt | wc -l) -eq 1
	@echo "OK"

rebase:
	@echo -n "Check incorporate changes from master ... "
	@git -C book log | grep "^commit" > log.txt 2>&1
	@test $$(git -C book log | grep "^commit" | wc -l) -eq 3
	@echo "OK"

test:
	@git -C book checkout -b year-fix
	@sed -i '0,/????/s//1984/' book/chapter-3.txt
	@git -C book commit -a -m "Fixed missing year 1984"
	@git -C book checkout master
	@sed -i 's/lang/long/' book/chapter-3.txt
	@git -C book commit -a -m "Fixed spelling long"
	@git -C book checkout year-fix
	@git -C book rebase master

clean:
	rm -fr book
	rm -f log.txt
