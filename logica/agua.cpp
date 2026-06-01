#include "agua.h"

Agua::Agua(int min, int max){
    xmin = min;
    xmax = max;
}

int Agua::obtenerXmin(){
    return xmin;
}
int Agua::obtenerXmax(){
    return xmax;
}