/**
 * @file ruleta.cc
 * @author Gonzalo Márquez (i02matog@uco.es)
 * @brief definition of the methods of the class Ruleta
*/

#include <iostream>
#include <fstream>
#include <vector>
#include "ruleta.h"


bool Ruleta::setBanca(int const &banca){
	if(banca>0){ //Comprueba si el numero valor de la banca es mayor que 0
		banca_=banca;
		return true;
	}
	return false;
}

bool Ruleta::setBola(int const &bola){
	if(bola>-1 && bola<37){//Comprueba que el valor de la bola se encuentra entre 0 y 36
		bola_=bola;
		return true;
	}
	else{
		return false;
	}
}

bool Ruleta::addJugador(Jugador &jugador){
	std::list<Jugador>:: iterator j;
	j=jugadores_.begin();
	for(int i=0; i< (int) jugadores_.size(); i++){
		if(jugador.getDNI()==(*j).getDNI()){
			return false;
		}
		j++;
	}
	jugadores_.push_back(jugador);
	std::fstream f((jugador.getDNI()+".txt"), std::fstream::app);
	if(!f){
		std::cout<<"ERROR al abrir el archivo\n";
		return false;
	}
	return true;
}

int Ruleta::deleteJugador(std::string const &dni){
	if(jugadores_.empty()){
		return -1;
	}

	std::list<Jugador>:: iterator j;
	j=jugadores_.begin();
	for(int i=0; i< (int) jugadores_.size(); i++){
		if(dni==(*j).getDNI()){
			j=jugadores_.erase(j);
			return 1;
		}
		j++;
	}
	return -2;
}

int Ruleta::deleteJugador(Jugador &jugador){
	if(jugadores_.empty()){
		return -1;
	}

	std::list<Jugador>:: iterator j;
	j=jugadores_.begin();
	for(int i=0; i< (int) jugadores_.size(); i++){
		if(jugador.getDNI()==(*j).getDNI()){
			j=jugadores_.erase(j);
			return 1;
		}
		j++;
	}
	return -2;
}

void Ruleta::escribeJugadores(){
	std::ofstream f("jugadores.txt");
	if(!f){
		std::cout<<"ERROR al abrir el archivo\n";
		EXIT_FAILURE;
	}
	std::list<Jugador>::iterator j;
	j=jugadores_.begin();
	for(int i=0; i<(int)jugadores_.size(); i++){
		f<<(*j).getDNI()<<','<<(*j).getCodigo()<<','<<(*j).getNombre()<<','<<(*j).getApellidos()<<',' <<(*j).getDireccion()<<','<<(*j).getLocalidad()<<','<<(*j).getProvincia()<<','<<(*j).getPais()<<','<<(*j).getDinero()<<'\n';
		j++;
	}
	f.close();
}

void Ruleta::leeJugadores(){
	std::ifstream f("jugadores.txt");
	if(!f){
		std::cout<<"ERROR al abrir el archivo\n";
		EXIT_FAILURE;
	}
	jugadores_.clear();
	Jugador jugador("a", "a");
	std::string cadena;
	getline(f, cadena, ',');
	while(!f.eof()){
		jugador.setDNI(cadena);
		getline(f, cadena, ',');
		jugador.setCodigo(cadena);
		getline(f, cadena, ',');
		jugador.setNombre(cadena);
		getline(f, cadena, ',');
		jugador.setApellidos(cadena);
		getline(f, cadena, ',');
		jugador.setDireccion(cadena);
		getline(f, cadena, ',');
		jugador.setLocalidad(cadena);
		getline(f, cadena, ',');
		jugador.setProvincia(cadena);
		getline(f, cadena, ',');
		jugador.setPais(cadena);
		getline(f, cadena, '\n');
		jugador.setDinero(std::stoi(cadena));
		jugadores_.push_back(jugador);
		getline(f, cadena, ',');
	}
	f.close();
}

