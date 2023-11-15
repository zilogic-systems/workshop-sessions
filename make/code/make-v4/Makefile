OBJS = add.o sub.o main.o
CFLAGS = -Wall

calc: $(OBJS)
	gcc -o $@ $^

%.o: %.c
	gcc $(CFLAGS) -c $<

clean:
	rm *.o
	rm calc
