/**
 * @file juego.cc
 * @author Gonzalo Márquez (i02matog@uco.es)
 * @brief body of program to prove the class Dados
*/

#include <iostream>
#include "dados.h"
#include "dados.cc"

int main(){
	Dados d;
	int operacion=1, v;

	while (operacion!=0){

		std::cout<<"\n|--------------------------------------------------------|\n";
		std::cout<<"|------------Menu de Seleccion:--------------------------|\n";
		std::cout<<"|--------------------------------------------------------|\n";
		std::cout<<"|Pulsa 0 para salir                                      |\n";
		std::cout<<"|Pulsa 1 para realizar lanzamiento                       |\n";
		std::cout<<"|Pulsa 2 para obtener el valor del dado 1                |\n";
		std::cout<<"|Pulsa 3 para obtener el valor del dado 2                |\n";
		std::cout<<"|Pulsa 4 para asignar el valor del dado 1                |\n";
		std::cout<<"|Pulsa 5 para asignar el valor del dado 2                |\n";
		std::cout<<"|Pulsa 6 para sumar el dado 1 con el dado 2              |\n";
		std::cout<<"|--------------------------------------------------------|\n";
		std::cout<<"\nSu eleccion: ";
		std::cin>>operacion;

		switch(operacion){
			
			case 0:
				std::cout<<"Hasta pronto\n";
			break;

			case 1: 
				d.lanzamiento();
			break;

			case 2:
				std::cout<<"El valor del dado 1 es: "<<d.getDado1()<<"\n";
			break;

			case 3:
				std::cout<<"El valor del dado 2 es: "<<d.getDado2()<<"\n";
			break;

			case 4:
				std::cout<<"El nuevo valor del dado 1 es: ";
				std::cin>>v;
				if(d.setDado1(v)){
					std::cout<<"Se cambio de forma correcta\n";
				}
				else{
					std::cout<<"Se produjo un error\n";
				}
			break;

			case 5:
				std::cout<<"El nuevo valor del dado 2 es: ";
				std::cin>>v;
				if(d.setDado2(v)){
					std::cout<<"Se cambio de forma correcta\n";
				}
				else{
					std::cout<<"Se produjo un error\n";
				}
			break;

			case 6:
				std::cout<<"La suma de los dados es de "<<d.getSuma()<<"\n";
			break;

			default:
				std::cout<<"ERROR al escoger operacion\n";
			break;
		}
	}
	return 0;
}