check: start remove-file
	@echo "All Checks Passed!"
	@rm -f log.txt

reset:  clean
	tar -x -f $(GIT_RES_DIR)/book.tar.gz
	touch book/chapter-4.txt
	git -C book add chapter-4.txt
	git -C book commit -a -m "Added a Chapter 4."

start:
	@echo "Running checks ..."

remove-file:
	@echo -n "Check file chapter-4.txt removed ... "
	@test $$(git -C book ls-files | grep "chapter-4.txt" | wc -l) -eq 0
	@git -C book log > log.txt 2>&1
	@test $$(git -C book log | grep "^commit" | wc -l) -eq 3
	@echo "OK"

test:
	@git -C book rm chapter-4.txt > log.txt 2>&1
	@git -C book commit -a -m "Removed Chapter 4."

clean:
	rm -fr book
	rm -f log.txt
