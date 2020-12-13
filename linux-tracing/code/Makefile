targets = fibonacci foobar lfoobar libprof.so myfopen.so sleeptest test

all: $(targets)

fibonacci: fibonacci.c
	gcc -pg -o fibonacci fibonacci.c

foobar: foobar.c
	gcc -pg -o foobar foobar.c

lfoobar: lfoobar.c
	gcc -pg -o lfoobar lfoobar.c

libprof.so: mcount.S
	gcc -shared mcount.S -o libprof.so

myfopen.so: myfopen.c
	gcc -shared myfopen.c -o myfopen.so

sleeptest: sleeptest.c
	gcc -pg sleeptest.c -o sleeptest

test: test.c
	gcc -pg test.c -o test

clean:
	rm -f $(targets)
