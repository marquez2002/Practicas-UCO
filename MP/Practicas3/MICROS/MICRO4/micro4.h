#ifndef __micro4__
#define __micro4__
struct proceso{
    char nombre[15];
    int duracion;
    int prioridad;
};
void rellenar(char const *archivo1, char const *archivo2, char const *archivo3, int prioridad);

#endif