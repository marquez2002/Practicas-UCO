#Fichero: makefile
#Construye micro2 a partir de micro2main.c

destino: saludo micro2

saludo:
	@echo "Hecho por Gonzalo"

micro2: micro2main.o micro2.o
	gcc -o micro2 micro2main.o micro2.o

micro2main.o: micro2main.c micro2.h
	gcc -c micro2main.c

micro2.o: micro2.c micro2.h
	gcc -c micro2.c