void Ruleta::getPremios()
{
  std::list<Apuesta> apuestas;
  std::list<Apuesta>::iterator a;
  std::list<Jugador>::iterator j;
  j =jugadores_.begin();
  for (int i = 0; i < (int) jugadores_.size(); i++){
    (*j).setApuestas();//Se cargan las apuestas de los jugadores mediante el bucle
    j++;
  }

  j =jugadores_.begin();
  for (int i = 0; i < (int) jugadores_.size(); i++){
    apuestas = (*j).getApuestas();
	a = apuestas.begin();
    for (int m = 0; m < (int) apuestas.size(); m++){
      switch ((*a).tipo){
      case 1:
        if (std::stoi((*a).valor)==bola_){//Determina si se acierta la bola con la apuesta
          (*j).setDinero(((*j).getDinero()+((*a).cantidad*35)));//Actualizacion del dinero
          setBanca((getBanca()-((*a).cantidad*35)));//Actualizacion del dinero
          break;
        }
        (*j).setDinero(((*j).getDinero()-(*a).cantidad));//Actualizacion del dinero
        setBanca((getBanca()+(*a).cantidad));//Actualizacion del dinero
        break;
      
      case 2:
        if (aciertaColor((*a).valor)){//Determina si se acierta el color
          (*j).setDinero(((*j).getDinero()+(*a).cantidad));//Actualizacion del dinero
          setBanca((getBanca()-(*a).cantidad));//Actualizacion del dinero
          break;
        }
        (*j).setDinero(((*j).getDinero()-(*a).cantidad));//Actualizacion del dinero
        setBanca((getBanca()+(*a).cantidad));//Actualizacion del dinero
        break;
      
      case 3:
        if (aciertaParidad((*a).valor)){//Determina si se acierta la paridad
          (*j).setDinero(((*j).getDinero()+(*a).cantidad));//Actualizacion del dinero
          setBanca((getBanca()-(*a).cantidad));//Actualizacion del dinero
          break;
        }
        (*j).setDinero(((*j).getDinero()-(*a).cantidad));//Actualizacion del dinero
        setBanca((getBanca()+(*a).cantidad));//Actualizacion del dinero
        break;

      case 4:
        if (aciertaZona((*a).valor)){//Determina si se acierta la zona
          (*j).setDinero(((*j).getDinero()+(*a).cantidad));//Actualizacion del dinero
          setBanca((getBanca()-(*a).cantidad));//Actualizacion del dinero
          break;
        }
        (*j).setDinero(((*j).getDinero()-(*a).cantidad));//Actualizacion del dinero
        setBanca((getBanca()+(*a).cantidad));//Actualizacion del dinero
        break;
      }
      a++;
    }
    j++;
  }
}

bool Ruleta::aciertaColor(std::string const &color){
	std::vector<int> rojo={1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36};
	std::vector<int> negro={2,4,6,8,10,11,13,15,17,20,22,24,26,28,29,31,33,35};
	if(bola_==0){
		return false;
	}
	else if(color=="rojo"){
		for(int i=0; i<(int)rojo.size(); i++){
			if(bola_==rojo[i]){
				return true;
			}
		}
	}
	else if(color=="negro"){
		for(int i=0; i<(int)negro.size(); i++){
			if(bola_==negro[i]){
				return true;
			}
		}
	}
	return false;
}

bool Ruleta::aciertaParidad(std::string const &paridad){
	std::vector<int> par={2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36};
	std::vector<int> impar={1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35};
	if(bola_==0){
		return false;
	}
	else if(paridad=="par"){
		for(int i=0; i<(int)par.size(); i++){
			if(bola_==par[i]){
				return true;
			}
		}
	}
	else if(paridad=="impar"){
		for(int i=0; i<(int)impar.size(); i++){
			if(bola_==impar[i]){
				return true;
			}
		}
	}
	return false;
}

bool Ruleta::aciertaZona(std::string const &zona){
	std::vector<int> bajo={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18};
	std::vector<int> alto={19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36};
	if(bola_==0){
		return false;
	}
	else if(zona=="bajo"){
		for(int i=0; i<(int)bajo.size(); i++){
			if(bola_==bajo[i]){
				return true;
			}
		}
	}
	else if(zona=="alto"){
		for(int i=0; i<(int)alto.size(); i++){
			if(bola_==alto[i]){
				return true;
			}
		}
	}
	return false;
}
