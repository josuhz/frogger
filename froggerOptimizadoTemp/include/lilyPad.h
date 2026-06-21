#ifndef LILYPAD_H
#define LILYPAD_H

// Plataforma fija del lago. Si la rana esta encima, no se ahoga.
class LilyPad {
private:
    int fila;
    int columna;
    int ancho;

public:
    LilyPad(int filaInicial, int columnaInicial, int anchoInicial);

    int obtenerFila();
    int obtenerColumna();
    int obtenerAncho();
};

#endif
