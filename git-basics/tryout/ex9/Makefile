check: start repo git-files initial-commit
	@echo "All Checks Passed!"
	@rm -f log.txt

reset:  clean

start:
	@echo "Running checks ..."

repo:
	@echo -n "Check proj reprository ... "
	@git -C proj/.git rev-parse --is-inside-git-dir > log.txt 2>&1
	@test $$(git -C proj/.git rev-parse --is-inside-git-dir)
	@echo "OK"

git-files:
	@echo -n "Check git files 'hello.txt' & 'goodbye.txt' ... "
	@git -C proj ls-files --error-unmatch hello.txt goodbye.txt > log.txt 2>&1
	@test $$(git -C proj ls-files | grep "hello.txt" | wc -l) -eq 1
	@test $$(git -C proj ls-files | grep "goodbye.txt" | wc -l) -eq 1
	@echo "OK"

initial-commit:
	@echo -n "Check initial commit ... "
	@git -C proj log > log.txt 2>&1
	@test $$(git -C proj log | grep "^commit" | wc -l) -eq 1
	@echo "OK"

test:
	@mkdir proj
	@git -C proj init
	@echo "Hello World" > proj/hello.txt
	@echo "Good Bye" > proj/goodbye.txt
	@git -C proj add hello.txt goodbye.txt
	@git -C proj commit -a -m "Initial project folder"

clean:
	rm -fr proj
	rm -f log.txt
