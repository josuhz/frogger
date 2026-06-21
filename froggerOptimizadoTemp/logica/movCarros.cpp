#include "carro.h"
#include "tableroNcurses.h"

void moverCarro(Carro& carro, TableroNcurses& tabla){
    if(carro.obtenerDireccion()){
        carro.moverIzquierda(carro.obtenerVelocidad());
        if(carro.obtenerColumna() <= -1){
                carro.teleportar(TableroNcurses::ANCHO_TABLERO -3);
            }
        tabla.dibujarCarro(carro.obtenerFila(),carro.obtenerColumna());
    }
    else{
        carro.moverDerecha(carro.obtenerVelocidad());
        if(carro.obtenerColumna() >= TableroNcurses::ANCHO_TABLERO -3){
                carro.teleportar(-1);
            }
        tabla.dibujarCarro(carro.obtenerFila(),carro.obtenerColumna());
    }

    
}