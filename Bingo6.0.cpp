#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <set>
#include <limits>
using namespace std;

const int NUM_FILAS = 5;
const int NUM_COLUMNAS = 5;

// Función para generar un número aleatorio único en un rango específico
int generarNumero(int min, int max, set<int>& usados) {
    int num;
    do {
        num = min + rand() % (max - min + 1);
    } while (usados.count(num) > 0);
    usados.insert(num);
    return num;
}

// Función para generar una carta de bingo
void generarCartaBingo(int carta[NUM_FILAS][NUM_COLUMNAS]) {
    vector<pair<int, int>> rangos = {
        {1, 15}, {16, 30}, {31, 45}, {46, 60}, {61, 75}
    };

    for (int col = 0; col < NUM_COLUMNAS; ++col) {
        set<int> usados;
        for (int fila = 0; fila < NUM_FILAS; ++fila) {
            if (fila == 2 && col == 2) {
                carta[fila][col] = 0; // Espacio libre
            } else {
                carta[fila][col] = generarNumero(rangos[col].first, rangos[col].second, usados);
            }
        }
    }
}

// Función para imprimir dos cartas lado a lado
void imprimirCartasLadoALado(int carta1[NUM_FILAS][NUM_COLUMNAS], int carta2[NUM_FILAS][NUM_COLUMNAS]) {
    cout << setw(20) << "Carta Jugador 1" << setw(30) << "Carta Jugador 2" << "\n";
    cout << "  B   I   N   G   O    " << "  B   I   N   G   O\n";

    for (int fila = 0; fila < NUM_FILAS; ++fila) {
        for (int col = 0; col < NUM_COLUMNAS; ++col) {
            if (fila == 2 && col == 2) cout << "  * ";
            else if (carta1[fila][col] == -1) cout << "  X ";
            else cout << " " << setw(2) << carta1[fila][col] << " ";
        }
        cout << "    ";
        for (int col = 0; col < NUM_COLUMNAS; ++col) {
            if (fila == 2 && col == 2) cout << "  * ";
            else if (carta2[fila][col] == -1) cout << "  X ";
            else cout << " " << setw(2) << carta2[fila][col] << " ";
        }
        cout << "\n";
    }
}

// Función para verificar si un jugador ha ganado
bool verificarGanador(int carta[NUM_FILAS][NUM_COLUMNAS]) {
    for (int i = 0; i < NUM_FILAS; ++i) {
        bool filaCompleta = true, columnaCompleta = true;
        for (int j = 0; j < NUM_COLUMNAS; ++j) {
            if (carta[i][j] != -1) filaCompleta = false;
            if (carta[j][i] != -1) columnaCompleta = false;
        }
        if (filaCompleta || columnaCompleta) return true;
    }
    bool diagonal1 = true, diagonal2 = true;
    for (int i = 0; i < NUM_FILAS; ++i) {
        if (carta[i][i] != -1) diagonal1 = false;
        if (carta[i][NUM_FILAS - i - 1] != -1) diagonal2 = false;
    }
    return diagonal1 || diagonal2;
}

// Función para manejar el marcado del número por parte del jugador
bool seleccionarPosicion(int carta[NUM_FILAS][NUM_COLUMNAS], int numero, int jugador) {
    int fila, col, intentos = 0;
    while (intentos < 3) {
        cout << "Jugador " << jugador << ", ¿en qué posición (fila, columna) está el número " << numero << "? (0-4)\n";
        cout << "Fila: ";
        cin >> fila;
        cout << "Columna: ";
        cin >> col;

        if (cin.fail() || fila < 0 || fila >= NUM_FILAS || col < 0 || col >= NUM_COLUMNAS) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada inválida. Intenta nuevamente.\n";
        } else if (carta[fila][col] == numero) {
            carta[fila][col] = -1;
            return true;
        } else {
            cout << "La posición seleccionada no contiene el número " << numero << ".\n";
        }
        ++intentos;
    }
    cout << "Se agotaron los intentos. Pierdes este turno.\n";
    return false;
}

