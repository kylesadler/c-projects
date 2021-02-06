CFLAGS = -Wall -pedantic -std=c99

ALL = xmalloc-demo-1 xmalloc-demo-2

OFILES_1 = xmalloc-demo-1.o xmalloc.o
OFILES_2 = xmalloc-demo-2.o xmalloc.o

CC = gcc

all: $(ALL)

xmalloc-demo-1: $(OFILES_1)
	$(CC) $(OFILES_1) -o $@

xmalloc-demo-2: $(OFILES_2)
	$(CC) $(OFILES_2) -o $@

clean:
	rm -f $(ALL) $(OFILES_1) $(OFILES_2)

xmalloc-demo-1.o: xmalloc-demo-1.c xmalloc.h
xmalloc-demo-2.o: xmalloc-demo-2.c
xmalloc.o: xmalloc.c xmalloc.h
xmalloc.o: xmalloc.h