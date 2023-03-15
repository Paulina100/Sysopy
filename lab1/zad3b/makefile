CC = gcc
CFLAGS=-Wall

all: tests clean

tests:
	for lib in static shared dynamic ; do \
		for o in O0 O1 Os ; do \
			make $$lib OPTIMIZATION=-$$o; \
		done ; \
	done

static:
	make -C ../zad1 static
	make -C ../zad2 main 
	$(CC) $(CFLAGS) $(OPTIMIZATION) ../zad2/main.o ../zad1/liblibrary.a -o main.out
	./main.out < ../zad3a/tester > test_results/results_static_$(OPTIMIZATION).txt

shared:
	make -C ../zad1 shared
	$(CC) $(CFLAGS) $(OPTIMIZATION) ../zad2/main.c -l library -L ../zad1 -Wl,-rpath,../zad1 -o main.out
	./main.out < ../zad3a/tester > test_results/results_shared_$(OPTIMIZATION).txt

dynamic:
	make -C ../zad1 shared
	$(CC) $(CFLAGS) $(OPTIMIZATION) ../zad2/main.c -ldl -D LIB_DYNAMIC -o main.out
	./main.out < ../zad3a/tester > test_results/results_dynamic_$(OPTIMIZATION).txt

clean:
	make -C ../zad2 clean
	rm -rf tmp *.out