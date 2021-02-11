CFLAGS = -Wall -pedantic -std=c99

ALL = hilbert-matrix test-array

OFILES_1 = hilbert-matrix.o xmalloc.o
OFILES_2 = test-array.o xmalloc.o

CC = gcc

all: $(ALL)

hilbert-matrix: $(OFILES_1)
	$(CC) $(OFILES_1) -o $@

test-array: $(OFILES_2)
	$(CC) $(OFILES_2) -o $@

clean:
	rm -f $(ALL) $(OFILES_1) $(OFILES_2)

hilbert-matrix.o: hilbert-matrix.c array.h xmalloc.h
xmalloc.o: xmalloc.c xmalloc.h
test-array.o: test-array.c array.h xmalloc.h