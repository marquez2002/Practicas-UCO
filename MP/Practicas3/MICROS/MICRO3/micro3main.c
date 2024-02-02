#include "micro3.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const* argv[]){
    if(argc<4){
        printf("ERROR en el formato de ejecutar\n");
        return -1;
    }
    rellenaDocs(argv[1], argv[2], argv[3]);
}