#ifndef TAREATIEMPO_H
#define TAREATIEMPO_H
#include "tarea.h"

class TareaTiempo:public Tarea{
    private:
        float tiempo_;
    public:
        TareaTiempo(float tiempo, int ID, std::string nombre);
        inline int getTiempo(){return tiempo_;};
        bool setTiempo(int tiempo);
};
#endif