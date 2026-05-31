#ifndef RANA_H
#define RANA_H

// Esta clase representa la rana en la logica del juego.
// No usa ncurses y no dibuja nada. Solo guarda su posicion.
class Rana {
private:
    int fila;
    int columna;
    int altoTablero;
    int anchoTablero;

public:
    // Constructor: recibe la posicion inicial y el tamano del tablero.
    Rana(int filaInicial, int columnaInicial, int alto, int ancho);

    // Devuelve la fila actual de la rana.
    int obtenerFila();

    // Devuelve la columna actual de la rana.
    int obtenerColumna();

    // Cambia la posicion de la rana sin dejar que cruce los bordes.
    void moverArriba();
    void moverAbajo();
    void moverIzquierda();
    void moverDerecha();

};

#endif
