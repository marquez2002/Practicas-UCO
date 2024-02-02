#include "laptor.h"

Laptor::Laptor(int pulgadas, std::string modelo, int precio):Computer("Laptor", modelo, precio){
    if(setPulgadas(pulgadas)==true){
        pulgadas_=pulgadas;
    }
    pulgadas_=1;
}

bool Laptor::setPulgadas(int pulgadas){
    if(pulgadas<=0){
        return false;
    }
    pulgadas_=pulgadas;
    return true;
}