#include "tarea.h"

Tarea::Tarea(int ID, std::string nombre){
    if(ID>0){
        ID_=ID;
    }
    nombre_=nombre;
}

bool Tarea::setNombre(std::string nombre){
    if(nombre==""){
        return false;
    }
    nombre_=nombre;
    return true;
}

bool Tarea::setID(int ID){
    if(ID<=0){
        return false;
    }
    ID_=ID;
    return true;
}