#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <set>
using namespace std;
const int NUM_FILAS = 5;
const int NUM_COLUMNAS = 5;
string HEADER = " B   I   N   G   O ";

int bienvenida (int option){
    cout << "Bienvenido a BINGO \n";
    cout << "* * * * * * * * * * * \n";
    cout << "* 1. Jugar          * \n";
    cout << "* 2. ¿Como jugar?  * \n";
    cout << "* 3. Ranking        * \n";
    cout << "* 4. Salir          * \n";
    cout << "* * * * * * * * * * * \n";
    cout << "Opcion: ";
    cin >> option;

    return option;
}


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
    cout << "Carta Jugador 1" << ::setw(HEADER.size() + 10) << "Carta Jugador 2" << ::endl;
    cout << HEADER << ::setw(10) << " " << HEADER << endl;

    for (int fila = 0; fila < NUM_FILAS; ++fila) {
        for (int col = 0; col < NUM_COLUMNAS; ++col) {
            if (fila == 2 && col == 2) {
                cout << "  * "; // Espacio fijo para el centro
            } else if (carta1[fila][col] == -1) {
                cout << "  X "; // Espacio fijo para números marcados
            } else {
                cout << " " << setfill('0') << setw(2) << carta1[fila][col] << " "; // Número formateado
            }
        }

        cout << setw(5) << " "; // Separador entre cartas

        for (int col = 0; col < NUM_COLUMNAS; ++col) {
            if (fila == 2 && col == 2) {
                cout << "  * ";
            } else if (carta2[fila][col] == -1) {
                cout << "  X ";
            } else {
                cout << " " << setfill('0') << setw(2) << carta2[fila][col] << " ";
            }
        }
        cout << endl;
    }
}



// Función para marcar un número en la carta
bool marcarNumero(int carta[NUM_FILAS][NUM_COLUMNAS], int numero) {
    for (int fila = 0; fila < NUM_FILAS; ++fila) {
        for (int col = 0; col < NUM_COLUMNAS; ++col) {
            if (carta[fila][col] == numero) {
                carta[fila][col] = -1; // Marcar número con -1
                return true;
            }
        }
    }
    return false;
}

// Función para verificar si un jugador ha ganado (línea completa o carta completa)
bool verificarGanador(int carta[NUM_FILAS][NUM_COLUMNAS]) {
    // Verificar filas y columnas
    for (int i = 0; i < NUM_FILAS; ++i) {
        bool filaCompleta = true;
        bool columnaCompleta = true;
        for (int j = 0; j < NUM_COLUMNAS; ++j) {
            if (carta[i][j] != -1) filaCompleta = false;
            if (carta[j][i] != -1) columnaCompleta = false;
        }
        if (filaCompleta || columnaCompleta) return true;
    }
    // Verificar diagonales
    bool diagonal1 = true, diagonal2 = true;
    for (int i = 0; i < NUM_FILAS; ++i) {
        if (carta[i][i] != -1) diagonal1 = false;
        if (carta[i][NUM_FILAS - i - 1] != -1) diagonal2 = false;
    }
    return diagonal1 || diagonal2;
}
int menu (int option){
    bool ganador = false;
    set<int> numerosLlamados;
    switch (option)
    {
    case 1:
    srand(time(0)); // Semilla para números aleatorios
    int cartaJugador1[NUM_FILAS][NUM_COLUMNAS];
    int cartaJugador2[NUM_FILAS][NUM_COLUMNAS];
    
    // Generar cartas para cada jugador
    generarCartaBingo(cartaJugador1);
    generarCartaBingo(cartaJugador2);

    // Set para almacenar los números llamados

    while (!ganador) {
        int numero;
        do {
            numero = 1 + rand() % 75;
        } while (numerosLlamados.count(numero) > 0);

        numerosLlamados.insert(numero);
        cout << "\nNúmero sacado: " << numero << "\n";

        // Marcar el número en ambas cartas
        bool marcado1 = marcarNumero(cartaJugador1, numero);
        bool marcado2 = marcarNumero(cartaJugador2, numero);

        // Imprimir cartas actualizadas
        imprimirCartasLadoALado(cartaJugador1, cartaJugador2);

        // Verificar si alguno de los jugadores ha ganado
        if (marcado1 && verificarGanador(cartaJugador1)) {
            cout << "\n¡Jugador 1 ha ganado!" << endl;
            ganador = true;
        } else if (marcado2 && verificarGanador(cartaJugador2)) {
            cout << "\n¡Jugador 2 ha ganado!" << endl;
            ganador = true;
        }

        if (!ganador) {
            cout << "\nPresiona Enter para continuar al siguiente número...\n";
            cin.ignore();
        }
    }
        break;
    case 2:

    cout << "                                        Reglas \n";
    cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n";
    cout << "* 1. Se te asignara una carta.                                                        * \n";
    cout << "* 2. Revisa los numeros de tu carta.                                                  * \n";
    cout << "* 3. Cada vez que presiones enter un numero aleatorio aparecera.                      * \n";
    cout << "* 4. Si tienes ese numero en tu carta una 'x' aparecera en su lugar.                  * \n";
    cout << "* 5. El primer jugador en tener 5 'x' seguidas en filas, columnas o en diagonal gana. * \n";
    cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n";    
        break;
    case 3:
    cout << "";
        break;

    case 4:
    cout << "Salir \n";
        break;
    default:
    cout << "Opcion invalida \n";
        break;
    }
    return option;

}


int main() {

    int option = bienvenida(option);

    menu(option);
    
    return 0;
}