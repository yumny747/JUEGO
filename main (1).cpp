#include <iostream> // Para entrada y salida estándar (cout, cin)
#include <vector>   // Para usar el contenedor vector
#include <cstdlib>  // Para funciones de números aleatorios (rand, srand)
#include <ctime>    // Para obtener la hora actual (time)

using namespace std; // Para evitar escribir std:: antes de cout, cin, vector, etc.

// Clase Carta: Representa una carta en el juego
class Carta {
public:
    int valor;    // El valor numérico de la carta
    string color; // El color de la carta

    // Constructor: Inicializa una carta con valor y color
    Carta(int valor, const string& color) : valor(valor), color(color) {}
};

// Clase Jugador: Representa a un jugador en el juego
class Jugador {
public:
    string nombre;      // Nombre del jugador
    vector<Carta> cartas; // Vector para almacenar las cartas del jugador
    int puntaje;        // Puntaje del jugador

    // Constructor: Inicializa un jugador con un nombre y puntaje inicial de 0
    Jugador(const string& nombre) : nombre(nombre), puntaje(0) {}

    // Función para mostrar las cartas del jugador
    void mostrarCartas() const {
        cout << nombre << " tiene las siguientes cartas:" << endl;
        for (int i = 0; i < cartas.size(); i++) {
            const Carta& carta = cartas[i];
            // Utiliza códigos de escape ANSI para colorear la salida según el color de la carta
            if (carta.color == "rojo") {
                cout << i + 1 << ": \033[31m[ ROJO ]\033[0m Valor: " << carta.valor << endl;
            } else if (carta.color == "verde") {
                cout << i + 1 << ": \033[32m[ VERDE ]\033[0m Valor: " << carta.valor << endl;
            } else if (carta.color == "azul") {
                cout << i + 1 << ": \033[34m[ AZUL ]\033[0m Valor: " << carta.valor << endl;
            } else if (carta.color == "marron") {
                cout << i + 1 << ": \033[33m[ MARRÓN ]\033[0m Valor: " << carta.valor << endl;
            }
        }
        cout << endl;
    }

    // Función para que el jugador elija una carta de su mano
    int elegirCarta() const {
        int indice;
        do {
            cout << nombre << ", elige el número de la carta que quieres jugar: ";
            cin >> indice;
        } while (indice < 1 || indice > cartas.size());
        return indice - 1; // Ajuste para el índice del vector (los índices comienzan en 0)
    }
};

// Función para repartir cartas entre jugadores
void repartirCartas(vector<Jugador>& jugadores, vector<Carta>& mazo) {
    int cartasPorJugador;
    // Determina cuántas cartas repartir según el número de jugadores
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
            return; // No debería ocurrir (manejo de error)
    }

    // Reparte las cartas a cada jugador
    for (Jugador& jugador : jugadores) {
        for (int i = 0; i < cartasPorJugador; i++) {
            int indice = rand() % mazo.size(); // Selecciona una carta aleatoria del mazo
            jugador.cartas.push_back(mazo[indice]); // Agrega la carta a la mano del jugador
            mazo.erase(mazo.begin() + indice);    // Elimina la carta del mazo
        }
    }
}

