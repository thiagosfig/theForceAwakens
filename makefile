CC=clang
CFLAGS=-Wall -g

all: tp

combination.o: combination.c combination.h
	$(CC) $(CFLAGS) -c combination.c

tp: tp.c combination.o
	$(CC) $(CFLAGS) -o $@ $^