# Implicit Patterns

OBJS = add.o sub.o main.o
CFLAGS = -Wall

calc: $(OBJS)
	gcc -o $@ $^

.PHONY: clean

clean:
	rm -f *.o
	rm -f calc
