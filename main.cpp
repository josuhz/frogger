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
#include "jugador.h"


int main() {
    Jugador jugador;
    jugador.top1 = 0;
    jugador.top1Name = "nadie";
    jugador.top2 = 0;
    jugador.top2Name = "nadie";
    jugador.top3 = 0;
    jugador.top3Name = "sumama";
    TableroNcurses tablero;

    while(true){

        EstadoPartida estado;
        estado.vidas = 5;
        estado.puntos = 0;
        estado.nivel = 1;
        estado.tiempo = 60;

    

        bool jugar = false;
        tablero.dibujar();
        tablero.dibujarTitulo(jugador);
        nodelay(stdscr, FALSE); 
        while (!jugar){
            int tecla = tablero.leerTecla();
            flushinp();
            if(tecla == 'q' || tecla == 'Q'){
                jugar = true;
                estado.vidas = -1;
            }
            if(tecla == 'e' || tecla == 'E'){
                jugar = true;
            }
        }
        nodelay(stdscr, TRUE); 

        if(estado.vidas >= 0){
            nivel1(estado, tablero);
            if(estado.vidas >= 0) {
                nivel2(estado, tablero);
                if(estado.vidas >= 0){
                    nivel3(estado, tablero);
                    if(estado.vidas >= 0){
                        nivel4(estado,tablero);
                    }
                    int velocidad = 0;
                    while(estado.vidas >= 0){
                        nivel5(estado,tablero, velocidad);
                        velocidad++;
                    }
                }
            
            }

            nodelay(stdscr, FALSE); 
            if(estado.puntos > jugador.top1){
                std::string nombre = tablero.introducirNombre();
                jugador.top3 = jugador.top2;
                jugador.top3Name = jugador.top2Name;
                jugador.top2 = jugador.top1;
                jugador.top2Name = jugador.top1Name;
                jugador.top1 = estado.puntos;
                jugador.top1Name = nombre;    
            }
            else if(estado.puntos > jugador.top2){
                std::string nombre = tablero.introducirNombre();
                jugador.top3 = jugador.top2;
                jugador.top3Name = jugador.top2Name;
                jugador.top2 = estado.puntos;
                jugador.top2Name = nombre;
            }
            else if(estado.puntos > jugador.top3){
                std::string nombre = tablero.introducirNombre();
                jugador.top3 = estado.puntos;
                jugador.top3Name = nombre;
            }
            nodelay(stdscr, TRUE); 

  
        //mvprintw(1, 12, tablero.introducirNombre());
        }

    }
    // Cuando main termina, se destruye el objeto tablero.
    // Eso llama automaticamente al destructor y cierra ncurses.
    return 0;
}
