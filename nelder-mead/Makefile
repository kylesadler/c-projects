CC = gcc
CFLAGS = -Wall -pedantic -std=c99
LIBS = -lm
ALL = rank-vertices-test nelder-mead demo-1D demo-2D demo-constrained demo-energy

all: $(ALL)

clean:
	rm -f $(ALL) demo-1D.o demo-2D.o demo-constrained.o demo-energy.o nelder-mead.o

demo-1D.o: demo-1D.c nelder-mead.h
demo-2D.o: demo-2D.c nelder-mead.h
demo-constrained.o: demo-constrained.c nelder-mead.h
demo-energy.o: demo-energy.c nelder-mead.h
nelder-mead.o: nelder-mead.c array.h xmalloc.h nelder-mead.h
xmalloc.o: xmalloc.c xmalloc.h

