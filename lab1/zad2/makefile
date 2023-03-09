CC = gcc
CFLAGS=-Wall

all: static shared clean

static:
	make -C ../zad1 static

shared:
	make -C ../zad1 shared

main:
	$(CC) $(CFLAGS) -c library.c
	$(CC) $(CFLAGS) -c main.c
	$(CC) $(CFLAGS) main.o library.o -o main.out
	./main.out


main_static: 
	$(CC) $(CFLAGS) main.o liblibrary.a –o main.out
	./main


clean:
	make -C ../zad1 clean
	rm -rf *.o *.a *.so tmp