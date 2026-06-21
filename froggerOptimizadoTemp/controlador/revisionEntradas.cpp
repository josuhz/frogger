#include "rana.h"
#include "carro.h"
#include <thread>
#include <chrono>
#include "tableroNcurses.h"
#include <ncurses.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
int manejarEntradas(Rana& rana, TableroNcurses& tablero){
    int tecla = tablero.leerTecla();
        flushinp();

        if (tecla == 'q' || tecla == 'Q') {
            return 1;
        }
        else if (tecla == 'w' || tecla == 'W') {
            rana.moverArriba();
            return 2;
        }
        else if (tecla == 's' || tecla == 'S') {
            rana.moverAbajo();
            return 2;
        }
        else if (tecla == 'a' || tecla == 'A') {
            rana.moverIzquierda();
            return 2;
        }
        else if (tecla == 'd' || tecla == 'D') {
            rana.moverDerecha();
            return 2;
        }
        return 0;

}
