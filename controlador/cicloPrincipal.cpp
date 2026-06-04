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
#include "estadoPartida.h"
#include "lilyPad.h"
#include "tronco.h"
#include <string>

void ciclo(TableroNcurses& tablero, Rana& rana, Carro carros[],
           int cantidad, EstadoPartida& estado, Agua aguas[], int cantAgua,
           LilyPad lilyPads[], int cantLilyPads, Tronco troncos[], int cantTroncos,
           int filaSafe){
    bool perdio = false;
    bool jugando = true;

    // Guarda el momento en que inicia el contador del tiempo.
    auto ultimoSegundo = std::chrono::steady_clock::now();

    while (jugando) {
        bool estaEnAgua = false;
        bool estaSobreLily = false;
        bool estaSobreTronco = false;
        bool estaEnSafe = false;

        // Dibuja el tablero, marcador y la rana en su posicion actual.
        tablero.setMarcador(estado.vidas, estado.puntos, estado.nivel, estado.tiempo);
        tablero.dibujar();

        if(manejarEntradas(rana, tablero) == 1){
            jugando = false;
            estado.vidas = -1;
            return;
        }

        for(int i = 0; i<cantAgua;i++){
            tablero.dibujarAgua(aguas[i].obtenerXmin(),aguas[i].obtenerXmax());
            if(rana.obtenerFila() >= aguas[i].obtenerXmin() && rana.obtenerFila() <= aguas[i].obtenerXmax()){
                estaEnAgua = true;
            }
        }

        if(filaSafe >= 0){
            tablero.dibujarFilaSafe(filaSafe);
            estaEnSafe = rana.obtenerFila() == filaSafe;
        }

        for(int i = 0; i<cantLilyPads;i++){
            tablero.dibujarLilyPad(lilyPads[i].obtenerFila(),
                                   lilyPads[i].obtenerColumna(),
                                   lilyPads[i].obtenerAncho());

            if(lilyPads[i].contiene(rana.obtenerFila(), rana.obtenerColumna())){
                estaSobreLily = true;
            }
        }

        for(int i = 0; i<cantTroncos;i++){
            bool ranaIbaEnEsteTronco = troncos[i].contiene(rana.obtenerFila(), rana.obtenerColumna());
            int desplazamiento = troncos[i].mover();

            if(ranaIbaEnEsteTronco){
                rana.moverHorizontal(desplazamiento);
            }

            tablero.dibujarTronco(troncos[i].obtenerFila(),
                                  troncos[i].obtenerColumna(),
                                  troncos[i].obtenerAncho());
        }

        for(int i = 0; i<cantTroncos;i++){
            if(troncos[i].contiene(rana.obtenerFila(), rana.obtenerColumna())){
                estaSobreTronco = true;
            }
        }

        for(int i = 0; i<cantidad;i++){
            moverCarro(carros[i],tablero);
            if(rana.obtenerFila() == carros[i].obtenerFila() && rana.obtenerColumna() <= carros[i].obtenerColumna() +4 &&
            rana.obtenerColumna() >= carros[i].obtenerColumna() -1 ){
                perdio = true;
            }
        }

        if(estaEnAgua && !estaSobreLily && !estaSobreTronco){
            perdio = true;
        }

        if(estaSobreTronco){
            tablero.dibujarRanaConFondo(rana.obtenerFila(), rana.obtenerColumna(), 3);
        }
        else if(estaSobreLily){
            tablero.dibujarRanaConFondo(rana.obtenerFila(), rana.obtenerColumna(), 2);
        }
        else if(estaEnSafe){
            tablero.dibujarRanaConFondo(rana.obtenerFila(), rana.obtenerColumna(), 1);
        }
        else{
            tablero.dibujarRana(rana.obtenerFila(), rana.obtenerColumna());
        }

        refresh();

        std::this_thread::sleep_for(
    std::chrono::milliseconds(60)
        );
        auto ahora = std::chrono::steady_clock::now();

        auto tiempoPasado = std::chrono::duration_cast<std::chrono::seconds>(
            ahora - ultimoSegundo
        ).count();

        if (tiempoPasado >= 1) {
            estado.tiempo--;
            ultimoSegundo = ahora;
        }
        if (estado.tiempo <= 0) {
            perdio = true;
        }

        if(rana.obtenerFila() == 1 && !perdio){
            estado.puntos += (estado.tiempo * 100) / 60;
            return;}

        if(perdio){
            bool seguir = true;
            nodelay(stdscr, FALSE);
            while(seguir){
                if(estado.vidas > 0){
                    tablero.perder();
                    int tecla = tablero.leerTecla();
                    flushinp();
                    if(tecla == 'r' || tecla == 'R'){
                        seguir = false;
                        perdio = false;
                        rana.teleportar(TableroNcurses::ALTO_TABLERO - 2,
                            TableroNcurses::ANCHO_TABLERO / 2);
                        estado.vidas--;
                        estado.tiempo = 60;
                        ultimoSegundo = std::chrono::steady_clock::now();
                    }
                    if(tecla == 'q' || tecla == 'Q'){
                        seguir = false;
                        perdio = false;
                        jugando = false;
                        estado.vidas = -1;
                    }
                }
                else{
                    tablero.perderfinal();
                    int tecla = tablero.leerTecla();
                    flushinp();
                    if(tecla == 'q' || tecla == 'Q'){
                        estado.vidas = -1;
                        seguir = false;
                        perdio = false;
                        jugando = false;
                    }
                }
            }
            nodelay(stdscr, TRUE); 
        }
    }
    estado.vidas = -1;
}

