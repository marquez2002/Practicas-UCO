#makefile.mak

destino: saludo micro3 clean
saludo:
	@echo "Ejecutando make"
micro3: micro3main.o micro3.o
	gcc -o micro3 micro3main.o micro3.o
micro3main.o: micro3main.c micro3.h
	gcc -c micro3main.c
micro3.o: micro3.c micro3.h
	gcc -c micro3.c
clean:
	rm *.o