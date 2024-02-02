#include <iostream>
#include "computer.h"

Computer::Computer(std::string nombre, std::string modelo, int precio=1){
    if(nombre==""){
        nombre="Ninguno";
    }
    if(modelo==""){
        modelo="Ninguno";
    }
    setPrecio(precio);
    setModelo(modelo);
    setNombre(nombre);
}

bool Computer::setNombre(std::string nombre){
    if(nombre==""){
        return false;
    }
    nombre_=nombre;
    return true;
}

bool Computer::setModelo(std::string modelo){
    if(modelo==""){
        return false;
    }
    modelo_=modelo;
    return true;
}

bool Computer::setPrecio(int precio){
    if(precio<=0){
        return false;
    }
    precio_=precio;
    return true;
}
 