//guess.cc
//the user has to guess a number from 1 to 10
#include <iostream>
#include <cstdlib>
#include <ctime>

int main(){
	srand(time(NULL));
	int number=rand()%10;
	int number2;
	while(number!=number2){//Mientras los numeros no sean iguales
		std::cout<<"Introduce un numero entre 1-10\n";
		std::cin>>number2;
		std::cout<<"\n";
		if(number2>number){//El numero es menor al introducido
			std::cout<<"El numero es menor al introducido\n";
		}
		if(number2<number){//El numero es mayor al introducido
			std::cout<<"El numero es mayor al introducido\n";
		}
	}
	std::cout<<"CORRECTO, el numero es "<<number<<"\n";


}