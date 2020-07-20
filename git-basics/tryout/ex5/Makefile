check: start switch-branch spelling-fix all-committed
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

start:
	@echo "Running checks ..."

switch-branch:
	@echo -n "Check branch switched to master ... "
	@git -C book branch | grep "* master" > log.txt 2>&1
	@echo "OK"

spelling-fix:
	@echo -n "Check spelling fix for long ... "
	@test $$(grep long book/chapter-3.txt | wc -l) -eq 1
	@test $$(git -C book log | grep "^commit" | wc -l) -eq 4
	@echo "OK"

all-committed:
	@echo -n "Checking all changes committed ... "
	@test $$(git -C book diff | wc -l) -eq 0
	@echo "OK"

clean:
	rm -fr book
	rm -f log.txt
