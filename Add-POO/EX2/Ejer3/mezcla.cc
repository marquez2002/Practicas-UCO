#include "mezcla.h"
#include <fstream>

bool Mezcla::addIngrediente(std::string ingrediente){
    std::list<string>::iterator c;
    int i;
    for(i=lista.begin(); c!=lista.end(); i++, c++){
        if(*c==ingrediente){
            return false;
        }
    }
    lista.push_back(ingrediente);    
    return true;
}

void Mezcla::print(){
    std::list<string>::iterator c;
    int i;
    for(i=lista.begin(); i<=getN() && c!=lista.end(); i++, c++){
        cout<<i<<","<<(*c)<<"\n";
    }
}    

void Mezcla::write(){
    std::ofstream f("salida.txt");
    if(!fopen(f)){
        std::cout<<"ERROR al abrir el archivo\n"
    }
    else{
        std::list<std::string>::iterator c;
        int i;
        for(i=lista.begin(); i<=getN() && c!=lista.end(); i++, c++){
            f<<i<<","<<(*c)<<std::endl;
        }
        f.close();
    }
}
