//============================================================================
// Name        : main.cpp
// Author      : Gonzalo Márquez de Torres
// Version     : 1.0
// Date        : 23/02/2021
//Busqueda por profundidad
//============================================================================

/////////////////////////////////////////////////////
//EDITA ÚNICAMENTE LAS LÍNEAS ASOCIADAS A TAREAS POR HACER (marcadas entre un bloque TODO)
/////////////////////////////////////////////////////


#include "State.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <stack> //Fíjate en que se está utilizando la clase stack para implementar frontera como una pila
#include <deque>
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
    
	stack <State*> frontier; //Crea la pila frontera
    vector <State*> *Successors; //Crea el vector de sucesores
    bool objective=false; //Crea el boleano objetivo y lo pone falso
    frontier.push(initialState);
    
    while (((frontier.empty())!=1)&&objective==false){ //Comprueba que frontera no esta vacio y que objetivo es falso
    	objective=frontier.top()->isObjective();//Comprueba que la pila es objetivo y dedice en que if lo introduce
	     if(objective==true){//Si es objetivo...
	     	cout<<"Este estado es solución:\n";
	     	frontier.top()->print();//Imprime la solucion
	     }

	     else{//Si no es objetivo...
	     	cout<<"Este estado no es solución.\n"; 
	     	Successors=frontier.top()->getSuccessors(); //Se elimina la cima del vector
	     	frontier.pop(); //
	     	for(int i=0;i<Successors->size();i++){
	     		frontier.push(Successors->at(i));
	     	}
	     }
    }
    delete Successors; //se elimina el vector de sucesores
    
    //////////////////////////////////////////
    // Fin bloque TODO
    //////////////////////////////////////////
    
    if (frontier.empty())
		cout << "There is no solution for " << numQueens << " queens" << endl;
    
	return 0;
}
