#include "rana.h"
#include "carro.h"
#include <thread>
#include <chrono>
#include "tableroNcurses.h"
#include <ncurses.h>

int manejarEntradas(Rana& rana, TableroNcurses& tablero){
    int tecla = tablero.leerTecla();
        flushinp();

        if (tecla == 'q' || tecla == 'Q') {
            return 1;
        }
        else if (tecla == 'w' || tecla == 'W') {
            rana.moverArriba();
        }
        else if (tecla == 's' || tecla == 'S') {
            rana.moverAbajo();
        }
        else if (tecla == 'a' || tecla == 'A') {
            rana.moverIzquierda();
        }
        else if (tecla == 'd' || tecla == 'D') {
            rana.moverDerecha();
        }
        return 0;

}