// Función para simular un duelo entre jugadores
void duelo(vector<Jugador>& jugadores, const vector<int>& cartas, vector<Carta>& mazo) {
    string colorDuelo = jugadores[0].cartas[cartas[0]].color; // El primer jugador impone el color
    cout << "\nEl color del duelo es: \033[3" << (colorDuelo == "rojo" ? '1' : colorDuelo == "verde" ? '2' : colorDuelo == "azul" ? '4' : '3') << "m" << colorDuelo << "\033[0m" << endl;

    // Muestra las cartas jugadas por cada jugador
    for (int i = 0; i < jugadores.size(); i++) {
        cout << jugadores[i].nombre << " juega \033[3" << (jugadores[i].cartas[cartas[i]].color == "rojo" ? '1' : jugadores[i].cartas[cartas[i]].color == "verde" ? '2' : jugadores[i].cartas[cartas[i]].color == "azul" ? '4' : '3') << "m" << jugadores[i].cartas[cartas[i]].valor << " de color " << jugadores[i].cartas[cartas[i]].color << "\033[0m" << endl;
    }

    // Determina al ganador del duelo
    int ganador = 0;
    for (int i = 1; i < jugadores.size(); i++) {
        if (jugadores[i].cartas[cartas[i]].color == colorDuelo && (jugadores[i].cartas[cartas[i]].valor > jugadores[ganador].cartas[cartas[ganador]].valor || jugadores[ganador].cartas[cartas[ganador]].color != colorDuelo)) {
            ganador = i;
        }
    }

    cout << "\n" << jugadores[ganador].nombre << " gana el duelo!" << endl;
    jugadores[ganador].puntaje++;

    // Elimina las cartas jugadas de la mano de cada jugador y las agrega al mazo
    for (int i = 0; i < jugadores.size(); i++) {
        mazo.push_back(jugadores[i].cartas[cartas[i]]);
        jugadores[i].cartas.erase(jugadores[i].cartas.begin() + cartas[i]);
    }
}

// Función para mostrar el puntaje de cada jugador
void mostrarPuntajes(const vector<Jugador>& jugadores) {
    for (const Jugador& jugador : jugadores) {
        cout << jugador.nombre << " tiene " << jugador.puntaje << " puntos." << endl;
    }
}

// Función principal del programa
int main() {
    srand(time(0)); // Inicializa el generador de números aleatorios

    // Crea el mazo de cartas
    vector<string> colores = {"rojo", "verde", "azul", "marron"};
    vector<Carta> mazo;
    for (const string& color : colores) {
        for (int i = 1; i <= 10; i++) {
            mazo.emplace_back(i, color); // Crea y agrega una carta al mazo
        }
    }

    // Obtiene el número de jugadores
    int numJugadores;
    do {
        cout << "Ingresa el número de jugadores (2-4): ";
        cin >> numJugadores;
    } while (numJugadores < 2 || numJugadores > 4);
    cin.ignore(); // Limpia el buffer del teclado

    // Obtiene los nombres de los jugadores
    vector<Jugador> jugadores;
    for (int i = 0; i < numJugadores; i++) {
        string nombre;
        cout << "Ingresa el nombre del Jugador " << i + 1 << ": ";
        getline(cin, nombre);
        jugadores.emplace_back(nombre);
    }

    // Reparte las cartas a los jugadores
    repartirCartas(jugadores, mazo);

    // Muestra las cartas iniciales de cada jugador
    cout << "\nCartas iniciales de los jugadores:" << endl;
    for (Jugador& jugador : jugadores) {
        jugador.mostrarCartas();
    }

    // Pregunta si quieren iniciar la partida
    char iniciarPartida;
    cout << "\n¿Desean iniciar la partida? (S/N): ";
    cin >> iniciarPartida;

    // Inicia la partida si responden 'S'
    if (iniciarPartida == 'S' || iniciarPartida == 's') {
        cout << "\nIniciando los duelos..." << endl;
        // Simula los duelos hasta que el mazo esté vacío
        while (!mazo.empty()) {
            vector<int> cartas(jugadores.size()); // Almacena los índices de las cartas jugadas
            for (int i = 0; i < jugadores.size(); i++) {
                jugadores[i].mostrarCartas();
                cartas[i] = jugadores[i].elegirCarta();
            }
            duelo(jugadores, cartas, mazo);
            mostrarPuntajes(jugadores);
        }

        // Muestra los resultados finales
        cout << "\nJuego finalizado. Resultados:" << endl;
        mostrarPuntajes(jugadores);

        // Determina al ganador o ganadores
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

        // Muestra al ganador o ganadores
        if (ganadores.size() == 1) {
            cout << "El ganador es: " << ganadores[0] << " con " << maxPuntaje << " puntos." << endl;
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


