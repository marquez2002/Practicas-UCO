#include <iostream>
#include "computer2.h"

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

std::ofstream &operator<<(std::ofstream &stream, Computer &c){
    std::cout<<"Nombre: " + c.getNombre()<<std::endl;
    std::cout<<"Modelo: " + c.getModelo()<<std::endl;
    return stream;
}
        
std::ifstream &operator>>(std::ifstream &stream, Computer &c){
    std::string nombre, modelo;
    std::cout<<"Nombre: ";
    std::cin>>nombre;
    c.setNombre(nombre);
    std::cout<<"Modelo: ";
    std::cin>>modelo;
    c.setModelo(modelo);
    return stream;
}
 