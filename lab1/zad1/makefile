CC = gcc
CFLAGS=-Wall

static:
	$(CC) $(CFLAGS) -c library.c
	ar rcs liblibrary.a library.o

shared:
	$(CC) $(CFLAGS) -c -fPIC library.c
	$(CC) $(CFLAGS) -shared -o liblibrary.so library.o

clean:
	rm -rf *.o *.a *.so tmp

