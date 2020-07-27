check: start commit-created unstaged-changes
	@echo "All Checks Passed!"
	@rm -f log.txt

reset: clean
	tar -x -f $(GIT_RES_DIR)/tangled-working-copy.tar.gz

start:
	@echo "Running checks ..."

commit-created:
	@echo -n "Check commited staged changes ... "
	@git -C book log > log.txt 2>&1
	@test $$(git -C book log | grep "^commit" | wc -l) -gt 1
	@echo "OK"

unstaged-changes:
	@echo -n "Check unstaged changes ... "
	@test $$(git -C book diff | grep "XXX" | wc -l) -eq 1
	@test $$(git -C book diff | grep "fredom" | wc -l) -eq 0
	@echo "OK"

test:
	@git -C book stage chapter-1.txt
	@git -C book stage --patch chapter-2.txt
	@git -C book commit -m "Fixed spelling freedom"

clean:
	rm -fr book
	rm -f log.txt
