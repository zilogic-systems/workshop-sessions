OBJS = add.o sub.o main.o
CFLAGS = -Wall

calc: $(OBJS)
	gcc -o calc $(OBJS)

add.o: add.c
	gcc $(CFLAGS) -c add.c

sub.o: sub.c
	gcc $(CFLAGS) -c sub.c

main.o: main.c
	gcc $(CFLAGS) -c main.c
