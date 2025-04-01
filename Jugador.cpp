#include "Jugador.h"
#include <iostream>


Jugador::Jugador(const string& nombre) {
    this->nombre = nombre;
    this->puntaje = 0;
}

void Jugador::mostrarCartas() const {
    cout << "\n" << nombre << " tiene las siguientes cartas: \n" << endl;
    for (int i = 0; i < cartas.size(); i++) {
        const Carta& carta = cartas[i];
 
        if(carta.valor > 9){
                
            if (carta.color == "rojo") {
                cout <<"   "<<WHITE<< BG_RED << carta.valor<< RESET; 
            } else if (carta.color == "verde") {
                cout <<"   "<<WHITE<< BG_GREEN << carta.valor<< RESET; 
            } else if (carta.color == "azul") {
                cout <<"   "<<WHITE<< BG_BLUE <<carta.valor<<RESET;  
            } else if (carta.color == "amarillo") {
                cout <<"   "<<WHITE<< BG_YELLOW <<carta.valor<<RESET;
            }
                
        }else{
            
            if(carta.color == "rojo"){
                cout <<"   "<<WHITE<< BG_RED << carta.valor<<" "<<RESET; 
            }else if(carta.color == "verde"){
                cout <<"   "<<WHITE<< BG_GREEN << carta.valor<<" "<<RESET; 
            }else if(carta.color == "azul"){
                cout <<"   "<<WHITE<< BG_BLUE <<carta.valor<<" "<<RESET;  
            }else if (carta.color == "amarillo") {
                cout <<"   "<<WHITE<< BG_YELLOW <<carta.valor<<" "<<RESET; 
            }
        }
    }
    cout<<endl;
}

int Jugador::elegirCarta() {
 
    int indice;
    cout<<"\n" << nombre << ", elige la posición de la carta que quieres jugar: ";
    cin >> indice;

    while (indice < 1 || indice > cartas.size()) {
        cout << "Índice inválido. Elige un número entre 1 y " << cartas.size() << ": ";
        cin >> indice;
    }

    return indice - 1;
}
