OBJS = add.o sub.o main.o
#CFLAGS = -Wall

calc: $(OBJS)
	gcc -o $@ $^

%.o: %.c
	gcc $(CFLAGS) -c $<

.PHONY: clean

clean:
	rm -f *.o
	rm -f calc
