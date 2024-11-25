#include <iostream>  // Biblioteca para entrada y salida estándar (leer y mostrar datos en la consola)
#include <vector>    // Biblioteca que proporciona el contenedor 'vector', útil para almacenar listas dinámicas de datos
#include <ctime>     // Biblioteca para trabajar con el tiempo, se usa aquí para generar números aleatorios basados en el reloj
#include <cstdlib>   // Biblioteca para funciones generales, como la generación de números aleatorios

using namespace std; // Usamos el espacio de nombres 'std' para simplificar la escritura del código

// Variables globales para llevar la cuenta de los resultados (ganados, perdidos, empatados)
int ganados = 0;
int perdidos = 0;
int empatados = 0;

// Función que devuelve la representación en texto de una carta y su palo
string obtenerStringDeCarta(int carta, char palo) {
    string nombreCarta;

    // Se asigna el nombre correcto a las cartas especiales (As, Jota, Reina, Rey)
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

    // Se asigna el símbolo del palo basado en el parámetro 'palo'
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

    // Devuelve la carta como un string en el formato adecuado
    return nombreCarta + simboloPalo;
}

// Función para barajar el mazo de cartas
void barajarMazo(vector<int>& mazo, vector<char>& palos) {
    srand(time(0));  // Usa el tiempo actual para generar una semilla aleatoria para los números
    // Baraja el mazo de cartas y los palos (sincronizarlos para que cada carta mantenga su palo)
    for (int i = 0; i < mazo.size(); i++) {
        int j = rand() % mazo.size();  // Genera un índice aleatorio
        swap(mazo[i], mazo[j]);       // Intercambia las cartas en el mazo
        swap(palos[i], palos[j]);     // Intercambia los palos correspondientes
    }
}

// Función para calcular el valor total de una mano de cartas
int calcularValorMano(const vector<int>& mano) {
    int valor = 0; // Variable para almacenar el valor total de la mano
    int ases = 0;  // Contador para los Ases, ya que tienen un valor especial (1 o 11)

    // Itera sobre las cartas en la mano
    for (int carta : mano) {
        if (carta == 1) {
            ases++;
            valor += 11;  // Inicialmente el As se cuenta como 11
        } else if (carta > 10) {
            valor += 10;  // Las cartas de figura (J, Q, K) valen 10
        } else {
            valor += carta;  // Las cartas numéricas suman su valor
        }
    }

    // Si el valor de la mano es mayor a 21, convertimos los Ases de 11 a 1
    while (valor > 21 && ases > 0) {
        valor -= 10;  // Restamos 10 para considerar el As como 1
        ases--;  // Reducimos el contador de Ases
    }

    return valor;  // Devuelve el valor total de la mano
}

// Función para mostrar las cartas de un jugador (mano) en la consola
void mostrarMano(const vector<int>& mano, const vector<char>& palos, const string& nombreJugador) {
    cout << nombreJugador << " tiene las cartas: ";
    // Itera sobre las cartas de la mano y las muestra con su palo
    for (size_t i = 0; i < mano.size(); ++i) {
        cout << obtenerStringDeCarta(mano[i], palos[i]) << " ";  // Imprime la carta
    }
    // Muestra el valor total de la mano
    cout << " - Valor total: " << calcularValorMano(mano) << endl;
}

// Función para repartir una carta a un jugador
void repartirCarta(vector<int>& mazo, vector<char>& palos, vector<int>& mano) {
    // Añade la última carta del mazo a la mano del jugador y luego la elimina del mazo
    mano.push_back(mazo.back());
    palos.push_back(palos.back());
    mazo.pop_back();
    palos.pop_back();
}

// Función para mostrar las instrucciones del juego
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

