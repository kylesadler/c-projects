INCLUDE = ${SuiteSparse}/include
#INCLUDE = /share/apps/SuiteSparse/5.8.1/gcc/include
CFLAGS = -Wall -pedantic -std=c99 -O2 -I$(INCLUDE)
LIBS = -L/share/apps/SuiteSparse/5.8.1/gcc/lib -lumfpack
ALL = umfpack-demo1 umfpack-demo2 umfpack-demo3

all: $(ALL)

umfpack-demo1: xmalloc.o sparse.o umfpack-demo1.o
	$(CC) $^ $(LIBS) -o $@
	
umfpack-demo2: xmalloc.o sparse.o umfpack-demo2.o
	$(CC) $^ $(LIBS) -o $@

umfpack-demo3: xmalloc.o umfpack-demo3.o
	$(CC) $^ $(LIBS) -o $@

clean:
	rm -f *.o $(ALL)

sparse.o: sparse.c sparse.h array.h xmalloc.h
umfpack-demo1.o: umfpack-demo1.c sparse.h array.h xmalloc.h
umfpack-demo2.o: umfpack-demo2.c sparse.h array.h xmalloc.h
umfpack-demo3.o: umfpack-demo3.c array.h xmalloc.h
xmalloc.o: xmalloc.c xmalloc.h