#ifndef CARRO_H
#define CARRO_H

// Esta clase representa el carro en la logica del juego.
// No usa ncurses y no dibuja nada. Solo guarda su posicion.
class Carro {
private:
    int fila;
    int columna;
    int altoTablero;
    int anchoTablero;
    int velocidad;

public:
    // Constructor: recibe la posicion inicial y el tamano del tablero.
    Carro(int filaInicial, int columnaInicial, int alto, int ancho, int velocidadjej);
    
    // Devuelve la fila actual de la rana.
    int obtenerFila();

    // Devuelve la columna actual de la rana.
    int obtenerColumna();

    // Cambia la posicion de la rana sin dejar que cruce los bordes.
    void moverArriba();
    void moverAbajo();
    void moverIzquierda(int cant);
    void moverDerecha(int cant);
    void teleportar(int ncolumna);
    
    int obtenerVelocidad();

};

#endif