void nivel1(EstadoPartida& estado, TableroNcurses& tablero){
    estado.nivel = 1;
    estado.tiempo = 60;
    tablero.setMensaje("FROGGER: nivel 1");
    // Crea la rana en la parte inferior central del tablero.
    // Se resta 2 en la fila para que quede dentro del borde inferior.
    Rana rana(TableroNcurses::ALTO_TABLERO - 2,
              TableroNcurses::ANCHO_TABLERO / 2,
              TableroNcurses::ALTO_TABLERO,
              TableroNcurses::ANCHO_TABLERO);

    

    Carro carros[5] = {
        Carro(TableroNcurses::ALTO_TABLERO /2,
                TableroNcurses::ANCHO_TABLERO -10,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                3, true),

        Carro(TableroNcurses::ALTO_TABLERO /2 +4,
                TableroNcurses::ANCHO_TABLERO -5,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                4, true),
        
        Carro(TableroNcurses::ALTO_TABLERO /2 -4,
                TableroNcurses::ANCHO_TABLERO -5,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                2, false),
        Carro(TableroNcurses::ALTO_TABLERO /2 -8,
                TableroNcurses::ANCHO_TABLERO -15,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                3, false),
        Carro(TableroNcurses::ALTO_TABLERO /2 +8,
                TableroNcurses::ANCHO_TABLERO -6,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                2, true)
        
    };

    ciclo(tablero, rana, carros, 5, estado, nullptr, 0, nullptr, 0, nullptr, 0, -1);
    



}

void nivel2(EstadoPartida& estado, TableroNcurses& tablero){
    estado.nivel = 2;
    estado.tiempo = 60;
    tablero.setMensaje("FROGGER: nivel 2");
    Agua aguas[1] = {
        Agua(1,6)
    };

    LilyPad lilyPads[10] = {
        LilyPad(1, 8, 2),
        LilyPad(1, 20, 2),
        LilyPad(1, 32, 2),
        LilyPad(1, 44, 2),
        LilyPad(1, 56, 2),
        LilyPad(4, 12, 2),
        LilyPad(4, 24, 2),
        LilyPad(4, 36, 2),
        LilyPad(4, 48, 2),
        LilyPad(4, 60, 2)
    };

    Tronco troncos[8] = {
        Tronco(2, 4, 12, 1, 1, TableroNcurses::ANCHO_TABLERO),
        Tronco(2, 35, 12, 1, 1, TableroNcurses::ANCHO_TABLERO),
        Tronco(3, 14, 10, -1, 1, TableroNcurses::ANCHO_TABLERO),
        Tronco(3, 48, 10, -1, 1, TableroNcurses::ANCHO_TABLERO),
        Tronco(5, 8, 12, 1, 1, TableroNcurses::ANCHO_TABLERO),
        Tronco(5, 42, 12, 1, 1, TableroNcurses::ANCHO_TABLERO),
        Tronco(6, 22, 10, -1, 1, TableroNcurses::ANCHO_TABLERO),
        Tronco(6, 56, 10, -1, 1, TableroNcurses::ANCHO_TABLERO)
    };

    int filaSafe = 7;

    // Crea la rana en la parte inferior central del tablero.
    // Se resta 2 en la fila para que quede dentro del borde inferior.
    Rana rana(TableroNcurses::ALTO_TABLERO - 2,
              TableroNcurses::ANCHO_TABLERO / 2,
              TableroNcurses::ALTO_TABLERO,
              TableroNcurses::ANCHO_TABLERO);

    

    Carro carros[6] = {
        Carro(9,
                TableroNcurses::ANCHO_TABLERO -10,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                3, true),

        Carro(11,
                TableroNcurses::ANCHO_TABLERO -20,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                4, false),
        
        Carro(13,
                TableroNcurses::ANCHO_TABLERO -5,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                2, true),
        
        Carro(15,
                TableroNcurses::ANCHO_TABLERO -15,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                3, true),

        Carro(17,
                TableroNcurses::ANCHO_TABLERO -10,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                4, false),
        
        Carro(19,
                TableroNcurses::ANCHO_TABLERO -9,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                2, true)
    };

    ciclo(tablero, rana, carros, 6, estado, aguas, 1, lilyPads, 10, troncos, 8, filaSafe);
    



}

