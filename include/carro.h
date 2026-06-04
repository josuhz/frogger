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
    bool direccion;

public:
    // Constructor: recibe la posicion inicial y el tamano del tablero.
    Carro(int filaInicial, int columnaInicial, int alto, int ancho, int velocidadjej, bool dir);
    
    // Devuelve la fila actual del carro.
    int obtenerFila();

    // Devuelve la columna actual del carro.
    int obtenerColumna();

    // Cambia la posicion del carro sin dejar que cruce los bordes.
    void moverArriba();
    void moverAbajo();
    void moverIzquierda(int cant);
    void moverDerecha(int cant);
    void teleportar(int ncolumna);
    
    int obtenerVelocidad();

    bool obtenerDireccion();
    

};

#endif