// Función principal del juego donde se juega una partida de Blackjack entre 2 jugadores y un dealer
void jugarBlackjack() {
    vector<int> mazo;    // Vector que representa el mazo de cartas (numeradas del 1 al 13, las figuras como 10)
    vector<char> palos;  // Vector que almacena los palos correspondientes a cada carta (H, D, C, S)
    vector<int> manoJugador1;  // Mano del jugador 1
    vector<int> manoJugador2;  // Mano del jugador 2
    vector<int> manoDealer;    // Mano del dealer

    // Llenar el mazo con 4 palos (Corazones, Diamantes, Tréboles, Picas) y 13 cartas por palo
    char todosLosPalos[] = {'H', 'D', 'C', 'S'};
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j <= 13; j++) {
            mazo.push_back(j > 10 ? 10 : j);  // Las figuras (J, Q, K) se consideran como 10
            palos.push_back(todosLosPalos[i]);  // Asigna el palo correspondiente
        }
    }

    barajarMazo(mazo, palos);  // Baraja el mazo de cartas

    // Repartir dos cartas a cada jugador y al dealer
    repartirCarta(mazo, palos, manoJugador1);
    repartirCarta(mazo, palos, manoJugador1);
    repartirCarta(mazo, palos, manoJugador2);
    repartirCarta(mazo, palos, manoJugador2);
    repartirCarta(mazo, palos, manoDealer);
    repartirCarta(mazo, palos, manoDealer);

    // Turno del Jugador 1
    mostrarMano(manoJugador1, palos, "Jugador 1");
    char eleccion;
    while (calcularValorMano(manoJugador1) < 21) {  // Mientras el valor total no supere 21
        cout << "Jugador 1, ¿quieres pedir otra carta (s/n)? ";
        cin >> eleccion;  // Solicita la decisión del jugador

        if (eleccion == 's' || eleccion == 'S') {  // Si el jugador quiere una carta más
            repartirCarta(mazo, palos, manoJugador1);
            mostrarMano(manoJugador1, palos, "Jugador 1");

            if (calcularValorMano(manoJugador1) > 21) {  // Si el jugador se pasa de 21
                cout << "Jugador 1, te pasaste de 21. ¡Perdiste!" << endl;
                perdidos++;  // Se cuenta como una derrota para el jugador
                return;
            }
        } else {
            break;  // El jugador decide quedarse con las cartas que tiene
        }
    }

    // Turno del Jugador 2
    mostrarMano(manoJugador2, palos, "Jugador 2");
    while (calcularValorMano(manoJugador2) < 21) {  // Lo mismo para el Jugador 2
        cout << "Jugador 2, ¿quieres pedir otra carta (s/n)? ";
        cin >> eleccion;

        if (eleccion == 's' || eleccion == 'S') {
            repartirCarta(mazo, palos, manoJugador2);
            mostrarMano(manoJugador2, palos, "Jugador 2");

            if (calcularValorMano(manoJugador2) > 21) {
                cout << "Jugador 2, te pasaste de 21. ¡Perdiste!" << endl;
                perdidos++;  // Derrota para el jugador
                return;
            }
        } else {
            break;  // El jugador decide no pedir más cartas
        }
    }

    // Turno del Dealer
    cout << "\nEl turno del Dealer." << endl;
    mostrarMano(manoDealer, palos, "Dealer (con una carta oculta)");

    // El dealer debe pedir cartas hasta llegar a 17 o más
    while (calcularValorMano(manoDealer) < 17) {
        cout << "El dealer pide una carta..." << endl;
        repartirCarta(mazo, palos, manoDealer);
        mostrarMano(manoDealer, palos, "Dealer");

        if (calcularValorMano(manoDealer) > 21) {  // Si el dealer se pasa de 21
            cout << "El dealer se pasó de 21." << endl;

            // Determinar el ganador comparando las manos
            int valorJugador1 = calcularValorMano(manoJugador1);
            int valorJugador2 = calcularValorMano(manoJugador2);

            if (valorJugador1 <= 21 && (valorJugador1 > valorJugador2 || valorJugador2 > 21)) {
                cout << "¡Jugador 1 gana!" << endl;
                ganados++;
            } else if (valorJugador2 <= 21 && (valorJugador2 > valorJugador1 || valorJugador1 > 21)) {
                cout << "¡Jugador 2 gana!" << endl;
                ganados++;
            }
            return;  // El juego termina aquí ya que el dealer ha perdido
        }
    }

    // Comparar las manos de los jugadores y del dealer para determinar el ganador
    int valorJugador1 = calcularValorMano(manoJugador1);
    int valorJugador2 = calcularValorMano(manoJugador2);
    int valorDealer = calcularValorMano(manoDealer);

    if (valorJugador1 > valorDealer && valorJugador1 <= 21) {
        cout << "¡Jugador 1 gana!" << endl;
        ganados++;
    } else if (valorJugador2 > valorDealer && valorJugador2 <= 21) {
        cout << "¡Jugador 2 gana!" << endl;
        ganados++;
    } else if (valorDealer > valorJugador1 && valorDealer > valorJugador2) {
        cout << "El dealer gana." << endl;
        perdidos++;  // Si el dealer gana
    } else {
        cout << "Es un empate." << endl;
        empatados++;  // Si es empate
    }
}

// Función principal del programa
int main() {
    cout << "¡Bienvenido al juego de Blackjack!" << endl;

    mostrarInstrucciones();  // Muestra las instrucciones del juego

    char jugarOtraVez;
    cout << "¿Quieres jugar ahora? (s/n): ";
    cin >> jugarOtraVez;

    if (jugarOtraVez == 's' || jugarOtraVez == 'S') {
        do {
            jugarBlackjack();  // Llama a la función que gestiona el juego
            cout << "¿Quieres jugar otra vez (s/n)? ";
            cin >> jugarOtraVez;
        } while (jugarOtraVez == 's' || jugarOtraVez == 'S');  // Repite el juego si el jugador lo desea
    }

    // Al finalizar el juego, muestra las estadísticas
    cout << "\nEstadísticas del juego:" << endl;
    cout << "Ganados: " << ganados << endl;
    cout << "Perdidos: " << perdidos << endl;
    cout << "Empatados: " << empatados << endl;

    cout << "Gracias por jugar. ¡Hasta la próxima!" << endl;
    return 0;
}
