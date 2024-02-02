#include "ejer4.h"

int main(){
    int nfil, ncol;
    printf("Introducir nfil: ");
    scanf("%d", &nfil);
    printf("Introducir ncol: ");
    scanf("%d", &ncol);
    int** matriz;
    matriz=reservaMemoria(nfil, ncol);
    rellenar(matriz, nfil, ncol);
    imprimir(matriz, nfil, ncol);
    printf("\n");
    int* vector=minCol(matriz, nfil, ncol);
    for(int i=0; i<ncol;i++){    
        printf("%d  ", vector[i]);
    }
    liberar(matriz, nfil, ncol);
}