all: trabalhoPratico
 
trabalhoPratico: tp.o combination.o
	c99 -o trabalhoPratico tp.o combination.o
 
tp.o: tp.c combination.h
	c99 -o tp.o tp.c -c -W -Wall
 
combination.o: combination.c combination.h
	c99 -o combination.o combination.c -c -W -Wall
 
clean:
	rm -rf *.o *~ trabalhoPratico
