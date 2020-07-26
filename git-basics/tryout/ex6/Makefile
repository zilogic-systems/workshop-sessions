check: start merge-branch
	@echo "All Checks Passed!"
	@rm -f log.txt

reset:  clean
	tar -x -f $(GIT_RES_DIR)/book.tar.gz
	sed -i "3iBy Richard M. Stallman\n" book/chapter-1.txt
	sed -i "3iBy Richard M. Stallman\n" book/chapter-2.txt
	git -C book commit -a -m "Fixed author line."
	sed -i "s/fredom/freedom/g" book/chapter-1.txt
	sed -i "s/fredom/freedom/g" book/chapter-2.txt
	git -C book commit -a -m "Fixed spelling of freedom."
	git -C book checkout -b year-fix
	sed -i "s/????/1984/" book/chapter-3.txt
	git -C book commit -a -m "Fixed missing year."
	git -C book checkout master
	sed -i "s/lang/long/" book/chapter-3.txt
	git -C book commit -a -m "Fixed spelling of long."

start:
	@echo "Running checks ..."

merge-branch:
	@echo -n "Check merge year-fix branch to master ... "
	@git -C book log master > log.txt 2>&1
	@git -C book show master | grep "^Merge" > log.txt 2>&1
	@test $$(git -C book diff master year-fix | grep "^[+-].*1984" | wc -l) -eq 0
	@echo "OK"

test:
	@git -C book merge year-fix > log.txt 2>&1

clean:
	rm -fr book
	rm -f log.txt
