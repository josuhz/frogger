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
#include <string>


int main() {
    TableroNcurses tablero;
    int vidas = 5;

    while(vidas > 0){
    vidas = nivel1(vidas, tablero);
    vidas = nivel2(vidas, tablero);
    }
    // Cuando main termina, se destruye el objeto tablero.
    // Eso llama automaticamente al destructor y cierra ncurses.
    return 0;
}
