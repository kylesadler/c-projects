
homework1: findroots.c printprimes.c sum.c
	make findroots.o
	make printprimes.o
	make sum.o


findroots.o: findroots.c util.h
	gcc -Wall -pedantic -std=c99 util.c findroots.c -o findroots

printprimes.o: printprimes.c util.h
	gcc -Wall -pedantic -std=c99 util.c printprimes.c -o printprimes
	
sum.o: sum.c util.h
	gcc -Wall -pedantic -std=c99 util.c sum.c -o sum

clean:
	rm -f sum printprimes findroots