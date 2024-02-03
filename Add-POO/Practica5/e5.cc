#include <iostream>
#include <fstream>
#include <vector>
#include "jugador.h"
#include <algorithm>

std::vector<Jugador> leeJugadores(){
  std::ifstream f("jugadores.txt"); 
  if (!f){//Comprobamos que el fichero se haya abierto correctamente
    std::cout<<"Error al abrir el archivo\n"; //Como no se ha abierto correctamente informamos al usuario de que ha habido un error
    EXIT_FAILURE;
  }
  std::vector<Jugador> jugadores;//Creamos el vector de jugadores
  jugadores.clear(); //Vaciamos la lista
  Jugador jugador("a","a");//Creamos un jugador auxiliar
  std::string cadena;//Creamos una cadena para almacenar las lecturas de getline
  getline(f, cadena,',');
  while (!f.eof()){
    jugador.setDNI(cadena);
    getline(f, cadena,',');
    jugador.setCodigo(cadena);
    getline(f, cadena,',');
    jugador.setNombre(cadena);
    getline(f, cadena,',');
    jugador.setApellidos(cadena);
    getline(f, cadena,',');
    jugador.setDireccion(cadena);
    getline(f, cadena,',');
    jugador.setLocalidad(cadena);
    getline(f, cadena,',');
    jugador.setProvincia(cadena);
    getline(f, cadena,',');
    jugador.setPais(cadena);
    getline(f, cadena,'\n');
    jugador.setDinero(std::stoi(cadena));
    jugadores.push_back(jugador);
    getline(f, cadena,',');
  }
  f.close(); //Como ya no hay nada mas que leer cerramos el fichero
  return jugadores;
}

bool ascendente(Jugador j1, Jugador j2){
    return j1.getDNI()<j2.getDNI();
}

int main(int argc, char const *argv[]){
   std::vector<Jugador> jugadores;
   jugadores = leeJugadores();
   std::cout<<"DNI del vector de jugadores : ";
   for (int i = 0; i < (int) jugadores.size(); i++){
     std::cout<<jugadores[i].getDNI()<<" ";
   }
   std::cout<<"\n";
   std::sort(jugadores.begin(), jugadores.end(), ascendente);
   std::cout<<"DNIS del vector de jugadores ordenados : ";
   for (int i = 0; i < (int) jugadores.size(); i++){
     std::cout<<jugadores[i].getDNI()<<" ";
   }
   std::cout<<"\n";
   return 0;
}