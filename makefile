all: tp
 
tp: main.o combination.o paradigms.o
	c99 -o tp main.o combination.o paradigms.o
 
main.o: main.c combination.h paradigms.h
	c99 -o main.o main.c -c -W -Wall
 
combination.o: combination.c combination.h
	c99 -o combination.o combination.c -c -W -Wall
 
paradigms.o: paradigms.c paradigms.h
	c99 -o paradigms.o paradigms.c -c -W -Wall

clean:
	rm -rf *.o *~ tp
