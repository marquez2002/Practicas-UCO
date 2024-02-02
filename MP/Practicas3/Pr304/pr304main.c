#include "pr304.h"
#include <stdio.h>
#include <stdlib.h>
#include "libro.h"

int main(int argc, char const *argv[]){
    if(argc<2){
        printf("ERROR, falta el nombre del archivo\n");
        return -1;
    }

    int select;
    while(select!=0){
        printf("Introduzca el numero que corresponde con la operación que desea realizar\n");
        printf("Pulse 1 para comprobar la existencia de un libro en stock\n");
        printf("Pulse 2 para introducir un nuevo libro en stock\n");
        printf("Pulse 3 para contar el numero de libros diferentes en stock\n");
        printf("Pulse 4 para listar los libros en el stock almacenandolos en un vector dinamico\n");
        printf("Pulse 5 para vender n unidades de un libro buscandolo por titulo\n");
        printf("Pulse 6 para borrar aquellos libros con 0 stock\n");
        printf("Pulse 0 para salir\n");
        scanf("%d", &select);

        switch(select){
            case 1:
                printf("Introduce el titulo: ");
                char titulo[256];
                fgets(titulo, 256, stdin);
                int estado=existeLibro(argv[1], titulo);
                switch(estado){
                    case 0:
                        printf("El archivo no existe\n");
                    break;
                    case 1:
                        printf("El libro no esta en stock\n");
                    break;
                    case 2:
                        printf("El libro está en stock\n");
                    break;
                }
            break;

            case 2:
                introducirNuevoLibro(argv[1]);
            break;


        }
    }

}