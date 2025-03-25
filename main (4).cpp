#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Estructura de la carta
struct Carta {
    int valor;  // valor de la carta (1 a 10)
    string color;  // color de la carta (rojo, verde, azul, marron)
};

// Estructura del jugador
struct Jugador {
    string nombre;
    vector<Carta> cartas;
    int puntaje = 0;  // Puntaje inicial
};

// Función para generar una carta aleatoria
Carta generarCarta(int valor, const string& color) {
    Carta c;
    c.valor = valor;
    c.color = color;
    return c;
}

// Función para repartir cartas entre jugadores
void repartirCartas(vector<Jugador>& jugadores, vector<Carta>& mazo) {
    for (int i = 0; i < jugadores.size(); i++) {
        for (int j = 0; j < 6; j++) {  // Cada jugador recibe 6 cartas
            int indice = rand() % mazo.size();
            jugadores[i].cartas.push_back(mazo[indice]);
            mazo.erase(mazo.begin() + indice);  // Elimina la carta del mazo
        }
    }
}

// Función para simular un duelo entre dos jugadores
void duelo(Jugador& jugador1, Jugador& jugador2) {
    // Elige las cartas aleatorias de ambos jugadores
    int carta1 = rand() % jugador1.cartas.size();
    int carta2 = rand() % jugador2.cartas.size();

    // Compara las cartas
    cout << jugador1.nombre << " juega " << jugador1.cartas[carta1].valor << " de color " << jugador1.cartas[carta1].color << endl;
    cout << jugador2.nombre << " juega " << jugador2.cartas[carta2].valor << " de color " << jugador2.cartas[carta2].color << endl;

    if (jugador1.cartas[carta1].valor > jugador2.cartas[carta2].valor) {
        cout << jugador1.nombre << " gana el duelo!" << endl;
        jugador1.puntaje++;
    } else if (jugador1.cartas[carta1].valor < jugador2.cartas[carta2].valor) {
        cout << jugador2.nombre << " gana el duelo!" << endl;
        jugador2.puntaje++;
    } else {
        cout << "Empate!" << endl;
    }

    // Elimina las cartas que se usaron
    jugador1.cartas.erase(jugador1.cartas.begin() + carta1);
    jugador2.cartas.erase(jugador2.cartas.begin() + carta2);
}

// Función para mostrar el puntaje
void mostrarPuntajes(const vector<Jugador>& jugadores) {
    for (const auto& jugador : jugadores) {
        cout << jugador.nombre << " tiene " << jugador.puntaje << " puntos." << endl;
    }
}

// Función principal
int main() {
    srand(time(0));  // Inicializa el generador de números aleatorios

    // Definir los colores
    vector<string> colores = {"rojo", "verde", "azul", "marron"};
    
    // Crear un mazo de 36 cartas (9 cartas por color con valores del 1 al 10)
    vector<Carta> mazo;
    for (const string& color : colores) {
        for (int i = 1; i <= 10; i++) {
            mazo.push_back(generarCarta(i, color));
        }
    }

    // Crear los jugadores
    vector<Jugador> jugadores(4);
    for (int i = 0; i < jugadores.size(); i++) {
        jugadores[i].nombre = "Jugador " + to_string(i + 1);
        cout <<"ingresa tu nombre">><< i + 1 << ": ";
         
         
    }

    // Repartir las cartas a los jugadores
    repartirCartas(jugadores, mazo);

 

    // Mostrar puntajes finales
    cout << "\nPuntajes finales:" << endl;
    mostrarPuntajes(jugadores);

    // Determinar al ganador
    int maxPuntaje = 0;
    string ganador;
    for (const auto& jugador : jugadores) {
        if (jugador.puntaje > maxPuntaje) {
            maxPuntaje = jugador.puntaje;
            ganador = jugador.nombre;
        }
    }
    
    cout << "El ganador es: " << ganador << " con " << maxPuntaje << " puntos." << endl;

    return 0;
}
