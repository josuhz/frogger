#include "carro.h"
#include "tableroNcurses.h"

void moverCarro(Carro& carro, TableroNcurses& tabla){
    carro.moverIzquierda(carro.obtenerVelocidad());

            if(carro.obtenerColumna() <= -1){
                carro.teleportar(TableroNcurses::ANCHO_TABLERO -3);
            }
            tabla.dibujarCarro(carro.obtenerFila(),carro.obtenerColumna());
}