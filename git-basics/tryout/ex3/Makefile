check: start checkout-rev
	@echo "All Checks Passed!"
	@rm -f log.txt

reset: clean
	tar -x -f $(GIT_RES_DIR)/book.tar.gz
	sed -i "3iBy Richard M. Stallman\n" book/chapter-1.txt
	sed -i "3iBy Richard M. Stallman\n" book/chapter-2.txt
	git -C book commit -a -m "Fixed author line."
	sed -i "s/fredom/freedom/g" book/chapter-1.txt
	sed -i "s/fredom/freedom/g" book/chapter-2.txt
	git -C book commit -a -m "Fixed spelling of freedom."

start:
	@echo "Running checks ..."

checkout-rev:
	@git -C book log > log.txt 2>&1
	@test $$(git -C book log | grep "^commit" | wc -l) -eq 1

clean:
	rm -fr book
	rm -f log.txt
