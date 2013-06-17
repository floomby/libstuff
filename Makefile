CFLAGS=-Wall -std=c99
ARFLAGS=-cvq

SRCS=$(wildcard src/*.c)
OBJS=$(SRCS:.c=.o)

$(CC)=gcc

libstuff: objects
	mv *.o src/
	ar $(ARFLAGS) libstuff.a $(OBJS)

objects: $(SRCS)
	$(CC) $^ -c $(CFLAGS)

test: libstuff tools/tester.c
	$(CC) tools/tester.c -o tester -L ./ -lstuff $(CFLAGS)

clean:
	rm $(OBJS)
