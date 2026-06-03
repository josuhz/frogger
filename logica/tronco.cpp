#include "tronco.h"

Tronco::Tronco(int filaInicial, int columnaInicial, int anchoInicial,
               int direccionInicial, int velocidadInicial, int anchoDelTablero) {
    fila = filaInicial;
    columna = columnaInicial;
    ancho = anchoInicial;
    direccion = direccionInicial;
    velocidad = velocidadInicial;
    anchoTablero = anchoDelTablero;
}

int Tronco::obtenerFila() {
    return fila;
}

int Tronco::obtenerColumna() {
    return columna;
}

int Tronco::obtenerAncho() {
    return ancho;
}

int Tronco::obtenerDireccion() {
    return direccion;
}

bool Tronco::contiene(int filaRana, int columnaRana) {
    return filaRana == fila &&
           columnaRana >= columna &&
           columnaRana < columna + ancho;
}

int Tronco::mover() {
    int desplazamiento = direccion * velocidad;
    columna += desplazamiento;

    if (columna <= -ancho) {
        columna = anchoTablero - 2;
    }
    else if (columna >= anchoTablero - 1) {
        columna = 1 - ancho;
    }

    return desplazamiento;
}
