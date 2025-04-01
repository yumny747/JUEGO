#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <vector>
#include "Carta.h"
#include "Colores.h"

using namespace std;

class Jugador {
public:
    string nombre;
    vector<Carta> cartas;
    int puntaje;

    Jugador(const string& nombre);
    void mostrarCartas() const;
    int elegirCarta();
};

#endif
