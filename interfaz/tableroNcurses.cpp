#include "tableroNcurses.h"
#include <ncurses.h>
#include <string>


// Constructor del tablero.
// Aqui se inicializa la pantalla en modo ncurses.
TableroNcurses::TableroNcurses() {
    initscr();      // Inicia ncurses y toma control de la terminal.
    noecho();       // Evita que las teclas presionadas se impriman en pantalla.
    cbreak();       // Permite leer teclas inmediatamente, sin esperar ENTER.
    curs_set(0);    // Oculta el cursor de la terminal.
    nodelay(stdscr, TRUE);   // Manin

    // Activa colores si la terminal los soporta.
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK); // Color para la rana.
        init_pair(2, COLOR_RED, COLOR_BLACK);
        init_pair(3, COLOR_WHITE, COLOR_CYAN);
    }
}

// Destructor del tablero.
// Se encarga de devolver la terminal a su estado normal.
TableroNcurses::~TableroNcurses() {
    endwin();       // Finaliza ncurses.
}

// Dibuja el tablero inicial del juego.
void TableroNcurses::dibujar() {
    clear();        // Limpia toda la pantalla.
    getmaxyx(stdscr, filasTerminal, columnasTerminal);
    inicioColumna = (columnasTerminal - ANCHO_TABLERO) / 2;
    mvprintw(1, inicioColumna,mensajeNivel.c_str());
    // Obtiene el tamano actual de la terminal.
    // ncurses trabaja con filas y columnas de caracteres, no con pixeles.
    //int filasTerminal;
    //int columnasTerminal;
    //getmaxyx(stdscr, filasTerminal, columnasTerminal);

    // Si la terminal es muy pequena, no intentamos dibujar el tablero.
    if (!terminalTieneEspacio(filasTerminal, columnasTerminal)) {
        mvprintw(2, 2, "La terminal es muy pequena.");
        mvprintw(3, 2, "Agrandela para poder mostrar el tablero de Frogger.");
        refresh();
        return;
    }

    // Calcula donde empieza el tablero para que quede centrado.
    //int inicioColumna = (columnasTerminal - ANCHO_TABLERO) / 2;

    // Escribe un titulo arriba del tablero.
    //mvprintw(1, inicioColumna, "FROGGER - Segunda Etapa");

    // Este doble for recorre la matriz visual del tablero.
    for (int fila = inicioFila; fila < inicioFila + ALTO_TABLERO; fila++) {
        for (int columna = inicioColumna; columna < inicioColumna + ANCHO_TABLERO; columna++) {

            // Estas variables indican si la celda actual pertenece a un borde.
            bool bordeSuperior = fila == inicioFila;
            bool bordeInferior = fila == inicioFila + ALTO_TABLERO - 1;
            bool bordeIzquierdo = columna == inicioColumna;
            bool bordeDerecho = columna == inicioColumna + ANCHO_TABLERO - 1;

            // Si estamos en los bordes, dibujamos '#'.
            if (bordeSuperior || bordeInferior || bordeIzquierdo || bordeDerecho) {
                mvaddch(fila, columna, '#');
            }
            // Si no estamos en los bordes, dejamos espacio vacio.
            else {
                mvaddch(fila, columna, ' ');
            }
        }
    }

    // Mensaje temporal para salir del programa.
    mvprintw(inicioFila + ALTO_TABLERO + 1, inicioColumna,
             "Presione cualquier tecla para salir...");

    // Actualiza la pantalla para mostrar lo dibujado.
}

// Dibuja la rana usando coordenadas logicas del tablero.
// filaRana y columnaRana son posiciones dentro del tablero, no de la terminal.
void TableroNcurses::dibujarRana(int filaRana, int columnaRana) {
    //int filasTerminal;
    //int columnasTerminal;
    //getmaxyx(stdscr, filasTerminal, columnasTerminal);

    // Si el tablero no cabe, no intentamos dibujar la rana.
    if (!terminalTieneEspacio(filasTerminal, columnasTerminal)) {
        return;
    }

    // Usa el mismo calculo de centrado que dibujar().
    //int inicioColumna = (columnasTerminal - ANCHO_TABLERO) / 2;

    // La rana se representa como '@' en color verde.
    attron(COLOR_PAIR(1));
    mvaddch(inicioFila + filaRana, inicioColumna + columnaRana, '@');
    attroff(COLOR_PAIR(1));
}

void TableroNcurses::dibujarCarro(int filaCarro, int columnaCarro) {
    //int filasTerminal;
    //int columnasTerminal;
    //getmaxyx(stdscr, filasTerminal, columnasTerminal);

    // Si el tablero no cabe, no intentamos dibujar la rana.
    if (!terminalTieneEspacio(filasTerminal, columnasTerminal)) {
        return;
    }

    // Usa el mismo calculo de centrado que dibujar().
    //int inicioColumna = (columnasTerminal - ANCHO_TABLERO) / 2;

    // La rana se representa como '@' en color verde.
    attron(COLOR_PAIR(2));
    mvprintw(inicioFila + filaCarro, inicioColumna + columnaCarro, "=00=");
    attroff(COLOR_PAIR(2));

}

// Lee una tecla del usuario y la retorna.
int TableroNcurses::leerTecla() {
    return getch(); // Devuelve el codigo de la tecla presionada.
}

// Espera una tecla del usuario.
void TableroNcurses::esperarTecla() {
    getch();        // Detiene el programa hasta que se presione una tecla.
}

// Retorna true si la terminal tiene suficiente espacio para el tablero.
bool TableroNcurses::terminalTieneEspacio(int filasTerminal, int columnasTerminal) {
    return filasTerminal >= ALTO_TABLERO + MARGEN_VERTICAL &&
           columnasTerminal >= ANCHO_TABLERO + MARGEN_HORIZONTAL;
}

void TableroNcurses::perder(){
    mvprintw((ALTO_TABLERO /2) +3, inicioColumna + 12, "QUE TOONTOOO C murio");
    mvprintw((ALTO_TABLERO /2) +4, inicioColumna + 7, "Presione R para repetir por tonto");
    refresh();
}

void TableroNcurses::perderfinal(){
    mvprintw((ALTO_TABLERO /2) +3, inicioColumna + 12, "Que malo, ya murio pa siempre");
    mvprintw((ALTO_TABLERO /2) +4, inicioColumna +7, "Presione Q para salir, mejor no juegue mas...");
    refresh();
}

void TableroNcurses::dibujarVida(int fila, int columna){
    attron(COLOR_PAIR(1));
    mvprintw( fila +2, columna + inicioColumna, "@");
    attroff(COLOR_PAIR(1));
}

void TableroNcurses::dibujarAgua(int filaMin, int filaMax){
    attron(COLOR_PAIR(3));
    for(int i = filaMin;i<=filaMax;i++){
        mvhline(
            inicioFila + i,
            inicioColumna + 1,
            '~',
            ANCHO_TABLERO - 2);
    }
    attroff(COLOR_PAIR(3));
}

void TableroNcurses::setMensaje(const std::string& mensaje){
    mensajeNivel = mensaje;
}
