#ifndef MAZO_H
#define MAZO_H

#include <vector>
#include "Carta.h"
#include "Jugador.h"
#include "Colores.h"

using namespace std;


class Mazo {
public:
    vector<Carta> cartas;

    Mazo();
    void repartirCartas(std::vector<Jugador>& jugadores);
    void duelo(vector<Jugador>& jugadores, const vector<int>& cartasElegidas, vector<Carta>& mazo);
    void mostrarPuntajes(const vector<Jugador>& jugadores);
};

#endif
