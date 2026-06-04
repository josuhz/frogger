#include "tableroNcurses.h"
#include <ncurses.h>
#include <string>
#include "jugador.h"


// Constructor del tablero.
// Aqui se inicializa la pantalla en modo ncurses.
TableroNcurses::TableroNcurses() {
    initscr();      // Inicia ncurses y toma control de la terminal.
    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);
    noecho();       // Evita que las teclas presionadas se impriman en pantalla.
    cbreak();       // Permite leer teclas inmediatamente, sin esperar ENTER.
    curs_set(0);    // Oculta el cursor de la terminal.
    nodelay(stdscr, TRUE);   // Manin
    vidasMarcador = 0;
    puntosMarcador = 0;
    nivelMarcador = 1;
    tiempoMarcador = 0;

    // Activa colores si la terminal los soporta.
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK); // Color para la rana.
        init_pair(2, COLOR_RED, COLOR_BLACK);
        init_pair(3, COLOR_WHITE, COLOR_CYAN);
        init_pair(4, COLOR_BLACK, COLOR_GREEN); // Lily pad.
        init_pair(5, COLOR_BLACK, COLOR_YELLOW); // Tronco.
        init_pair(6, COLOR_BLACK, COLOR_GREEN); // Rana sobre lily pad.
        init_pair(7, COLOR_BLACK, COLOR_YELLOW); // Rana sobre tronco.
        init_pair(8, COLOR_BLACK, COLOR_WHITE); // Fila safe.
        init_pair(9, COLOR_GREEN, COLOR_WHITE); // Rana sobre fila safe.
    }
}

// Destructor del tablero.
// Se encarga de devolver la terminal a su estado normal.
TableroNcurses::~TableroNcurses() {
    endwin();       // Finaliza ncurses.
}

// Dibuja el tablero inicial del juego.
void TableroNcurses::dibujar() {
    erase();
    getmaxyx(stdscr, filasTerminal, columnasTerminal);
    inicioColumna = (columnasTerminal - ANCHO_TABLERO) / 2;
    mvprintw(1, inicioColumna,mensajeNivel.c_str());
    dibujarMarcador();
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
          
        }
    }

    // Mensaje temporal para salir del programa.
    mvprintw(inicioFila + ALTO_TABLERO + 1, inicioColumna,
             "Presione tecla Q para salir...");

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

    dibujarRanaConFondo(filaRana, columnaRana, 0);
}

void TableroNcurses::dibujarRanaConFondo(int filaRana, int columnaRana, int tipoFondo) {
    if (!terminalTieneEspacio(filasTerminal, columnasTerminal)) {
        return;
    }

    int colorRana = 1;

    if (tipoFondo == 1) {
        colorRana = 9; // Sobre fila safe.
    }
    else if (tipoFondo == 2) {
        colorRana = 6; // Sobre lily pad.
    }
    else if (tipoFondo == 3) {
        colorRana = 7; // Sobre tronco.
    }

    attron(COLOR_PAIR(colorRana));
    mvaddch(inicioFila + filaRana, inicioColumna + columnaRana, '@');
    attroff(COLOR_PAIR(colorRana));
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

void TableroNcurses::dibujarLilyPad(int fila, int columna, int ancho) {
    if (!terminalTieneEspacio(filasTerminal, columnasTerminal)) {
        return;
    }

    attron(COLOR_PAIR(4));
    for (int i = 0; i < ancho; i++) {
        mvaddch(inicioFila + fila, inicioColumna + columna + i, 'O');
    }
    attroff(COLOR_PAIR(4));
}

void TableroNcurses::dibujarTronco(int fila, int columna, int ancho) {
    if (!terminalTieneEspacio(filasTerminal, columnasTerminal)) {
        return;
    }

    attron(COLOR_PAIR(5));
    for (int i = 0; i < ancho; i++) {
        int columnaActual = columna + i;
        if (columnaActual > 0 && columnaActual < ANCHO_TABLERO - 1) {
            mvaddch(inicioFila + fila, inicioColumna + columnaActual, '=');
        }
    }
    attroff(COLOR_PAIR(5));
}

void TableroNcurses::dibujarFilaSafe(int fila) {
    if (!terminalTieneEspacio(filasTerminal, columnasTerminal)) {
        return;
    }

    attron(COLOR_PAIR(8));
    mvhline(inicioFila + fila, inicioColumna + 1, ' ', ANCHO_TABLERO - 2);
    attroff(COLOR_PAIR(8));
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
}

void TableroNcurses::perderfinal(){
    mvprintw((ALTO_TABLERO /2) +3, inicioColumna + 12, "Que malo, ya murio pa siempre");
    mvprintw((ALTO_TABLERO /2) +4, inicioColumna +7, "Presione Q para salir, mejor no juegue mas...");
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

void TableroNcurses::setMarcador(int vidas, int puntos, int nivel, int tiempo) {
    vidasMarcador = vidas;
    puntosMarcador = puntos;
    nivelMarcador = nivel;
    tiempoMarcador = tiempo;
}

void TableroNcurses::dibujarMarcador() {
    mvprintw(2, inicioColumna,
             "Vidas: %d  Puntos: %d  Nivel: %d  Tiempo: %d",
             vidasMarcador, 
             puntosMarcador, 
             nivelMarcador, 
             tiempoMarcador);
}

void TableroNcurses::dibujarTitulo(Jugador jugador){
    attron(COLOR_PAIR(1));
    mvprintw(4, inicioColumna + 1, " _____ _____ _____ _____ _____ _____ _____ _____ _____ _____ ____  _____ ");
    mvprintw(5, inicioColumna + 1, "|   __| __  |     |   __|   __|   __| __  |   __|  _  |   | |    \\|     |");
    mvprintw(6, inicioColumna + 1, "|   __|    -|  |  |  |  |  |  |   __|    -|   __|     | | | |  |  |  |  |");
    mvprintw(7, inicioColumna + 1, "|__|  |__|__|_____|_____|_____|_____|__|__|_____|__|__|_|___|____/|_____|");
    mvprintw(9, inicioColumna + 1, " _____ _____ ____  _____ ");
    mvprintw(10, inicioColumna + 1, "|  _  |   | |    \\|     |");
    mvprintw(11, inicioColumna + 1, "|     | | | |  |  |  |  |");
    mvprintw(12,inicioColumna + 1, "|__|__|_|___|____/|_____|");
    attroff(COLOR_PAIR(3));
    mvprintw(14, inicioColumna + 4, "Presione E para empezar");
    std::string mensaje = "Top 1: " + jugador.top1Name + ": " + std::to_string(jugador.top1); 
    mvprintw(16, inicioColumna + 6, mensaje.c_str());
    mensaje = "Top 2: " + jugador.top2Name + ": " + std::to_string(jugador.top2); 
    mvprintw(18, inicioColumna + 6, mensaje.c_str());
    mensaje = "Top 3: " + jugador.top3Name + ": " + std::to_string(jugador.top3);
    mvprintw(20, inicioColumna + 6, mensaje.c_str());


}

std::string TableroNcurses::introducirNombre(){
    mvprintw((ALTO_TABLERO/2) + 4, inicioColumna + 4, "Wow, entro en el top, esa no me la esperaba");
    nodelay(stdscr, FALSE); 
    mvprintw((ALTO_TABLERO/2) + 6, inicioColumna + 7, "Introduzca su nombre: ");

    echo();
    char buffer[4];
    getnstr(buffer, 3);
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    return buffer;
}