void nivel3(EstadoPartida& estado, TableroNcurses& tablero){
    estado.nivel = 3;
    estado.tiempo = 60;
    tablero.setMensaje("FROGGER: nivel 3");
    Agua aguas[2] = {
        Agua(2,5),
        Agua(9,11)

    };

    LilyPad lilyPads[15] = {
        LilyPad(4, 12, 2),
        LilyPad(4, 24, 2),
        LilyPad(4, 36, 2),
        LilyPad(4, 48, 2),
        LilyPad(4, 60, 2),
        LilyPad(9, 12, 2),
        LilyPad(9, 24, 2),
        LilyPad(9, 36, 2),
        LilyPad(9, 48, 2),
        LilyPad(9, 60, 2),
        LilyPad(11, 12, 2),
        LilyPad(11, 24, 2),
        LilyPad(11, 36, 2),
        LilyPad(11, 48, 2),
        LilyPad(11, 60, 2)
    };

    Tronco troncos[8] = {
        Tronco(2, 4, 12, 1, 1, TableroNcurses::ANCHO_TABLERO),
        Tronco(2, 35, 12, 1, 1, TableroNcurses::ANCHO_TABLERO),
        Tronco(3, 14, 10, -1, 1, TableroNcurses::ANCHO_TABLERO),
        Tronco(3, 48, 10, -1, 1, TableroNcurses::ANCHO_TABLERO),
        Tronco(5, 8, 12, 1, 1, TableroNcurses::ANCHO_TABLERO),
        Tronco(5, 42, 12, 1, 1, TableroNcurses::ANCHO_TABLERO),
        Tronco(10, 8, 12, 1, 1, TableroNcurses::ANCHO_TABLERO),
        Tronco(10, 42, 12, 1, 1, TableroNcurses::ANCHO_TABLERO),
    };

    int filaSafe = 6;

    // Crea la rana en la parte inferior central del tablero.
    // Se resta 2 en la fila para que quede dentro del borde inferior.
    Rana rana(TableroNcurses::ALTO_TABLERO - 2,
              TableroNcurses::ANCHO_TABLERO / 2,
              TableroNcurses::ALTO_TABLERO,
              TableroNcurses::ANCHO_TABLERO);

    

    Carro carros[8] = {
        Carro(1,
                TableroNcurses::ANCHO_TABLERO -10,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                4, false),

        Carro(20,
                TableroNcurses::ANCHO_TABLERO -20,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                4, false),
        
        Carro(13,
                TableroNcurses::ANCHO_TABLERO -5,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                2, false),
        
        Carro(15,
                TableroNcurses::ANCHO_TABLERO -15,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                3, true),

        Carro(17,
                TableroNcurses::ANCHO_TABLERO -10,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                4, true),
        
        Carro(19,
                TableroNcurses::ANCHO_TABLERO -9,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                2, false),
        Carro(1,
                TableroNcurses::ANCHO_TABLERO -5,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                3, false),
        Carro(7,
                TableroNcurses::ANCHO_TABLERO -5,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                4, false)
    };

    ciclo(tablero, rana, carros, 8, estado, aguas, 2, lilyPads, 15, troncos, 8, filaSafe);
    



}


