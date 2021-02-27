CC = gcc
CFLAGS = -Wall -pedantic -std=c99
ALL = rank-vertices-test nelder-mead demo-1D demo-2D demo-constrained demo-energy

# add -lm for math library 

all: $(ALL)

clean:
	rm -f $(ALL)

demo-1D: demo-1D.c nelder-mead.h
demo-2D: demo-2D.c nelder-mead.h
demo-constrained: demo-constrained.c nelder-mead.h
demo-energy: demo-energy.c nelder-mead.h
nelder-mead: nelder-mead.c array.h xmalloc.h nelder-mead.h
xmalloc.o: xmalloc.c xmalloc.h

