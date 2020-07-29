check: start spelling-in-chapter1 spelling-in-chapter2 amend-commit
	@echo "All Checks Passed!"
	@rm -f log.txt

reset: clean
	tar -x -f $(GIT_RES_DIR)/book.tar.gz

start:
	@echo "Running checks ..."

spelling-in-chapter1:
	@echo -n "Check spelling freedom fixed in chapter1 ... "
	@cat book/chapter-1.txt | grep -i freedom > log.txt 2>&1
	@echo "OK"

spelling-in-chapter2:
	@echo -n "Check spelling freedom fixed in chapter2 ... "
	@cat book/chapter-2.txt | grep -i freedom > log.txt 2>&1
	@echo "OK"

amend-commit:
	@echo -n "Check amending commits ... "
	@git -C book log > log.txt 2>&1
	@test $$(git -C book log | grep "^commit" | wc -l) -eq 2
	@echo "OK"

test:
	@sed -i 's/fredom/freedom/g' book/chapter-1.txt
	@git -C book commit -a -m "Fixed spelling freedom"
	@sed -i 's/fredom/freedom/g' book/chapter-2.txt
	@git -C book commit --amend -m "Fixed spelling freedom"

clean:
	rm -fr book
	rm -f log.txt
