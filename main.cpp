#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Carta.h"
#include "Jugador.h"
#include "Mazo.h"

using namespace std;

int main() {
    srand(time(0));

    Mazo mazo;
    int numJugadores;
    do {
        cout << "Ingresa el número de jugadores (2-4): ";
        cin >> numJugadores;
    } while (numJugadores < 2 || numJugadores > 4);
    cin.ignore();

    vector<Jugador> jugadores;
    for (int i = 0; i < numJugadores; i++) {
        string nombre;
        cout << "Ingresa el nombre del Jugador " << i + 1 << ": ";
        getline(cin, nombre);
        jugadores.emplace_back(nombre);
    }

    mazo.repartirCartas(jugadores);

    char iniciarPartida;
    cout << "\n¿Desean iniciar la partida? (S/N): ";
    cin >> iniciarPartida;

    cout << "\nCartas de los jugadores:" << endl;
    for (Jugador& jugador : jugadores) {
        jugador.mostrarCartas();
    }

    if (iniciarPartida == 'S' || iniciarPartida == 's') {
        cout << "\nIniciando los duelos..." << endl;
        while (true) {
            vector<int> cartas(jugadores.size());
            bool todosSinCartas = true;

            for (int i = 0; i < jugadores.size(); i++) {
                if (!jugadores[i].cartas.empty()) {
                    todosSinCartas = false;
                    cartas[i] = jugadores[i].elegirCarta();
                } else {
                    cartas[i] = -1;
                }
            }

            if (todosSinCartas) {
                break;
            }

            mazo.duelo(jugadores, cartas, mazo.cartas);
        }

        cout << "\nResultados finales:" << endl << endl;
        mazo.mostrarPuntajes(jugadores);

        // Determinar al ganador
        int maxPuntaje = 0;
        vector<string> ganadores;
        for (const Jugador& jugador : jugadores) {
            if (jugador.puntaje > maxPuntaje) {
                maxPuntaje = jugador.puntaje;
                ganadores.clear();
                ganadores.push_back(jugador.nombre);
            } else if (jugador.puntaje == maxPuntaje) {
                ganadores.push_back(jugador.nombre);
            }
        }

        if (ganadores.size() == 1) {
            cout << "\nEl ganador es: " << ganadores[0] << " con " << maxPuntaje << " puntos." << endl;
        } else {
            cout << "Empate entre: ";
            for (int i = 0; i < ganadores.size(); i++) {
                cout << ganadores[i];
                if (i < ganadores.size() - 1) {
                    cout << ", ";
                }
            }
            cout << " con " << maxPuntaje << " puntos." << endl;
        }
    } else {
        cout << "Partida cancelada." << endl;
    }

    return 0;
}
