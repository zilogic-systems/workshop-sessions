check: start author-in-chapter-1 author-in-chapter-2 commit-created all-committed
	@echo "All Checks Passed!"
	@rm -f log.txt

reset: clean
	tar -x -f $(GIT_RES_DIR)/book.tar.gz

start:
	@echo "Running checks ..."

author-in-chapter-1:
	@cat book/chapter-1.txt | grep -i stallman > log.txt 2>&1

author-in-chapter-2:
	@cat book/chapter-2.txt | grep -i stallman > log.txt 2>&1

commit-created:
	@git -C book log > log.txt 2>&1
	@test $$(git -C book log | grep "^commit" | wc -l) -eq 2

all-committed:
	@test $$(git -C book diff | wc -l) -eq 0

clean:
	rm -fr book
	rm -f log.txt
