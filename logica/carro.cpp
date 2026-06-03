#include "carro.h"

Carro::Carro(int filaInicial, int columnaInicial, int alto, int ancho, int velocidadjej) {
    fila = filaInicial;
    columna = columnaInicial;
    altoTablero = alto;
    anchoTablero = ancho;
    velocidad = velocidadjej;
}


// Retorna la fila actual del carro.
int Carro::obtenerFila() {
    return fila;
}

// Retorna la columna actual del carro.
int Carro::obtenerColumna() {
    return columna;
}

void Carro::moverIzquierda(int cant) { 
        columna -= cant;
}
void Carro::moverDerecha(int cant) {
        columna += cant;
}

void Carro::teleportar(int ncolumna){
    columna = ncolumna;
}

int Carro::obtenerVelocidad(){
    return velocidad;
}
