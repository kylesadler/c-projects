CFLAGS = -Wall -pedantic -std=c99 -O2
LIBS = -lm

ALL = heat-explicit heat-implicit heat-crank-nicolson

all: $(ALL)

heat-explicit: xmalloc.o problem-spec.o heat-explicit.o
	$(CC) $^ -o $@ $(LIBS)

heat-implicit: xmalloc.o problem-spec.o heat-implicit.o
	$(CC) $^ -o $@ $(LIBS)

heat-crank-nicolson: xmalloc.o problem-spec.o heat-crank-nicolson.o
	$(CC) $^ -o $@ $(LIBS)

clean:
	rm -f *.gv *.o $(ALL)
