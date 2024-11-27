#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <set>
#include <map>
#include <limits>
using namespace std;


const int NUM_FILAS = 5;
const int NUM_COLUMNAS = 5;
string nombreJugador1, nombreJugador2;

// Función para generar un numero aleatorio unico en un rango especifico
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
    cout << setw(10) << "  Carta de " << nombreJugador1 << setw(1) << "          Carta de " << nombreJugador2 << "\n";
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

// Función para manejar el marcado del numero por parte del jugador
bool seleccionarPosicion(int carta[NUM_FILAS][NUM_COLUMNAS], int numero, const string& nombreJugador) {
    int fila, col, intentos = 0;
    while (intentos < 3) {
        cout << nombreJugador << ", en que posicion (fila, columna) esta el numero " << numero << "? (FILAS Y COLUMNAS EMPIEZAN EN 0 Y TERMINAN EN 4)\n";
        cout << "Fila: ";
        cin >> fila;
        cout << "Columna: ";
        cin >> col;

        if (cin.fail() || fila < 0 || fila >= NUM_FILAS || col < 0 || col >= NUM_COLUMNAS) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Intenta nuevamente.\n";
        } else if (carta[fila][col] == numero) {
            carta[fila][col] = -1;
            return true;
        } else {
            cout << "La posicion seleccionada no contiene el numero " << numero << ".\n";
        }
        ++intentos;
    }
    cout << "Se agotaron los intentos. Pierdes este turno.\n";
    return false;
}

// Función para manejar el turno del jugador
bool turnoJugador(int carta[NUM_FILAS][NUM_COLUMNAS], int numero, const string& nombreJugador) {
    char respuesta;
    cout << nombreJugador << ", tienes el numero " << numero << " en tu carta? (s/n): ";
    cin >> respuesta;

    if (respuesta == 's' || respuesta == 'S') {
        return seleccionarPosicion(carta, numero, nombreJugador);
    } else if (respuesta == 'n' || respuesta == 'N') {
        cout << "Turno pasado.\n";
    } else {
        cout << "Respuesta no valida. Intenta nuevamente.\n";
        return turnoJugador(carta, numero, nombreJugador);
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
        cout << "* 2. Como jugar?   * \n";
        cout << "* 3. Ranking        * \n";
        cout << "* 4. Salir          * \n";
        cout << "* * * * * * * * * * * \n";
        cout << "Opcion: ";
        cin >> option;

        if (cin.fail() || option < 1 || option > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Opcion invalida. Por favor, elige una opcion valida.\n";
        }
    } while (option < 1 || option > 3);
    return option;
}

// Función para mostrar las reglas
void mostrarReglas() {
    cout << "                                        Reglas \n";
    cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n";
    cout << "* 1. Se te asignara una carta.                                                                                              * \n";
    cout << "* 2. Revisa los numeros de tu carta.                                                                                        * \n";
    cout << "* 3. Se generara un numero y se te mostrara.                                                                                * \n";
    cout << "* 4. Verifica si tienes el numero o no.                                                                                     * \n";
    cout << "* 5. Si lo tienes tendras que seleccionar en la fila y columna en la que se encuentra y se marcara una 'x' en la posicion.  * \n";
    cout << "* 6. Ten en cuenta que las filas y columnas inician en 0 y finalizan en 4.                                                  * \n";
    cout << "*    Es decir si quieres ubicar el numero en la primera fila y tercera columna deberas introducir '0' y '2'.                * \n";
    cout << "* 7. El primer jugador en tener 5 'x' seguidas en filas, columnas o en diagonal gana.                                       * \n";
    cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
}
// Leer ranking desde archivo
map<string, int> leerRanking(const string& archivo) {
    map<string, int> ranking;
    ifstream file(archivo);
    if (file.is_open()) {
        string nombre;
        int victorias;
        while (file >> nombre >> victorias) {
            ranking[nombre] = victorias;
        }
        file.close();
    }
    return ranking;
}

// Guardar ranking en archivo
void guardarRanking(const string& archivo, const map<string, int>& ranking) {
    ofstream file(archivo);
    if (file.is_open()) {
        for (const auto& entry : ranking) {
            file << entry.first << " " << entry.second << "\n";
        }
        file.close();
    }
}

// Mostrar ranking
void mostrarRanking(const map<string, int>& ranking) {
    cout << "\nRanking de jugadores:\n";
    cout << setw(20) << left << "Jugador" << "Victorias\n";
    cout << string(30, '-') << "\n";
    for (const auto& entry : ranking) {
        cout << setw(20) << left << entry.first << entry.second << "\n";
    }
    cout << string(30, '-') << "\n";
}

// Función principal del juego (modificada para incorporar el ranking)
// Función principal del juego (modificada para no mostrar el ranking)
void jugar(const string& archivoRanking) {
    // Leer ranking actual desde el archivo
    map<string, int> ranking = leerRanking(archivoRanking);

    cout << "Ingrese el nombre del Jugador 1: ";
    cin.ignore();
    getline(cin, nombreJugador1);

    cout << "Ingrese el nombre del Jugador 2: ";
    getline(cin, nombreJugador2);

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

        cout << "Turno de " << nombreJugador1 << "\n";
        if (turnoJugador(cartaJugador1, numero, nombreJugador1) && verificarGanador(cartaJugador1)) {
            cout << "\n¡" << nombreJugador1 << " ha ganado!\n";
            ranking[nombreJugador1]++;
            ganador = true;
            break;
        }

        cout << "Turno de " << nombreJugador2 << "\n";
        if (turnoJugador(cartaJugador2, numero, nombreJugador2) && verificarGanador(cartaJugador2)) {
            cout << "\n¡" << nombreJugador2 << " ha ganado!\n";
            ranking[nombreJugador2]++;
            ganador = true;
            break;
        }

        cout << "\nCartas actualizadas:\n";
        imprimirCartasLadoALado(cartaJugador1, cartaJugador2);
    }

    // Guardar el ranking actualizado en el archivo
    guardarRanking(archivoRanking, ranking);
}

// Main modificado para mostrar el ranking en el case 3
int main() {
    srand(time(0));
    const string archivoRanking = "ranking.txt"; // Nombre del archivo de ranking
    int opcion;

    do {
        opcion = bienvenida();
        switch (opcion) {
            case 1:
                jugar(archivoRanking);
                break;
            case 2:
                mostrarReglas();
                break;
            case 3:
                // Leer y mostrar el ranking actualizado
                mostrarRanking(leerRanking(archivoRanking));
                break;
        }
    } while (opcion != 4);

    cout << "¡Gracias por jugar! Hasta la próxima.\n";
    return 0;
}
