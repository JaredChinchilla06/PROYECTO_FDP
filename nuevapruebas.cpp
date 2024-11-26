#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Resultados {
    int ganados = 0;
    int perdidos = 0;
    int empatados = 0;
};

string obtenerStringDeCarta(int carta, char palo) {
    string nombreCarta;
    if (carta == 1) {
        nombreCarta = "A";  // As
    } else if (carta == 11) {
        nombreCarta = "J";  // Jota
    } else if (carta == 12) {
        nombreCarta = "Q";  // Reina
    } else if (carta == 13) {
        nombreCarta = "K";  // Rey
    } else {
        nombreCarta = to_string(carta);  // Las cartas numéricas se representan por su valor
    }

    string simboloPalo;
    if (palo == 'H') {
        simboloPalo = "♥";  // Corazones
    } else if (palo == 'D') {
        simboloPalo = "♦";  // Diamantes
    } else if (palo == 'C') {
        simboloPalo = "♣";  // Tréboles
    } else if (palo == 'S') {
        simboloPalo = "♠";  // Picas
    }

    return nombreCarta + simboloPalo;
}

void barajarMazo(vector<int>& mazo, vector<char>& palos) {
    srand(time(0));  
    for (int i = 0; i < mazo.size(); i++) {
        int j = rand() % mazo.size();  
        swap(mazo[i], mazo[j]);       
        swap(palos[i], palos[j]);     
    }
}

int calcularValorMano(const vector<int>& mano) {
    int valor = 0;
    int ases = 0;

    for (int carta : mano) {
        if (carta == 1) {
            ases++;
            valor += 11;
        } else if (carta > 10) {
            valor += 10;
        } else {
            valor += carta;
        }
    }

    while (valor > 21 && ases > 0) {
        valor -= 10;
        ases--;
    }

    return valor;
}

void mostrarMano(const vector<int>& mano, const vector<char>& palos, const string& nombreJugador) {
    cout << nombreJugador << " tiene las cartas: ";
    for (size_t i = 0; i < mano.size(); ++i) {
        cout << obtenerStringDeCarta(mano[i], palos[i]) << " ";
    }
    cout << " - Valor total: " << calcularValorMano(mano) << endl;
}

void repartirCarta(vector<int>& mazo, vector<char>& palos, vector<int>& mano) {
    mano.push_back(mazo.back());
    palos.push_back(palos.back());
    mazo.pop_back();
    palos.pop_back();
}

void mostrarInstrucciones() {
    cout << "\n=== INSTRUCCIONES DEL JUEGO ===" << endl;
    cout << "El Blackjack es un juego de cartas entre dos jugadores y un dealer." << endl;
    cout << "El objetivo del juego es tener un puntaje lo más cercano posible a 21, sin pasarse." << endl;
    cout << "Cada carta tiene un valor numérico: las cartas numéricas tienen su valor (2-10),"
         << " las figuras (J, Q, K) valen 10, y el As puede valer 1 o 11, según convenga." << endl;
    cout << "Los jugadores reciben dos cartas y pueden pedir más cartas ('hit') o quedarse ('stand')."
         << " El dealer juega después de que ambos jugadores terminen su turno." << endl;
    cout << "Si un jugador supera 21, pierde automáticamente. Si el dealer se pasa de 21," 
         << " los jugadores ganan." << endl;
    cout << " ¡Buena suerte y diviértete!\n" << endl;
}

