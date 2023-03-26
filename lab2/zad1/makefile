
all: test clean

sys:
	gcc translate.c -o translate.out -D SYS
	./translate.out a b ./files/in_file1.txt ./files/out_file1_sys.txt
	tr a b < ./files/in_file1.txt > tmp
	diff -s tmp ./files/out_file1_sys.txt

lib:
	gcc translate.c -o translate.out -D LIB
	./translate.out a b ./files/in_file1.txt ./files/out_file1_lib.txt
	tr a b < ./files/in_file1.txt > tmp
	diff -s tmp ./files/out_file1_lib.txt

test: sys lib

clean:
	rm -fr *.out files/out_file1.txt