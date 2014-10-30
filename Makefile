GC = gcc
FLAGS = -Wall -ggdb -std=c99


filereader.o: filereader.c  
	$(GC) $(FLAGS) -c filereader.c

reseplanerare.o: reseplanerare.c filereader.o
	$(GC) $(FLAGS) -o reseplanerare reseplanerare.c filereader.o
run: reseplanerare.o
	./reseplanerare 

clean:
	rm -f reseplanerare filereader.o 

.PHONY: run
