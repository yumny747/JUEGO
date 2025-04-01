#include "Mazo.h"
#include <cstdlib>
#include <iostream>

Mazo::Mazo() {
    std::vector<string> colores = {"rojo", "verde", "azul", "amarillo"};
    for (const string& color : colores) {
        for (int i = 1; i <= 10; i++) {
            cartas.emplace_back(i, color);
        }
    }
}

void Mazo::repartirCartas(vector<Jugador>& jugadores) {
    int cartasPorJugador;
    switch (jugadores.size()) {
        case 2:
            cartasPorJugador = 18;
            break;
        case 3:
            cartasPorJugador = 12;
            break;
        case 4:
            cartasPorJugador = 9;
            break;
        default:
            return;
    }

    for (Jugador& jugador : jugadores) {
        for (int i = 0; i < cartasPorJugador; i++) {
            int indice = rand() % cartas.size();
            jugador.cartas.push_back(cartas[indice]);
            cartas.erase(cartas.begin() + indice);
        }
    }
}

void Mazo::duelo(vector<Jugador>& jugadores, const vector<int>& cartasElegidas, vector<Carta>& mazo) {
    if (cartasElegidas.empty() || jugadores.empty()) return;

    string colorDuelo = jugadores[0].cartas[cartasElegidas[0]].color;
    cout << "\nEl color del duelo es:";

    if(colorDuelo == "rojo"){
        cout<< BG_RED << " ROJO " <<RESET<< endl<<endl;
    } else if(colorDuelo == "verde"){
        cout<< BG_GREEN << " VERDE " <<RESET<< endl<<endl;
    } else if(colorDuelo == "azul"){
        cout<< BG_BLUE << " AZUL " <<RESET<< endl<<endl;
    } else {
        cout<< BG_YELLOW << " AMARILLO " <<RESET<< endl<<endl;
    }

    for (int i = 0; i < jugadores.size(); i++) {
        cout << jugadores[i].nombre << " jugó la carta ";
        Carta cartaSeleccionada = jugadores[i].cartas[cartasElegidas[i]];
        if(cartaSeleccionada.valor > 9){
                
            if(cartaSeleccionada.color == "rojo") {
                cout<<"   "<<WHITE<< BG_RED << cartaSeleccionada.valor<< RESET<<endl; 
            } else if (cartaSeleccionada.color == "verde") {
                cout<<"   "<<WHITE<< BG_GREEN << cartaSeleccionada.valor<< RESET<<endl; 
            } else if (cartaSeleccionada.color == "azul") {
                cout<<"   "<<WHITE<< BG_BLUE <<cartaSeleccionada.valor<<RESET<<endl;  
            } else if (cartaSeleccionada.color == "amarillo") {
                cout<<"   "<<WHITE<< BG_YELLOW <<cartaSeleccionada.valor<<RESET<<endl;
            }
                
        }else{
            
            if(cartaSeleccionada.color == "rojo"){
                cout<<"   "<<WHITE<< BG_RED << cartaSeleccionada.valor<<" "<<RESET<<endl; 
            }else if(cartaSeleccionada.color == "verde"){
                cout<<"   "<<WHITE<< BG_GREEN << cartaSeleccionada.valor<<" "<<RESET<<endl; 
            }else if(cartaSeleccionada.color == "azul"){
                cout<<"   "<<WHITE<< BG_BLUE <<cartaSeleccionada.valor<<" "<<RESET<<endl;  
            }else if (cartaSeleccionada.color == "amarillo") {
                cout<<"   "<<WHITE<< BG_YELLOW <<cartaSeleccionada.valor<<" "<<RESET<<endl;
            }
        }
    }

    int ganador = 0;
    for (int i = 1; i < jugadores.size(); i++) {
        Carta cartaActual = jugadores[i].cartas[cartasElegidas[i]];

        if (cartaActual.color == colorDuelo && 
            (cartaActual.valor > jugadores[ganador].cartas[cartasElegidas[ganador]].valor || 
             jugadores[ganador].cartas[cartasElegidas[ganador]].color != colorDuelo)) {
            ganador = i;
        }
    }

    cout << "\n" << jugadores[ganador].nombre << " gana el duelo!" << endl;

    // Transferir la carta ganadora al mazo y eliminarla de los jugadores
    for (int i = 0; i < jugadores.size(); i++) {
        mazo.push_back(jugadores[i].cartas[cartasElegidas[i]]);
        jugadores[i].cartas.erase(jugadores[i].cartas.begin() + cartasElegidas[i]);
    }

     for (Jugador& jugador : jugadores) {
        if (!jugador.cartas.empty()) {
            jugador.mostrarCartas();  
        }
    }

    jugadores[ganador].puntaje++;
}
void Mazo::mostrarPuntajes(const vector<Jugador>& jugadores) {
    for (const Jugador& jugador : jugadores) {
        cout << jugador.nombre << " tiene " << jugador.puntaje << " puntos." << endl;
    }
}
