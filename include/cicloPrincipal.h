#ifndef CICLOPRINCIPAL_H
#define CICLOPRINCIPAL_H
#include "carro.h"
#include "tableroNcurses.h"
#include "agua.h"

int nivel1(int vidas, TableroNcurses& tablero);
int nivel2(int vidas, TableroNcurses& tablero);
int ciclo(TableroNcurses& tablero, Rana& rana, Carro carros[], int cantidad, int vidas, Agua aguas[], int cantAgua);

#endif