CFLAGS = -Wall -pedantic -std=c99 -O2
LIBS = -lm
CC = gcc

sparse-test: xmalloc.o sparse.o sparse-test.o
	$(CC) $^ -o $@ $(LIBS)

sparse-test.o: sparse-test.c sparse.h array.h xmalloc.h
sparse.o: sparse.c sparse.h array.h xmalloc.h
xmalloc.o: xmalloc.c xmalloc.h

clean:
	rm -f *.o $(ALL) sparse-test
