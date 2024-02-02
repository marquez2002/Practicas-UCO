#include "ejer3.h"

jugador* reservarMemoria(int n){
    jugador* equipo;
    equipo=(jugador*)malloc(n*sizeof(jugador));
    return equipo;
}

jugador listar(){
    jugador nuevo;
    printf("Introduce el nombre: ");
    scanf("%50s", nuevo.nombre);
    printf("Introduce el dorsal: ");
    scanf("%d", &nuevo.dorsal);
    printf("Introduce el peso: ");
    scanf("%f", &nuevo.peso);
    printf("Introduce el estatura: ");
    scanf("%f", &nuevo.estatura);
    return nuevo;
}

void crearEquipo(jugador equipo[], int n){
    for(int i=0; i<n; i++){
        equipo[i]=listar();
        printf("\n");
    }
}

void imprimir(jugador equipo[], int n){
    for(int i=0; i<n; i++){
        printf("Nombre: %s\n", equipo[i].nombre);
        printf("Dorsal: %d\n", equipo[i].dorsal);
        printf("Peso: %f\n", equipo[i].peso);
        printf("Estatura: %f\n", equipo[i].estatura);
        printf("\n");
    }
}

int borrarJugadores(jugador equipo[], int* n, char letra){
    int aux=*n;
    for(int i=0; i<aux; i++){
        for(int j=0; equipo[i].nombre[j]!='\0'; j++){
            if(toupper(letra)==toupper(equipo[i].nombre[j])){
                for(int k=i; k<aux; k++){
                    equipo[k]=equipo[k+1];
                }
                aux--;
                i--;
                if(aux==0){
                    free(equipo);
                    return aux;
                }
                equipo=(jugador*)realloc(equipo, aux*sizeof(jugador));
            }
        }
    }
    return aux;
}