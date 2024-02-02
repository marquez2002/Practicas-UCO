#include "ejer2.h"


int main(){
    int *vector, *vectormay, *vectormen;
    int longitud, num, nmay=0, nmen=0;
    printf("Introduce la longitud del vector: ");
    scanf("%d", &longitud);
    printf("Introduce un numero para diferenciar los vectores: ");
    scanf("%d", &num);
    vector=(int*)malloc(longitud*sizeof(int));
    rellenaAleatorio(vector, longitud);
    
    contarmayoresmenores(vector, longitud, num, &nmay, &nmen);
    vectormay=(int*)malloc(nmay*sizeof(int));
    vectormen=(int*)malloc(nmen*sizeof(int));
    vectores(vector, vectormay, vectormen, longitud, num, nmay, nmen);
    printf("\nVector principal: \n");
    imprimir(vector, longitud);
    printf("\nVector mayores que %d: \n", num);
    imprimir(vectormay, nmay);
    printf("Vector menores que %d: \n", num);
    imprimir(vectormen, nmen);


}