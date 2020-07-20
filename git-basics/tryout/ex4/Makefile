check: start create-branch year-fix
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

start:
	@echo "Running checks ..."

create-branch:
	@git -C book branch | grep "* year-fix" > log.txt 2>&1

year-fix:
	@git -C book diff master | grep 1984  > log.txt 2>&1
	@test $$(grep 1984 book/chapter-3.txt | wc -l) -eq 1

clean:
	rm -fr book
	rm -f log.txt
