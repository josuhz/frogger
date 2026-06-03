#include "tableroNcurses.h"
#include "rana.h"
#include "carro.h"
#include <thread>
#include <chrono>
#include <ncurses.h>
#include <iostream>
#include "revisionEntradas.h"
#include "movCarros.h"
#include "cicloPrincipal.h"
#include "estadoPartida.h"
#include <string>


int main() {
    TableroNcurses tablero;
    EstadoPartida estado;
    estado.vidas = 5;
    estado.puntos = 0;
    estado.nivel = 1;
    estado.tiempo = 60;

    nivel1(estado, tablero);
    if(estado.vidas > 0) {
        nivel2(estado, tablero);
    }
    

    // Cuando main termina, se destruye el objeto tablero.
    // Eso llama automaticamente al destructor y cierra ncurses.
    return 0;
}
