all: trabalhoPratico
 
trabalhoPratico: tp.o combination.o
	gcc -o trabalhoPratico tp.o combination.o
 
tp.o: tp.c combination.h
	gcc -o tp.o tp.c -c -W -Wall -ansi -pedantic
 
combination.o: combination.c combination.h
	gcc -o combination.o combination.c -c -W -Wall -ansi -pedantic
 
clean:
	rm -rf *.o *~ trabalhoPratico
