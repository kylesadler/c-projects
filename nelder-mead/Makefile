CC = gcc
CFLAGS = -Wall -pedantic -std=c99
LIBS = -lm
ALL = rank-vertices-test demo-1D demo-2D demo-constrained demo-energy

OFILES = nelder-mead.o xmalloc.o

all: $(ALL)

rank-vertices-test: rank-vertices-test.c
	$(CC) rank-vertices-test.c -o $@

demo-1D: $(OFILES)
	$(CC) $@.c $(OFILES) -o $@

demo-2D: $(OFILES)
	$(CC) $@.c $(OFILES) -o $@

demo-constrained: $(OFILES)
	$(CC) $@.c $(OFILES) -o $@

demo-energy: $(OFILES)
	$(CC) $@.c $(OFILES) -o $@

clean:
	rm -f $(ALL) demo-1D.o demo-2D.o demo-constrained.o demo-energy.o nelder-mead.o xmalloc.o

demo-1D.o: demo-1D.c nelder-mead.h
demo-2D.o: demo-2D.c nelder-mead.h
demo-constrained.o: demo-constrained.c nelder-mead.h
demo-energy.o: demo-energy.c nelder-mead.h
nelder-mead.o: nelder-mead.c array.h xmalloc.h nelder-mead.h
rank-vertices-test.o: rank-vertices-test.c
xmalloc.o: xmalloc.c xmalloc.h