// Función para manejar el turno del jugador
bool turnoJugador(int carta[NUM_FILAS][NUM_COLUMNAS], int numero, int jugador) {
    char respuesta;
    cout << "Jugador " << jugador << ", ¿tienes el número " << numero << " en tu carta? (s/n): ";
    cin >> respuesta;

    if (respuesta == 's' || respuesta == 'S') {
        return seleccionarPosicion(carta, numero, jugador);
    } else if (respuesta == 'n' || respuesta == 'N') {
        cout << "Turno pasado.\n";
    } else {
        cout << "Respuesta no válida. Intenta nuevamente.\n";
        return turnoJugador(carta, numero, jugador);
    }
    return false;
}

// Función para la bienvenida
int bienvenida() {
    int option;
    do {
    cout << " Bienvenido a BINGO \n";
    cout << "* * * * * * * * * * * \n";
    cout << "* 1. Jugar          * \n";
    cout << "* 2. ¿Como jugar?   * \n";
    cout << "* 3. Salir          * \n";
    cout << "* * * * * * * * * * * \n";
    cout << "Opcion: ";
    cin >> option;

        if (cin.fail() || option < 1 || option > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Opción inválida. Por favor, elige una opción válida.\n";
        }
    } while (option < 1 || option > 3);
    return option;
}

// Función para mostrar las reglas
void mostrarReglas() {
            cout << "                                        Reglas \n";
            cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n";
            cout << "* 1. Se te asignará una carta.                                                                                              * \n";
            cout << "* 2. Revisa los números de tu carta.                                                                                        * \n";
            cout << "* 3. Se generará un número y se te mostrará.                                                                                * \n";
            cout << "* 4. Verifica si tienes el número o no.                                                                                     * \n";
            cout << "* 5. Si lo tienes tendras que seleccionar en la fila y columna en la que se encuentra y se marcara una 'x' en la posicion.  * \n";
            cout << "* 6. Ten en cuenta que las filas y columnas inician en 0 y finalizan en 4.                                                  * \n";
            cout << "*    Es decir si quieres ubicar el numero en la primera fila y tercera columna deberas introducir '0' y '2'.                * \n";
            cout << "* 7. El primer jugador en tener 5 'x' seguidas en filas, columnas o en diagonal gana.                                       * \n";
            cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
}

// Función principal del juego
void jugar() {
    int cartaJugador1[NUM_FILAS][NUM_COLUMNAS];
    int cartaJugador2[NUM_FILAS][NUM_COLUMNAS];
    set<int> numerosLlamados;
    bool ganador = false;

    generarCartaBingo(cartaJugador1);
    generarCartaBingo(cartaJugador2);

    cout << "\nCartas iniciales:\n";
    imprimirCartasLadoALado(cartaJugador1, cartaJugador2);

    while (!ganador) {
        int numero = generarNumero(1, 75, numerosLlamados);
        cout << "\nNúmero sacado: " << numero << "\n";

        cout << "Turno del Jugador 1\n";
        if (turnoJugador(cartaJugador1, numero, 1) && verificarGanador(cartaJugador1)) {
            cout << "\n¡Jugador 1 ha ganado!\n";
            ganador = true;
            break;
        }

        cout << "Turno del Jugador 2\n";
        if (turnoJugador(cartaJugador2, numero, 2) && verificarGanador(cartaJugador2)) {
            cout << "\n¡Jugador 2 ha ganado!\n";
            ganador = true;
            break;
        }

        cout << "\nCartas actualizadas:\n";
        imprimirCartasLadoALado(cartaJugador1, cartaJugador2);
    }
}

int main() {
    int option;
    do {
        option = bienvenida();
        switch (option) {
        case 1:
            jugar();
            break;
        case 2:
            mostrarReglas();
            break;
        case 3:
            cout << "¡Gracias por jugar! Hasta pronto.\n";
            break;
        }
    } while (option != 3);
    return 0;
}
