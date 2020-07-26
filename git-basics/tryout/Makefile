exercises = ex1 ex2 ex3 ex4 ex5 ex6 ex7 ex8 ex9

reset:
	for ex in $(exercises); do make -C $${ex} reset; done

clean:
	for ex in $(exercises); do make -C $${ex} clean; done
	find . -name "*~" -delete
