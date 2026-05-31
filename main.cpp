#include "tableroNcurses.h"
#include "rana.h"

int main() {
    // Crea el objeto tablero.
    // Al crearlo, se ejecuta el constructor y se inicia ncurses.
    TableroNcurses tablero;

    // Crea la rana en la parte inferior central del tablero.
    // Se resta 2 en la fila para que quede dentro del borde inferior.
    Rana rana(TableroNcurses::ALTO_TABLERO - 2,
              TableroNcurses::ANCHO_TABLERO / 2,
              TableroNcurses::ALTO_TABLERO,
              TableroNcurses::ANCHO_TABLERO);

    bool jugando = true;
    while (jugando) {
        // Dibuja el tablero y la rana en su posicion actual.
        tablero.dibujar();
        tablero.dibujarRana(rana.obtenerFila(), rana.obtenerColumna());

        int tecla = tablero.leerTecla();

        if (tecla == 'q' || tecla == 'Q') {
            jugando = false; // Salir del juego si se presiona 'q' o 'Q'.
        }
        else if (tecla == 'w' || tecla == 'W') {
            rana.moverArriba();
        }
        else if (tecla == 's' || tecla == 'S') {
            rana.moverAbajo();
        }
        else if (tecla == 'a' || tecla == 'A') {
            rana.moverIzquierda();
        }
        else if (tecla == 'd' || tecla == 'D') {
            rana.moverDerecha();
        }

    }
    // Cuando main termina, se destruye el objeto tablero.
    // Eso llama automaticamente al destructor y cierra ncurses.
    return 0;
}
