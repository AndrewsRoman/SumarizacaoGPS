CFLAGS = -Wall -std=c99 -D_DEFAULT_SOURCE

all: gps

gps: gps.o loadFiles.o funcoes.o
		gcc $(CFLAGS) gps.o loadFiles.o funcoes.o -o gps
		
gps.o: gps.c
		gcc -c $(CFLAGS) gps.c 

loadFiles.o: loadFiles.c loadFiles.h 
		gcc -c $(CFLAGS) loadFiles.c
		
funcoes.o: funcoes.c funcoes.h
		gcc -c $(CFLAGS) funcoes.c
		
run:
		./gps -d ./log

valgrind:
		valgrind ./gps -d ./log
clean:
		-rm -f *.o

purge: clean
		-rm -f gps 
