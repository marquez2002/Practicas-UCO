#include "cart2.h"

void Cart::print(){
    std::list<Computer>::iterator c;
    int i=0;
    for(i=0, c=clist.begin(); i<getN() && c!=clist.end(); i++, c++){
        std::cout<<i<<", "<<getID()<<", "<<getNombre()<<", "<<getModelo()<<", "<<getPrecio()<<"\n";
    }
}

void Cart::write(){
    std::fstream f;
    f.open("salida.txt");
    if(!f.is_open()){
        std::cout<<"ERROR al abrir el archivo";
    }
    std::list<Computer>::iterator c;
    int i=0;
    for(i=0, c=clist.begin(); i<getID() && c!=clist.end(); i++, c++){
        f<<i<<", "<<std::to_string(getID())<<", "<<c->getNombre()<<", "<<c->getModelo()<<", "<<std::to_string(c->getPrecio())<<"\n";
    }
}

bool Cart::eraseComputer(Computer c){
    for(std::list<Computer>::iterator i=clist.begin(); i!=clist.end(); i++){
        if(i->getNombre()==c.getNombre() && i->getModelo()==c.getModelo()){
            clist.erase(i);
            return true;
        }
    }
    return false;
}