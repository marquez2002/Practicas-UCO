//============================================================================
// Name        : maincolas.cpp
// Author      : Gonzalo Márquez de Torres
// Version     : 1.0
// Date        : 23/02/2021
//en anchura
//============================================================================

/////////////////////////////////////////////////////
//EDITA ÚNICAMENTE LAS LÍNEAS ASOCIADAS A TAREAS POR HACER (marcadas entre un bloque TODO)
/////////////////////////////////////////////////////


#include "State.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <stack> //Fíjate en que se está utilizando la clase stack para implementar frontera como una pila
#include <queue>
using namespace std;

class QueensState: private State {

public:
	/**
	 * This function allows the user to set the number of queens of the problem.
	 * It should be passed as a pointer to an int variable with the desired value.
	 */
	static void setParameters(void *parameters);

	/**
	 * This function returns the initial state for the queens problem. An empty board
	 */
	static State* getInitialState();

	/**
	 * Destructor
	 */
	virtual ~QueensState();
};

int main() {

	int numQueens;
	cout << "¿Con cuántas reinas deseas que se resuelva el problema?" << endl;
	cin >> numQueens;

	QueensState::setParameters(&numQueens);

	State *initialState = QueensState::getInitialState();

    /////////////////////////////////////////
	// TODO programar aquí la búsqueda que se desee aplicar
    /////////////////////////////////////////
    queue <State*> frontier; //se crea la frontera con una cola
    vector <State*> *Successors; //se crea el vector de sucesores
    bool objective=false; //creo boleano para determinar cuando alcanzo el objetivo
    frontier.push(initialState); // 
    while (((frontier.empty())!=1)&&objective==false){//mientras objetivo sea falso o mientras la pila se encuentre llena
    	objective=frontier.front()->isObjective();//indica si el elemento es objetivo y en funcion de este entra en el if
	     if(objective==true){//Si se encuentra la solucion
	     	cout<<"Este estado es solución:\n";
	     	frontier.front()->print();//Se imprime por pantalla
	     }
	     else{
	     	cout<<"Este estado no es solución.\n";//Si no se encuentra la solucion
	     	Successors=frontier.front()->getSuccessors();//Retorna el primer elemento del vector
	     	frontier.pop(); //Este se elimina
	     	for(int i=0;i<Successors->size();i++){
	     		frontier.push(Successors->at(i));//Se inserta un nuevo elemento en la pila
	     	}
	     }
    }
    delete Successors;//borro el vector de sucesores
    //////////////////////////////////////////
    // Fin bloque TODO
    //////////////////////////////////////////
    
    if (frontier.empty())
		cout << "There is no solution for " << numQueens << " queens" << endl;
    
	return 0;
}