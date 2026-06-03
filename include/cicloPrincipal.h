#ifndef CICLOPRINCIPAL_H
#define CICLOPRINCIPAL_H
#include "carro.h"
#include "tableroNcurses.h"
#include "agua.h"
#include "estadoPartida.h"
#include "lilyPad.h"
#include "tronco.h"

void nivel1(EstadoPartida& estado, TableroNcurses& tablero);
void nivel2(EstadoPartida& estado, TableroNcurses& tablero);
void ciclo(TableroNcurses& tablero, Rana& rana, Carro carros[],
           int cantidad, EstadoPartida& estado, Agua aguas[], int cantAgua,
           LilyPad lilyPads[], int cantLilyPads, Tronco troncos[], int cantTroncos,
           int filaSafe);

#endif
