CFLAGS = -Wall -pedantic -std=c99 -O2
LIBS = -lm
CC = gcc

mesh-demo: mesh-demo.o mesh-to-eps.o mesh.o problem-spec.o
	$(CC) $^ -o $@ $(LIBS)

mesh-demo.o: mesh-demo.c mesh.h problem-spec.h mesh-to-eps.h
mesh-to-eps.o: mesh-to-eps.c mesh-to-eps.h mesh.h problem-spec.h
mesh.o: mesh.c triangle.h xmalloc.h array.h mesh.h problem-spec.h
problem-spec.o: problem-spec.c problem-spec.h array.h xmalloc.h
triangle.o: triangle.c triangle.h
xmalloc.o: xmalloc.c xmalloc.h

clean:
	mv triangle.o tmp && rm -f *.o mesh-demo; mv tmp triangle.o
