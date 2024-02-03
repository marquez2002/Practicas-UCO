#include <stdio.h>
#include <stdlib.h>
#include <math.h>


float norma(float x[], float valores_iniciales[], int dimension){
	float norma=0;
	for(int i=1; i<dimension;i++){
		norma=norma+((x[i])-(valores_iniciales[i]))*(x[i]-valores_iniciales[i]);
	}
	return norma;
}

float sumajacobi(float* auxiliar, float valores_iniciales[], int i, int dimension){
	float suma=0;
	for(int j=1; j<dimension; j++){
		if(i!=j){
			suma=suma+auxiliar[i]*valores_iniciales[i];
		}
	}
	return suma;
}

int main(){
	system("clear");
	int m, n;
	float criterioparada, error;
	printf("Para la empleacion del metodo de Jacobi tendremos que tener un sistema de tipo A·x=b\n");			
	int dimension, iteracion;
	/* Introducimos todas las variables*/
	printf("En primer lugar deberemos de conocer la dimension de la matriz a fin de crear la distintas matrices\n");
	scanf("%d", &dimension);
	dimension=dimension-1;
	/*Pedimos la dimension de la matriz a crear */
	printf("Creando la matriz A\n");
	float A[dimension][dimension];
	printf("Introduzca los valores de la matriz A\n");
	/* Introducimos los valores de la matriz A*/
	for(int i=0; i<dimension; i++){
		for(int j=0; j<dimension; j++){
			printf("\nA[%d][%d]=", i, j);
			scanf("%f", &A[i][j]);
		}
	}

	printf("Creando el vector x\n");
	float x[dimension];
	/* Creamos el vector x */

	printf("Creando el vector b\n");
	float b[dimension];
	printf("Introduzca los valores del vector b\n");
	/* Introducimos los valores pertencientes a b */
	for(int i=0; i<dimension; i++){
		printf("\nA[%d]=", i);
		scanf("%f", &b[i]);
	}

	printf("\n Error de parada: E=\n");
	/* Introducimos el criterio de parada*/
	scanf("%f", &criterioparada);
	error=criterioparada+1; /* Ponemos que el error sea mayor que criterio de parada para poder entrar en el while*/

	float valores_iniciales[dimension], auxiliar[dimension];
	printf("Los valores iniciales de la iteracion seran: \n");
	/* Introducimso el vector con los valores iniciales */
	for(int i=0; i<dimension;i++){
			printf("x0(%d)=", i);
			scanf("%f", &valores_iniciales[i]);
	}
	
	while(error>criterioparada){
		for(int i=0; i<dimension;i++){
			for(int j=0; j<dimension;j++){
				x[i]=(1/A[i][i])*(b[i]-sumajacobi(auxiliar, valores_iniciales, i, dimension));
				/* En caso de que se cumpla que el error sea mayor que el criterio de parada, realizamos la ecuacion del metodo de Jacobi, donde necesitaremos ir a la funcion sumajacobi para realizar la suma de las distintas matrices*/
			}
			printf("\n Iteracion %d: \n", iteracion);
			/* Contamos la iteraciones necesarias para ir realizando el proceso */
			for(int i=0; i<dimension;i++){
				valores_iniciales[i]=x[i];
				printf("X(%d)=%f \n",i, x[i]);
			}
			iteracion++;

		}
		error=norma(x, valores_iniciales, dimension);
		/* Actualizamos el valor del error */

		
		if(iteracion==20){
			error=criterioparada-1;
			/* Saldremos del codigo si se necesitan mas de 20 iteraciones*/
		}
	}

	printf("Solucion del sistema: \n");
	printf("El numero de iteraciones ha sido de %d\n", iteracion);
	/* Imprimiremos por pantalla la solucion correspondiente */
	for(int i=1; i<=dimension;i++){
		printf("X(%d)=%f \n",i, x[i]);
	}
	return 1;
}

