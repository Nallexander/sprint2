run:
	gcc -std=c99 -Wall -ggdb -o res reseplanerare.c
	./res 

file:
	gcc -std=c99 -Wall -ggdb -o filereader filereader.c
	./filereader	
gdb:
	gcc -std=c99 -Wall -ggdb -g -o res reseplanerare.c
