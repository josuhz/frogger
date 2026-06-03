#include "rana.h"

// Guarda la posicion inicial de la rana y los limites del tablero.
Rana::Rana(int filaInicial, int columnaInicial, int alto, int ancho) {
    fila = filaInicial;
    columna = columnaInicial;
    altoTablero = alto;
    anchoTablero = ancho;
}

// Retorna la fila actual de la rana.
int Rana::obtenerFila() {
    return fila;
}

// Retorna la columna actual de la rana.
int Rana::obtenerColumna() {
    return columna;
}

// Estas funciones cambian la posicion de la rana en la logica del juego.
void Rana::moverArriba() {
    if (fila > 1) { // Evita mover sobre el borde superior.
        fila--;
    }
}  
void Rana::moverAbajo() {
    if (fila < altoTablero - 2) { // Evita mover sobre el borde inferior.
        fila++;
    }
}
void Rana::moverIzquierda() {
    if (columna > 1) { // Evita mover sobre el borde izquierdo.
        columna--;
    }
}
void Rana::moverDerecha() {
    if (columna < anchoTablero - 2) { // Evita mover sobre el borde derecho.
        columna++;
    }
}

void Rana::moverHorizontal(int cantidad){
    columna += cantidad;

    if (columna < 1) {
        columna = 1;
    }
    if (columna > anchoTablero - 2) {
        columna = anchoTablero - 2;
    }
}

void Rana::teleportar(int filon, int columnon){
    fila = filon;
    columna = columnon;
}
