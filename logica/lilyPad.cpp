#include "lilyPad.h"

LilyPad::LilyPad(int filaInicial, int columnaInicial, int anchoInicial) {
    fila = filaInicial;
    columna = columnaInicial;
    ancho = anchoInicial;
}

int LilyPad::obtenerFila() {
    return fila;
}

int LilyPad::obtenerColumna() {
    return columna;
}

int LilyPad::obtenerAncho() {
    return ancho;
}

