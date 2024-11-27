#include <iostream>  // Biblioteca estándar para entrada y salida (como cout, cin)
#include <vector>    // Biblioteca que permite usar el contenedor vector (dinámico)
#include <ctime>     // Biblioteca para trabajar con el tiempo (necesario para la función rand)
#include <cstdlib>   // Biblioteca para usar la función rand() para números aleatorios

using namespace std;  // Para evitar escribir "std::" antes de cada función de la biblioteca estándar

// Estructura para almacenar los resultados de un jugador
struct Resultados {
    int ganados = 0;   // Número de juegos ganados
    int perdidos = 0;  // Número de juegos perdidos
    int empatados = 0; // Número de juegos empatados
};

// Función que convierte una carta y su palo en una cadena representativa (ej: "10♠")
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

// Función para barajar el mazo de cartas
void barajarMazo(vector<int>& mazo, vector<char>& palos) {
    srand(time(0));  // Semilla para el generador de números aleatorios con el tiempo actual
    for (int i = 0; i < mazo.size(); i++) {
        int j = rand() % mazo.size();  // Genera un índice aleatorio
        swap(mazo[i], mazo[j]);       // Intercambia las cartas en el mazo
        swap(palos[i], palos[j]);     // Intercambia los palos de las cartas
    }
}

// Función para calcular el valor de la mano de un jugador
int calcularValorMano(const vector<int>& mano) {
    int valor = 0;
    int ases = 0;  // Para contar los Ases (que pueden valer 1 o 11)

    // Recorre todas las cartas de la mano y suma sus valores
    for (int carta : mano) {
        if (carta == 1) {  // Si la carta es un As
            ases++;
            valor += 11;  // Se suma como 11 inicialmente
        } else if (carta > 10) {  // Las cartas J, Q, K valen 10
            valor += 10;
        } else {
            valor += carta;  // Las cartas numéricas tienen su valor
        }
    }

    // Si el valor total es mayor que 21 y hay Ases, los Ases se cambian a 1
    while (valor > 21 && ases > 0) {
        valor -= 10;  // Resta 10 por cada As para convertirlo de 11 a 1
        ases--;
    }

    return valor;
}

// Función para mostrar las cartas de la mano de un jugador
void mostrarMano(const vector<int>& mano, const vector<char>& palos, const string& nombreJugador) {
    cout << nombreJugador << " tiene las cartas: ";
    for (size_t i = 0; i < mano.size(); ++i) {
        cout << obtenerStringDeCarta(mano[i], palos[i]) << " ";  // Muestra la carta con su símbolo de palo
    }
    cout << " - Valor total: " << calcularValorMano(mano) << endl;  // Muestra el valor total de la mano
}

// Función para repartir una carta al jugador
void repartirCarta(vector<int>& mazo, vector<char>& palos, vector<int>& mano) {
    mano.push_back(mazo.back());  // Agrega la última carta del mazo a la mano del jugador
    palos.push_back(palos.back());  // Agrega el palo de la carta a la mano
    mazo.pop_back();  // Elimina la carta del mazo
    palos.pop_back();  // Elimina el palo del mazo
}

// Función para mostrar las instrucciones del juego
void mostrarInstrucciones() {
    cout << "\n=== INSTRUCCIONES DEL JUEGO ===" << endl;
    cout << "El Blackjack es un juego de cartas entre dos jugadores y un dealer." << endl;
    cout << "El objetivo del juego es tener un puntaje lo mas cercano posible a 21, sin pasarse." << endl;
    cout << "Cada carta tiene un valor numerico: las cartas numericas tienen su valor (2-10),"
         << " las figuras (J, Q, K) valen 10, y el As puede valer 1 o 11, segun convenga." << endl;
    cout << "Los jugadores reciben dos cartas y pueden pedir mas cartas ('hit') o quedarse ('stand')."
         << " El dealer juega despues de que ambos jugadores terminen su turno." << endl;
    cout << "Si un jugador supera 21, pierde automaticamente. Si el dealer se pasa de 21," 
         << " los jugadores ganan." << endl;
    cout << " Buena suerte y diviertete!!!\n" << endl;
}

