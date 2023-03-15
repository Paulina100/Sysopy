CC = gcc
CFLAGS=-Wall

all: tests clean

tests: static shared dynamic

static:
	make -C ../zad2 static 
	../zad2/main.out < tester > test_results/results_static.txt

shared:
	make -C ../zad2 shared
	../zad2/main.out < tester > test_results/results_shared.txt

dynamic:
	make -C ../zad2 dynamic
	../zad2/main.out < tester > test_results/results_dynamic.txt

clean:
	make -C ../zad2 clean
	rm -rf tmp