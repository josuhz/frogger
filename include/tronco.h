#ifndef TRONCO_H
#define TRONCO_H

// Plataforma movil del lago. La rana puede subirse y viajar con el tronco.
class Tronco {
private:
    int fila;
    int columna;
    int ancho;
    int direccion;
    int velocidad;
    int anchoTablero;

public:
    Tronco(int filaInicial, int columnaInicial, int anchoInicial,
           int direccionInicial, int velocidadInicial, int anchoDelTablero);

    int obtenerFila();
    int obtenerColumna();
    int obtenerAncho();
    int obtenerDireccion();

    bool contiene(int filaRana, int columnaRana);
    int mover();
};

#endif
