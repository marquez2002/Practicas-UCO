#include "contador.h"

Contador::Contador(int valor=0, int maximo=100){
    if(maximo<valor){
        maximo_=100;
        valor_=0;
    }
}

bool Contador::setV(int valor){
    if(valor>maximo_){
        return false;
    }
    valor_=valor;
    return true;
}

bool Contador::setM(int maximo){
    if(valor_>maximo){
        return false;
    }
    maximo_=maximo;
    return true;
}

Contador Contador::operator=(int valor){
    if(maximo_>valor){
        setV(valor);
    }
    else{
        setM(valor);
    }
    return *this;
}

Contador Contador::operator=(Contador a){
    (*this).setM(a.getV());
    (*this).setV(a.getV());
    return *this;
}

Contador Contador::operator++(void){
    valor_++;
    return *this;
}

Contador Contador::operator++(int){
    Contador aux=*this;
    valor_++;
    return aux;
}

Contador Contador::operator+(int a){
    if(maximo_<(a+valor_)){
        valor_=maximo_;
    }
    else{
        valor_=valor_+a;
        return *this;
    }
}

Contador operator+(int aux, Contador a){
    if(a.getM()<(aux+a.getV())){
        a.setV(a.getM());
    }
    else{
        a.setV(aux+a.getV());
    }
    return a;
}