foo: foo.o bar.o
	gcc -o foo *.o

foo.o: foo.c bar.h
	gcc -c foo.c

bar.o: bar.h bar.c
	gcc -c bar.c