// Función que maneja el flujo del juego de Blackjack entre dos jugadores
void jugarBlackjack(const string& nombreJugador1, const string& nombreJugador2, Resultados& resultadosJugador1, Resultados& resultadosJugador2) {
    vector<int> mazo;     // Contenedor para las cartas del mazo
    vector<char> palos;   // Contenedor para los palos de las cartas
    vector<int> manoJugador1;  // Manos de los jugadores
    vector<int> manoJugador2;
    vector<int> manoDealer;    // Mano del dealer

    char todosLosPalos[] = {'H', 'D', 'C', 'S'};  // Los 4 palos (Corazones, Diamantes, Tréboles, Picas)
    for (int i = 0; i < 4; i++) {  // Llena el mazo con las cartas y sus palos
        for (int j = 1; j <= 13; j++) {  // Cada palo tiene 13 cartas
            mazo.push_back(j > 10 ? 10 : j);  // Las cartas de figura (J, Q, K) valen 10
            palos.push_back(todosLosPalos[i]);  // Asigna el palo correspondiente
        }
    }

    barajarMazo(mazo, palos);  // Baraja el mazo antes de repartir

    // Reparte las cartas iniciales
    repartirCarta(mazo, palos, manoJugador1);
    repartirCarta(mazo, palos, manoJugador1);
    repartirCarta(mazo, palos, manoJugador2);
    repartirCarta(mazo, palos, manoJugador2);
    repartirCarta(mazo, palos, manoDealer);
    repartirCarta(mazo, palos, manoDealer);

    mostrarMano(manoJugador1, palos, nombreJugador1);  // Muestra la mano del jugador 1
    char eleccion;
    // Jugador 1 pide cartas hasta que se pase o decida plantarse
    while (calcularValorMano(manoJugador1) < 21) {
        cout << nombreJugador1 << ", quieres pedir otra carta? (s/n)? ";
        cin >> eleccion;

        if (eleccion == 's' || eleccion == 'S') {
            repartirCarta(mazo, palos, manoJugador1);
            mostrarMano(manoJugador1, palos, nombreJugador1);

            if (calcularValorMano(manoJugador1) > 21) {
                cout << nombreJugador1 << ", te pasaste de 21. Perdiste!!!" << endl;
                resultadosJugador1.perdidos++; 
                return;
            }
        } else {
            break; 
        }
    }

    mostrarMano(manoJugador2, palos, nombreJugador2);  // Muestra la mano del jugador 2
    while (calcularValorMano(manoJugador2) < 21) {
        cout << nombreJugador2 << ", quieres pedir otra carta? (s/n)? ";
        cin >> eleccion;

        if (eleccion == 's' || eleccion == 'S') {
            repartirCarta(mazo, palos, manoJugador2);
            mostrarMano(manoJugador2, palos, nombreJugador2);

            if (calcularValorMano(manoJugador2) > 21) {
                cout << nombreJugador2 << ", te pasaste de 21. Perdiste!!!" << endl;
                resultadosJugador2.perdidos++;  
                return;
            }
        } else {
            break; 
        }
    }

    mostrarMano(manoDealer, palos, "Dealer");  // Muestra la mano del dealer
    while (calcularValorMano(manoDealer) < 17) {  // El dealer pide cartas hasta que su valor sea 17 o más
        cout << "Dealer pide otra carta." << endl;
        repartirCarta(mazo, palos, manoDealer);
        mostrarMano(manoDealer, palos, "Dealer");
    }

    int valorJugador1 = calcularValorMano(manoJugador1);
    int valorJugador2 = calcularValorMano(manoJugador2);
    int valorDealer = calcularValorMano(manoDealer);

    // Determina el ganador comparando las manos
    if (valorDealer > 21) {  // Si el dealer se pasa de 21, los jugadores ganan
        cout << "El dealer se paso de 21. Los jugadores que no se pasaron ganan." << endl;
        if (valorJugador1 <= 21 && valorJugador2 <= 21) {
            if (valorJugador1 > valorJugador2) {
                cout << nombreJugador1 << " gana!!!" << endl;
                resultadosJugador1.ganados++;
                resultadosJugador2.perdidos++;
            } else if (valorJugador2 > valorJugador1) {
                cout << nombreJugador2 << " gana!!!" << endl;
                resultadosJugador2.ganados++;
                resultadosJugador1.perdidos++;
            } else {
                cout << "Empate entre los jugadores!!!" << endl;
                resultadosJugador1.empatados++;
                resultadosJugador2.empatados++;
            }
        } else if (valorJugador1 <= 21) {
            cout << nombreJugador1 << " gana!!!" << endl;
            resultadosJugador1.ganados++;
            resultadosJugador2.perdidos++;
        } else {
            cout << nombreJugador2 << " gana!!!" << endl;
            resultadosJugador2.ganados++;
            resultadosJugador1.perdidos++;
        }
    } else {
        // Si el dealer no se pasa de 21, se comparan las manos de los jugadores
        if (valorJugador1 > 21) {
            cout << nombreJugador1 << " se paso de 21. Dealer gana." << endl;
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
            cout << nombreJugador2 << " se paso de 21. Dealer gana." << endl;
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

// Función principal donde se controla el flujo del juego
int main() {
    string nombreJugador1, nombreJugador2;
    Resultados resultadosJugador1, resultadosJugador2;

    // Recibe los nombres de los jugadores
    cout << "Introduce el nombre del Jugador 1: ";
    getline(cin, nombreJugador1);
    cout << "Introduce el nombre del Jugador 2: ";
    getline(cin, nombreJugador2);

    int opcion;
    do {
        // Muestra el menú principal
        cout << "\n   ==MENU==\n1. Jugar\n2. Ver Instrucciones\n3. Ver Resultados\n4. Salir\n";
        cout << "Selecciona una opcion: ";
        cin >> opcion;
        cin.ignore(); // Para ignorar el salto de línea después de leer el número

        // Ejecuta según la opción seleccionada
        switch (opcion) {
            case 1:
                jugarBlackjack(nombreJugador1, nombreJugador2, resultadosJugador1, resultadosJugador2);
                break;
            case 2:
                mostrarInstrucciones();
                break;
            case 3:
                // Muestra los resultados acumulados de cada jugador
                cout << "\nRESULTADOS:\n";
                cout << nombreJugador1 << " - Ganados: " << resultadosJugador1.ganados 
                     << ", Perdidos: " << resultadosJugador1.perdidos 
                     << ", Empatados: " << resultadosJugador1.empatados << endl;
                cout << nombreJugador2 << " - Ganados: " << resultadosJugador2.ganados 
                     << ", Perdidos: " << resultadosJugador2.perdidos 
                     << ", Empatados: " << resultadosJugador2.empatados << endl;
                break;
            case 4:
                cout << "Hasta luego!!!" << endl;  // Salida del juego
                break;
            default:
                cout << "Opcion invalida. Intenta nuevamente." << endl;
        }
    } while (opcion != 4);

    return 0;  // Fin del programa
}