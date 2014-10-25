GC = gcc
FLAGS = -Wall -ggdb -std=c99

run:
	$(CC) $(FLAGS) -o res reseplanerare.c
	./res 

file:
	gcc -std=c99 -Wall -ggdb -o filereader filereader.c
	./filereader	
gdb:
	gcc -std=c99 -Wall -ggdb -g -o res reseplanerare.c

clean:
	rm -f reseplanerare.o filereader.o 

CUnit:
	gcc -Wall CUNIT_filereader.c  -o CUNIT_filereader
