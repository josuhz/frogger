#ifndef JUGADOR_H
#define JUGADOR_H
#include <string>
// Guarda los datos generales de la partida.
// Son los que se muestran en el marcador.
struct Jugador {
    int top1;
    std::string top1Name;
    int top2;
    std::string top2Name;
    int top3;
    std::string top3Name;
};

#endif