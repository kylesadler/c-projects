CFLAGS = -Wall -pedantic -std=c99
ALL = findroots printprimes sum

all: $(ALL)

findroots: src/findroots.c src/util.h
	gcc $(CFLAGS) src/util.c src/findroots.c -o findroots

printprimes: src/printprimes.c src/util.h
	gcc $(CFLAGS) src/util.c src/printprimes.c -o printprimes
	
sum: src/sum.c src/util.h
	gcc $(CFLAGS) src/util.c src/sum.c -o sum

clean:
	rm -f sum printprimes findroots