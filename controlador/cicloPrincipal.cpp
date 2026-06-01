#include "tableroNcurses.h"
#include "rana.h"
#include "carro.h"
#include <thread>
#include <chrono>
#include <ncurses.h>
#include <iostream>
#include "revisionEntradas.h"
#include "movCarros.h"
#include "agua.h"
#include <string>

int ciclo(TableroNcurses& tablero, Rana& rana, Carro carros[], int cantidad, int vidas, Agua aguas[], int cantAgua){
    int lives = vidas;
    bool perdio = false;
    bool jugando = true;
    while (jugando) {
        // Dibuja el tablero y la rana en su posicion actual.
        tablero.dibujar();

        for(int i = 0;i<lives;i++){
            tablero.dibujarVida(TableroNcurses::ALTO_TABLERO,i);
        }

        if(manejarEntradas(rana, tablero) == 1){
            jugando = false;
        }

        for(int i = 0; i<cantidad;i++){
            moverCarro(carros[i],tablero);
            if(rana.obtenerFila() == carros[i].obtenerFila() && rana.obtenerColumna() <= carros[i].obtenerColumna() +4 &&
            rana.obtenerColumna() >= carros[i].obtenerColumna() -1 ){
                perdio = true;
            }
        }
        for(int i = 0; i<cantAgua;i++){
            tablero.dibujarAgua(aguas[i].obtenerXmin(),aguas[i].obtenerXmax());
            if(rana.obtenerFila() >= aguas[i].obtenerXmin() && rana.obtenerFila() <= aguas[i].obtenerXmax()){
                perdio = true;
            }
        }

        refresh();
        

            std::this_thread::sleep_for(
        std::chrono::milliseconds(80)
        );

        if(rana.obtenerFila() == 1){
            clear();
            refresh();
            return lives;}

        if(perdio){
            bool seguir = true;
            while(seguir){
                if(lives > 0){
                    tablero.perder();
                    int tecla = tablero.leerTecla();
                    flushinp();
                    if(tecla == 'r' || tecla == 'R'){
                        seguir = false;
                        perdio = false;
                        rana.teleportar(TableroNcurses::ALTO_TABLERO - 2,
                            TableroNcurses::ANCHO_TABLERO / 2);
                        lives--;
                    }
                    if(tecla == 'q' || tecla == 'Q'){
                        seguir = false;
                        perdio = false;
                        jugando = false;
                    }
                }
                else{
                    tablero.perderfinal();
                    int tecla = tablero.leerTecla();
                    flushinp();
                    if(tecla == 'q' || tecla == 'Q'){
                        seguir = false;
                        perdio = false;
                        jugando = false;
                    }
                }
            }
        }
    }
    return 0;
}

int nivel1(int vidas, TableroNcurses& tablero){
    tablero.setMensaje("FROGGER: nivel 1");
    // Crea la rana en la parte inferior central del tablero.
    // Se resta 2 en la fila para que quede dentro del borde inferior.
    Rana rana(TableroNcurses::ALTO_TABLERO - 2,
              TableroNcurses::ANCHO_TABLERO / 2,
              TableroNcurses::ALTO_TABLERO,
              TableroNcurses::ANCHO_TABLERO);

    

    Carro carros[3] = {
        Carro(TableroNcurses::ALTO_TABLERO /2,
                TableroNcurses::ANCHO_TABLERO -10,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                3),

        Carro(TableroNcurses::ALTO_TABLERO /2 +4,
                TableroNcurses::ANCHO_TABLERO -5,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                4),
        
        Carro(TableroNcurses::ALTO_TABLERO /2 -4,
                TableroNcurses::ANCHO_TABLERO -5,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                2)
    };

    return ciclo(tablero, rana, carros, 3, vidas, nullptr, 0);
    



}

int nivel2(int vidas, TableroNcurses& tablero){
    tablero.setMensaje("FROGGER: nivel 2");
    Agua aguas[1] = {
        Agua(1,2)
    };

    // Crea la rana en la parte inferior central del tablero.
    // Se resta 2 en la fila para que quede dentro del borde inferior.
    Rana rana(TableroNcurses::ALTO_TABLERO - 2,
              TableroNcurses::ANCHO_TABLERO / 2,
              TableroNcurses::ALTO_TABLERO,
              TableroNcurses::ANCHO_TABLERO);

    

    Carro carros[6] = {
        Carro(TableroNcurses::ALTO_TABLERO /2,
                TableroNcurses::ANCHO_TABLERO -10,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                3),

        Carro(TableroNcurses::ALTO_TABLERO /2 +4,
                TableroNcurses::ANCHO_TABLERO -20,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                4),
        
        Carro(TableroNcurses::ALTO_TABLERO /2 -4,
                TableroNcurses::ANCHO_TABLERO -5,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                2),
        
        Carro(TableroNcurses::ALTO_TABLERO /2 + 8,
                TableroNcurses::ANCHO_TABLERO -15,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                3),

        Carro(TableroNcurses::ALTO_TABLERO /2 -8,
                TableroNcurses::ANCHO_TABLERO -10,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                4),
        
        Carro(TableroNcurses::ALTO_TABLERO /2 +1,
                TableroNcurses::ANCHO_TABLERO -9,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                2)
    };

    return ciclo(tablero, rana, carros, 6, vidas, aguas, 1);
    



}