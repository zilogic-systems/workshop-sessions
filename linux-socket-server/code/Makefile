CC = gcc
CFLAGS = -Wall -Wextra -g

SRCS =  $(shell find . -name '*.c')
BINS = $(SRCS:.c=)

all: $(BINS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(BINS)

.PHONY: all clean
