all: tp
 
tp: main.o combination.o paradigms.o paradigmsUtil.o
	gcc -o tp main.o combination.o paradigms.o paradigmsUtil.o
 
main.o: main.c combination.h paradigms.h
	gcc -o main.o main.c -c -W -Wall
 
combination.o: combination.c combination.h
	gcc -o combination.o combination.c -c -W -Wall
 
paradigms.o: paradigms.c paradigms.h
	gcc -o paradigms.o paradigms.c -c -W -Wall
	
paradigmsUtil.o: paradigmsUtil.c paradigmsUtil.h
	gcc -o paradigmsUtil.o paradigmsUtil.c -c -W -Wall
	
clean:
	rm -rf *.o *~ tp
