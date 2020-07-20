check: start spelling-in-chapter-1 spelling-in-chapter-2 commit-created all-committed
	@echo "All Checks Passed!"
	@rm -f log.txt

reset: clean
	tar -x -f $(GIT_RES_DIR)/book.tar.gz
	sed -i "3iBy Richard M. Stallman\n" book/chapter-1.txt
	sed -i "3iBy Richard M. Stallman\n" book/chapter-2.txt
	git -C book commit -a -m "Fixed author line"

start:
	@echo "Running checks ..."

spelling-in-chapter-1:
	@cat book/chapter-1.txt | grep -i freedom > log.txt 2>&1

spelling-in-chapter-2:
	@cat book/chapter-2.txt | grep -i freedom > log.txt 2>&1

commit-created:
	@git -C book log > log.txt 2>&1
	@test $$(git -C book log | grep "^commit" | wc -l) -eq 3

all-committed:
	@test $$(git -C book diff | wc -l) -eq 0

clean:
	rm -fr book
	rm -f log.txt
