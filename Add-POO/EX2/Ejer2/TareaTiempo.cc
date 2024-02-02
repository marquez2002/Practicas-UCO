#include "TareaTiempo.h"

TareaTiempo::TareaTiempo(float tiempo, int ID, std::string nombre):Tarea(ID, nombre){
    if(tiempo<0){
        tiempo_=0;
    }
}

bool TareaTiempo::setTiempo(int tiempo){
    if(tiempo<0){
        return false;
    }
    tiempo_=tiempo;
    return true;
}