#ifndef __libro__
#define __libro__
typedef struct{
    char titulo[256];
    char autor[256];
    float precio;
    int stock;
}libro;

int existeLibro(char const *nombre, char* titulo);
void introducirNuevoLibro(char const *nombre);
#endif