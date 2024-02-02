#Fichero: makefil6.mak
#Se muestra el uso de .PHONY

saludos: saludo.exe saludo2.exe clean

saludo.exe: saludo.c
	@echo Creando saludo.exe
	gcc -o saludo.exe saludo.c 

saludo2.exe: saludo2.c
	@echo Creando saludo2.exe
	gcc -o saludo2.exe saludo.c 

.PHONY : clean
clean:
	@echo Borrando ficheros.o ...
	@rm -f *.o
