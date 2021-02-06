CFLAGS = -Wall -pedantic -std=c99 src/util.c

homework1: src/findroots.c src/printprimes.c src/sum.c src/util.h
	make findroots
	make printprimes
	make sum

findroots: src/findroots.c src/util.h
	gcc $(CFLAGS) src/findroots.c -o findroots

printprimes: src/printprimes.c src/util.h
	gcc $(CFLAGS) src/printprimes.c -o printprimes
	
sum: src/sum.c src/util.h
	gcc $(CFLAGS) src/sum.c -o sum

clean:
	rm -f sum printprimes findroots