void jugarBlackjack(const string& nombreJugador1, const string& nombreJugador2, Resultados& resultadosJugador1, Resultados& resultadosJugador2) {
    vector<int> mazo;    
    vector<char> palos;  
    vector<int> manoJugador1;  
    vector<int> manoJugador2;  
    vector<int> manoDealer;    

    char todosLosPalos[] = {'H', 'D', 'C', 'S'};
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j <= 13; j++) {
            mazo.push_back(j > 10 ? 10 : j);  
            palos.push_back(todosLosPalos[i]);  
        }
    }

    barajarMazo(mazo, palos);  

    repartirCarta(mazo, palos, manoJugador1);
    repartirCarta(mazo, palos, manoJugador1);
    repartirCarta(mazo, palos, manoJugador2);
    repartirCarta(mazo, palos, manoJugador2);
    repartirCarta(mazo, palos, manoDealer);
    repartirCarta(mazo, palos, manoDealer);

    mostrarMano(manoJugador1, palos, nombreJugador1);
    char eleccion;
    while (calcularValorMano(manoJugador1) < 21) {
        cout << nombreJugador1 << ", ¿quieres pedir otra carta (s/n)? ";
        cin >> eleccion;

        if (eleccion == 's' || eleccion == 'S') {
            repartirCarta(mazo, palos, manoJugador1);
            mostrarMano(manoJugador1, palos, nombreJugador1);

            if (calcularValorMano(manoJugador1) > 21) {
                cout << nombreJugador1 << ", te pasaste de 21. ¡Perdiste!" << endl;
                resultadosJugador1.perdidos++; 
                return;
            }
        } else {
            break; 
        }
    }

    mostrarMano(manoJugador2, palos, nombreJugador2);
    while (calcularValorMano(manoJugador2) < 21) {
        cout << nombreJugador2 << ", ¿quieres pedir otra carta (s/n)? ";
        cin >> eleccion;

        if (eleccion == 's' || eleccion == 'S') {
            repartirCarta(mazo, palos, manoJugador2);
            mostrarMano(manoJugador2, palos, nombreJugador2);

            if (calcularValorMano(manoJugador2) > 21) {
                cout << nombreJugador2 << ", te pasaste de 21. ¡Perdiste!" << endl;
                resultadosJugador2.perdidos++;  
                return;
            }
        } else {
            break; 
        }
    }

    mostrarMano(manoDealer, palos, "Dealer");
    while (calcularValorMano(manoDealer) < 17) {
        cout << "Dealer pide otra carta." << endl;
        repartirCarta(mazo, palos, manoDealer);
        mostrarMano(manoDealer, palos, "Dealer");
    }

    int valorJugador1 = calcularValorMano(manoJugador1);
    int valorJugador2 = calcularValorMano(manoJugador2);
    int valorDealer = calcularValorMano(manoDealer);

    // Si el dealer se pasa de 21, todos los jugadores que no se hayan pasado ganan
    if (valorDealer > 21) {
        cout << "El dealer se pasó de 21. Los jugadores que no se pasaron ganan." << endl;
        if (valorJugador1 <= 21 && valorJugador2 <= 21) {
            // Si ambos jugadores no se pasaron, se compara quien tiene mejor valor
            if (valorJugador1 > valorJugador2) {
                cout << nombreJugador1 << " gana!" << endl;
                resultadosJugador1.ganados++;
                resultadosJugador2.perdidos++;
            } else if (valorJugador2 > valorJugador1) {
                cout << nombreJugador2 << " gana!" << endl;
                resultadosJugador2.ganados++;
                resultadosJugador1.perdidos++;
            } else {
                cout << "Empate entre los jugadores!" << endl;
                resultadosJugador1.empatados++;
                resultadosJugador2.empatados++;
            }
        } else if (valorJugador1 <= 21) {
            cout << nombreJugador1 << " gana!" << endl;
            resultadosJugador1.ganados++;
            resultadosJugador2.perdidos++;
        } else {
            cout << nombreJugador2 << " gana!" << endl;
            resultadosJugador2.ganados++;
            resultadosJugador1.perdidos++;
        }
    } else {
        // Si el dealer no se pasa de 21, se compara con los jugadores
        if (valorJugador1 > 21) {
            cout << nombreJugador1 << " se pasó de 21. Dealer gana." << endl;
            resultadosJugador1.perdidos++;
        } else if (valorJugador1 > valorDealer) {
            cout << nombreJugador1 << " gana." << endl;
            resultadosJugador1.ganados++;
        } else if (valorJugador1 == valorDealer) {
            cout << nombreJugador1 << " empata con el Dealer." << endl;
            resultadosJugador1.empatados++;
        } else {
            cout << "Dealer gana a " << nombreJugador1 << "." << endl;
            resultadosJugador1.perdidos++;
        }

        if (valorJugador2 > 21) {
            cout << nombreJugador2 << " se pasó de 21. Dealer gana." << endl;
            resultadosJugador2.perdidos++;
        } else if (valorJugador2 > valorDealer) {
            cout << nombreJugador2 << " gana." << endl;
            resultadosJugador2.ganados++;
        } else if (valorJugador2 == valorDealer) {
            cout << nombreJugador2 << " empata con el Dealer." << endl;
            resultadosJugador2.empatados++;
        } else {
            cout << "Dealer gana a " << nombreJugador2 << "." << endl;
            resultadosJugador2.perdidos++;
        }
    }
}

int main() {
    string nombreJugador1, nombreJugador2;
    Resultados resultadosJugador1, resultadosJugador2;

    cout << "Introduce el nombre del Jugador 1: ";
    getline(cin, nombreJugador1);
    cout << "Introduce el nombre del Jugador 2: ";
    getline(cin, nombreJugador2);

    int opcion;
    do {
        cout << "\n1. Jugar\n2. Ver Instrucciones\n3. Ver Resultados\n4. Salir\n";
        cout << "Selecciona una opción: ";
        cin >> opcion;
        cin.ignore(); // Para ignorar el salto de línea después de leer el número

        switch (opcion) {
            case 1:
                jugarBlackjack(nombreJugador1, nombreJugador2, resultadosJugador1, resultadosJugador2);
                break;
            case 2:
                mostrarInstrucciones();
                break;
            case 3:
                cout << "\nRESULTADOS:\n";
                cout << nombreJugador1 << " - Ganados: " << resultadosJugador1.ganados 
                     << ", Perdidos: " << resultadosJugador1.perdidos 
                     << ", Empatados: " << resultadosJugador1.empatados << endl;
                cout << nombreJugador2 << " - Ganados: " << resultadosJugador2.ganados 
                     << ", Perdidos: " << resultadosJugador2.perdidos 
                     << ", Empatados: " << resultadosJugador2.empatados << endl;
                break;
            case 4:
                cout << "¡Hasta luego!" << endl;
                break;
            default:
                cout << "Opción inválida. Intenta nuevamente." << endl;
        }
    } while (opcion != 4);

    return 0;
}