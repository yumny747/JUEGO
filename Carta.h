#ifndef CARTA_H
#define CARTA_H

#include <string>
#include "Colores.h"

using namespace std;

class Carta {
public:
    int valor;
    string color;

    Carta(int valor, const string& color);
};
#endif
