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

createstatlib: reseplanerare.o filereader.o
	ar rs resstatlib.a reseplanerare.o filereader.o

runstatlib: createstatlib
	$(GC) $(FLAGS) -o reseplanerare interface.c resstatlib.a
	./reseplanerare

createdynlib:
	$(GC) $(FLAGS) -fPIC -c reseplanerare.c
	$(GC) $(FLAGS) -fPIC -c filereader.c
	$(GC) -shared -o resdynlib.so reseplanerare.o filereader.o

rundynlib: createdynlib
	$(GC) -o reseplanerare interface.c resdynlib.so
	./reseplanerare	

clean:
	rm -f reseplanerare filereader.o reselib.a

.PHONY: run
