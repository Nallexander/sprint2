GC = gcc
FLAGS = -Wall -ggdb -std=c99


filereader.o: filereader.c  
	$(GC) $(FLAGS) -c filereader.c

reseplanerare.o: reseplanerare.c 
	$(GC) $(FLAGS) -c reseplanerare.c 

interface.o: interface.c reseplanerare.o filereader.o
	$(GC) $(FLAGS) -o reseplanerare interface.c reseplanerare.o filereader.o


run: interface.o
	./reseplanerare 

clean:
	rm -f reseplanerare filereader.o 

.PHONY: run
