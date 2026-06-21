#ifndef AGUA_H
#define AGUA_H

//Agua: Clase que representa el agua donde se ahoga la rana, guarda su fila inicial y final
class Agua {
private:
    int xmin;
    int xmax;

public:
    Agua(int xmin, int xmax);
    int obtenerXmin();
    int obtenerXmax();
};

#endif