void nivel4(EstadoPartida& estado, TableroNcurses& tablero){
    estado.nivel = 4;
    estado.tiempo = 60;
    tablero.setMensaje("FROGGER: nivel 4");
    Agua aguas[2] = {
        Agua(2,10),
        Agua(13,20)

    };

    LilyPad lilyPads[35] = {
        LilyPad(20, 12, 2),
        LilyPad(20, 24, 2),
        LilyPad(20, 36, 2),
        LilyPad(20, 48, 2),
        LilyPad(20, 60, 2),
        LilyPad(16, 12, 2),
        LilyPad(16, 24, 2),
        LilyPad(16, 36, 2),
        LilyPad(16, 48, 2),
        LilyPad(16, 60, 2),
        LilyPad(10, 12, 2),
        LilyPad(10, 24, 2),
        LilyPad(10, 36, 2),
        LilyPad(10, 48, 2),
        LilyPad(10, 60, 2),
        LilyPad(8, 12, 2),
        LilyPad(8, 24, 2),
        LilyPad(8, 36, 2),
        LilyPad(8, 48, 2),
        LilyPad(8, 60, 2),
        LilyPad(6, 12, 2),
        LilyPad(6, 24, 2),
        LilyPad(6, 36, 2),
        LilyPad(6, 48, 2),
        LilyPad(6, 60, 2),
        LilyPad(4, 12, 2),
        LilyPad(4, 24, 2),
        LilyPad(4, 36, 2),
        LilyPad(4, 48, 2),
        LilyPad(4, 60, 2),
        LilyPad(2, 12, 2),
        LilyPad(2, 24, 2),
        LilyPad(2, 36, 2),
        LilyPad(2, 48, 2),
        LilyPad(2, 60, 2)
    };

    Tronco troncos[20] = {
        Tronco(19, 4, 12, 1, 1, TableroNcurses::ANCHO_TABLERO),
        Tronco(19, 35, 12, 1, 1, TableroNcurses::ANCHO_TABLERO),
        Tronco(18, 14, 10, -1, 1, TableroNcurses::ANCHO_TABLERO),
        Tronco(18, 48, 10, -1, 1, TableroNcurses::ANCHO_TABLERO),
        Tronco(17, 8, 12, 1, 1, TableroNcurses::ANCHO_TABLERO),
        Tronco(17, 42, 12, 1, 1, TableroNcurses::ANCHO_TABLERO),
        Tronco(15, 4, 12, 1, 1, TableroNcurses::ANCHO_TABLERO),
        Tronco(15, 35, 12, 1, 1, TableroNcurses::ANCHO_TABLERO),
        Tronco(14, 8, 12, 1, 1, TableroNcurses::ANCHO_TABLERO),
        Tronco(14, 42, 12, 1, 1, TableroNcurses::ANCHO_TABLERO),
        Tronco(13, 14, 10, -1, 1, TableroNcurses::ANCHO_TABLERO),
        Tronco(13, 48, 10, -1, 1, TableroNcurses::ANCHO_TABLERO),
        Tronco(9, 14, 10, -1, 1, TableroNcurses::ANCHO_TABLERO),
        Tronco(9, 48, 10, -1, 1, TableroNcurses::ANCHO_TABLERO),
        Tronco(7, 4, 12, 1, 1, TableroNcurses::ANCHO_TABLERO),
        Tronco(7, 35, 12, 1, 1, TableroNcurses::ANCHO_TABLERO),
        Tronco(5, 4, 12, 1, 1, TableroNcurses::ANCHO_TABLERO),
        Tronco(5, 35, 12, 1, 1, TableroNcurses::ANCHO_TABLERO),
        Tronco(3, 8, 12, -1, 1, TableroNcurses::ANCHO_TABLERO),
        Tronco(3, 42, 12,-1, 1, TableroNcurses::ANCHO_TABLERO)
    };

    int filaSafe = 21;

    // Crea la rana en la parte inferior central del tablero.
    // Se resta 2 en la fila para que quede dentro del borde inferior.
    Rana rana(TableroNcurses::ALTO_TABLERO - 2,
              TableroNcurses::ANCHO_TABLERO / 2,
              TableroNcurses::ALTO_TABLERO,
              TableroNcurses::ANCHO_TABLERO);

    

    Carro carros[6] = {
        Carro(1,
                TableroNcurses::ANCHO_TABLERO -10,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                3, true),

        Carro(22,
                TableroNcurses::ANCHO_TABLERO -20,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                4, false),
        
        Carro(22,
                TableroNcurses::ANCHO_TABLERO -5,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                2, false),
        
        Carro(1,
                TableroNcurses::ANCHO_TABLERO -15,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                3, true),

        Carro(11,
                TableroNcurses::ANCHO_TABLERO -10,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                5, true),
        
        Carro(12,
                TableroNcurses::ANCHO_TABLERO -9,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                2, false)
    };

    ciclo(tablero, rana, carros, 6, estado, aguas, 2, lilyPads, 35, troncos, 20, filaSafe);
    



}


