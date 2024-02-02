#makefil7b.mak
#makefile ejemplo 7

destino: saludo main clean

saludo:
	@echo "Hecho por Gonzalo Marquez"

main: main.o vector.o orden.o
	gcc -o main main.o vector.o orden.o

main.o: main.c
	gcc -c main.c 

vector.o: vector.c vector.h
	gcc -c vector.c

orden.o: orden.c orden.h
	gcc -c orden.c

clean:
	rm *.o