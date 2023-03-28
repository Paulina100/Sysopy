
all: test clean

sys:
	gcc translate.c -o translate.out -D SYS

lib:
	gcc translate.c -o translate.out -D LIB

test: 
	echo "SYS" > pomiar_zad1.txt
	echo "SYS" > poprawnosc_zad1.txt
	make sys
	./tests/time_test >> pomiar_zad1.txt
	./tests/correctness_test >> poprawnosc_zad1.txt

	make clean

	echo "LIB" >> pomiar_zad1.txt
	echo "LIB" >> poprawnosc_zad1.txt
	make lib
	./tests/time_test >> pomiar_zad1.txt
	./tests/correctness_test >> poprawnosc_zad1.txt

clean:
	rm -fr *.out files/out*