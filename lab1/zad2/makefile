CC = gcc
CFLAGS=-Wall

static:
	make -C ../zad1 static
	make main
	$(CC) $(CFLAGS) main.o ../zad1/liblibrary.a -o main.out

shared:
	make -C ../zad1 shared
	$(CC) $(CFLAGS) main.c -l library -L ../zad1 -Wl,-rpath,../zad1 -o main.out

dynamic:
	make -C ../zad1 shared
	$(CC) $(CFLAGS) main.c -ldl -D LIB_DYNAMIC -o main.out

main:
	$(CC) $(CFLAGS) -c main.c

clean:
	make -C ../zad1 clean
	rm -rf *.o *.out