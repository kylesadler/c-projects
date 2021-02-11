CFLAGS = -Wall -pedantic -std=c99

ALL = hilbert-matrix

OFILES_1 = hilbert-matrix.o xmalloc.o

CC = gcc

all: $(ALL)

hilbert-matrix: $(OFILES_1)
	$(CC) $(OFILES_1) -o $@

clean:
	rm -f $(ALL) $(OFILES_1) $(OFILES_2)

hilbert-matrix.o: hilbert-matrix.c array.h xmalloc.h
xmalloc.o: xmalloc.c xmalloc.h