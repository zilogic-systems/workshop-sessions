SOURCES = $(shell ls libmath/*.c)
OBJS = $(patsubst %.c,%.o,$(SOURCES))

all: libmath.a libmath.so
	
libmath.a: $(OBJS)
	ar -rc $@ $^

libmath/%.o: %.c
	gcc -c $^

libmath.so: $(SOURCES)
	gcc -fPIC $^ --shared -o $@

clean:
	rm -f libmath/*.o
	rm -f *.o
	rm -f libmath/libmath.*
	rm -f *.a *.so
	rm -f calc

.PHONY: clean
