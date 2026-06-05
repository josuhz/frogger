#ifndef TABLERO_NCURSES_H
#define TABLERO_NCURSES_H
#include <string>
#include "jugador.h"

// Esta clase representa el tablero visual del juego usando ncurses.
// Por ahora inicia ncurses, dibuja un tablero centrado y espera una tecla.
class TableroNcurses {
public:
    // Medidas fijas del tablero logico del juego.
    // La terminal puede ser mas grande, pero el tablero mantiene este tamano.
    static const int ALTO_TABLERO = 25;
    static const int ANCHO_TABLERO = 75;
    int filasTerminal;
    int columnasTerminal;
    int inicioColumna;
    int vidasMarcador;
    int puntosMarcador;
    int nivelMarcador;
    int tiempoMarcador;
    static const int inicioFila = 3;
    std::string mensajeNivel;

    // Espacio extra necesario para titulo y mensaje inferior.
    static const int MARGEN_VERTICAL = 5;
    static const int MARGEN_HORIZONTAL = 4;

    // Constructor: se ejecuta automaticamente cuando se crea un TableroNcurses.
    // Aqui vamos a iniciar ncurses.
    TableroNcurses();

    // Destructor: se ejecuta automaticamente cuando el objeto deja de existir.
    // Aqui cerramos ncurses correctamente.
    ~TableroNcurses();

    // Dibuja el tablero en pantalla.
    void dibujar();

    // Dibuja la rana en una posicion dentro del tablero.
    void dibujarRana(int filaRana, int columnaRana);
    void dibujarRanaConFondo(int filaRana, int columnaRana, int tipoFondo);
    
    // Dibuja el rano en una posición dentro del tablero
    void dibujarCarro(int filaCarro, int columnaCarro);
    void dibujarLilyPad(int fila, int columna, int ancho);
    void dibujarTronco(int fila, int columna, int ancho);
    void dibujarFilaSafe(int fila);

    //lee tecla
    int leerTecla();

    // Espera a que el usuario presione una tecla.
    void esperarTecla();

    void perder();

    void perderfinal();

    void dibujarVida(int fila, int columna);

    void dibujarAgua(int filamin, int filamax);

    void setMensaje(const std::string& mensaje);

    void setMarcador(int vidas, int puntos, int nivel, int tiempo);

    void dibujarMarcador();


    void dibujarTitulo(Jugador jugador);

    std::string introducirNombre();
    
    void dibujarTablero();
private:
    // Revisa si la terminal tiene espacio suficiente para mostrar el tablero.
    bool terminalTieneEspacio(int filasTerminal, int columnasTerminal);
};

#endif
