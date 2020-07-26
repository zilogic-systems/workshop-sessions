check: start create-file commit-created
	@echo "All Checks Passed!"
	@rm -f log.txt

reset:  clean
	tar -x -f $(GIT_RES_DIR)/book.tar.gz

start:
	@echo "Running checks ..."

create-file:
	@echo -n "Check file chapter-4.txt added ... "
	@git -C book ls-files --error-unmatch chapter-4.txt > log.txt 2>&1
	@test $$(git -C book ls-files | grep "chapter-4.txt" | wc -l) -eq 1
	@echo "OK"

commit-created:
	@echo -n "Check chapter-4.txt committed ... "
	@git -C book log > log.txt 2>&1
	@test $$(git -C book log | grep "^commit" | wc -l) -eq 2
	@echo "OK"

test:
	@echo "" > book/chapter-4.txt
	@git -C book add chapter-4.txt > log.txt 2>&1
	@git -C book commit -a -m "Added a Chapter 4."

clean:
	rm -fr book
	rm -f log.txt
