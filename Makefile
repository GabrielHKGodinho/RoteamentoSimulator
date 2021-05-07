all:exec

exec: grafo.o
	gcc -o exec grafo.o

grafo.o: grafo.c grafo.h
	gcc -o grafo.o grafo.c -c -Wall -pedantic
	
clean:
	rm -rf *.o *~ exec
