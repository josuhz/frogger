#include "tableroNcurses.h"
#include "rana.h"
#include "carro.h"
#include <thread>
#include <chrono>
#include <ncurses.h>
#include <iostream>
#include "revisionEntradas.h"
#include "movCarros.h"


int main() {
    // Crea el objeto tablero.
    // Al crearlo, se ejecuta el constructor y se inicia ncurses.
    TableroNcurses tablero;

    // Crea la rana en la parte inferior central del tablero.
    // Se resta 2 en la fila para que quede dentro del borde inferior.
    Rana rana(TableroNcurses::ALTO_TABLERO - 2,
              TableroNcurses::ANCHO_TABLERO / 2,
              TableroNcurses::ALTO_TABLERO,
              TableroNcurses::ANCHO_TABLERO);

    

    Carro carros[2] = {
        Carro(TableroNcurses::ALTO_TABLERO /2,
                TableroNcurses::ANCHO_TABLERO -5,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                2),

        Carro(TableroNcurses::ALTO_TABLERO /2 +4,
                TableroNcurses::ANCHO_TABLERO -5,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                3)
    };
    bool perdio = false;
    bool jugando = true;
    while (jugando) {
        // Dibuja el tablero y la rana en su posicion actual.
        tablero.dibujar();

        if(manejarEntradas(rana, tablero) == 1){
            jugando = false;
        }

        for(int i = 0; i<2;i++){
            moverCarro(carros[i],tablero);
            if(rana.obtenerFila() == carros[i].obtenerFila() && rana.obtenerColumna() <= carros[i].obtenerColumna() +4 &&
            rana.obtenerColumna() >= carros[i].obtenerColumna() -1 ){
                perdio = true;
            }
        }
        

            std::this_thread::sleep_for(
        std::chrono::milliseconds(80)
        );

        if(perdio){
            bool seguir = true;
            while(seguir){
                tablero.perder();
                int tecla = tablero.leerTecla();
                flushinp();
                if(tecla == 'r' || tecla == 'R'){
                    seguir = false;
                    perdio = false;
                    rana.teleportar(TableroNcurses::ALTO_TABLERO - 2,
                        TableroNcurses::ANCHO_TABLERO / 2);
                }
                if(tecla == 'q' || tecla == 'Q'){
                    seguir = false;
                    perdio = false;
                    jugando = false;
                }
            }
        }

    }
    // Cuando main termina, se destruye el objeto tablero.
    // Eso llama automaticamente al destructor y cierra ncurses.
    return 0;
}
