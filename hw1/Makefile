
homework1: src/findroots.c src/printprimes.c src/sum.c
	make findroots
	make printprimes
	make sum

findroots: src/findroots.c src/util.h
	gcc -Wall -pedantic -std=c99 src/util.c src/findroots.c -o findroots

printprimes: src/printprimes.c src/util.h
	gcc -Wall -pedantic -std=c99 src/util.c src/printprimes.c -o printprimes
	
sum: src/sum.c src/util.h
	gcc -Wall -pedantic -std=c99 src/util.c src/sum.c -o sum

clean:
	rm -f sum printprimes findroots