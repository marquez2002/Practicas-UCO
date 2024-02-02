#include <stdio.h>
#include "ejer7.h"

int main(){
    int n;
    printf("Introduce el valor de n: ");
    scanf("%d", &n);
    int a[n];

    printf("Introduce los valores del vector: \n");
    for(int i=0; i<n;i++){
        printf("a[%d]=", i);
        scanf("%d", &a[i]);
    }
    int media, varianza, desviacion_tip;
    estadisticasVector(a, n, &media, &varianza, &desviacion_tip);
    printf("La media sera %d, la varianza %d y la desviacion tipica %d\n", media, varianza, desviacion_tip);   
}