void nivel5(EstadoPartida& estado, TableroNcurses& tablero, int vel){
    estado.nivel = 4;
    estado.tiempo = 60;
    tablero.setMensaje("FROGGER: nivel 4");
    Agua aguas[2] = {
        Agua(7,7),
        Agua(14,14)

    };

    LilyPad lilyPads[10] = {
        LilyPad(7, 12, 2),
        LilyPad(7, 24, 2),
        LilyPad(7, 36, 2),
        LilyPad(7, 48, 2),
        LilyPad(7, 60, 2),
        LilyPad(14, 12, 2),
        LilyPad(14, 24, 2),
        LilyPad(14, 36, 2),
        LilyPad(14, 48, 2),
        LilyPad(14, 60, 2),
    };

    //Tronco troncos[0] = {
    //};

    int filaSafe = 15;

    // Crea la rana en la parte inferior central del tablero.
    // Se resta 2 en la fila para que quede dentro del borde inferior.
    Rana rana(TableroNcurses::ALTO_TABLERO - 2,
              TableroNcurses::ANCHO_TABLERO / 2,
              TableroNcurses::ALTO_TABLERO,
              TableroNcurses::ANCHO_TABLERO);

    

    Carro carros[22] = {
        Carro(1,
                TableroNcurses::ANCHO_TABLERO -10,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                3 + vel, true),

        Carro(2,
                TableroNcurses::ANCHO_TABLERO -20,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                4 + vel, false),
        
        Carro(4,
                TableroNcurses::ANCHO_TABLERO -5,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                2 + vel, false),
        
        Carro(5,
                TableroNcurses::ANCHO_TABLERO -15,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                3 + vel, true),

        Carro(6,
                TableroNcurses::ANCHO_TABLERO -10,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                2 + vel, true),
        
        Carro(8,
                TableroNcurses::ANCHO_TABLERO -9,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                2 + vel, false),
        Carro(9,
                TableroNcurses::ANCHO_TABLERO -10,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                3 + vel, true),

        Carro(11,
                TableroNcurses::ANCHO_TABLERO -20,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                2 + vel, false),
        
        Carro(12,
                TableroNcurses::ANCHO_TABLERO -5,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                3 + vel, false),
        
        Carro(13,
                TableroNcurses::ANCHO_TABLERO -15,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                3 + vel, true),

        Carro(16,
                TableroNcurses::ANCHO_TABLERO -10,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                2 + vel, true),
        
        Carro(17,
                TableroNcurses::ANCHO_TABLERO -9,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                2 + vel, false),
        Carro(19,
                TableroNcurses::ANCHO_TABLERO -10,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                3 + vel, true),

        Carro(20,
                TableroNcurses::ANCHO_TABLERO -20,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                4 + vel, false),
        Carro(21,
                TableroNcurses::ANCHO_TABLERO -15,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                3 + vel, true),

        Carro(22,
                TableroNcurses::ANCHO_TABLERO -10,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                2 + vel, true),
        Carro(13,
                TableroNcurses::ANCHO_TABLERO -5,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                2 + vel, true),
        Carro(17,
                TableroNcurses::ANCHO_TABLERO -7,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                2 + vel, false),
        Carro(8,
                TableroNcurses::ANCHO_TABLERO -15,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                3 + vel, false),
        Carro(2,
                TableroNcurses::ANCHO_TABLERO -4,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                2 + vel, true),
        Carro(9,
                TableroNcurses::ANCHO_TABLERO -20,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                2 + vel, true),
        Carro(6,
                TableroNcurses::ANCHO_TABLERO -1,
                TableroNcurses::ALTO_TABLERO,
                TableroNcurses::ANCHO_TABLERO,
                3 + vel, true)
        
        
        
    };

    ciclo(tablero, rana, carros, 22, estado, aguas, 2, lilyPads, 10, nullptr, 0, filaSafe);
    



}

