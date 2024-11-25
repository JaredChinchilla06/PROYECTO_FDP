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

// Función de bienvenida
int bienvenida(int option) {
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
    // El encabezado será simétrico para las dos cartas
    const int ESPACIO_COLUMNA = 5; // Espacio entre las columnas
    cout << setw(ESPACIO_COLUMNA * 2) << "Carta Jugador 1" 
         << setw(ESPACIO_COLUMNA * 2) << "            Carta Jugador 2 \n" ;
    
    // Imprimir el encabezado
    cout << "  B   I   N   G   O    " 
         << "  B   I   N   G   O  \n";

    // Imprimir las filas de las cartas
    for (int fila = 0; fila < NUM_FILAS; ++fila) {
        // Imprimir la carta del Jugador 1
        for (int col = 0; col < NUM_COLUMNAS; ++col) {
            if (fila == 2 && col == 2) {
                cout << "  * ";
            } else if (carta1[fila][col] == -1) {
                cout << "  X ";
            } else {
                cout << " " << setw(2) << carta1[fila][col] << " ";
            }
        }

        // Espacio entre las cartas
        cout << "    "; // Ajusta el espacio si es necesario

        // Imprimir la carta del Jugador 2
        for (int col = 0; col < NUM_COLUMNAS; ++col) {
            if (fila == 2 && col == 2) {
                cout << "  * ";
            } else if (carta2[fila][col] == -1) {
                cout << "  X ";
            } else {
                cout << " " << setw(2) << carta2[fila][col] << " ";
            }
        }

        cout << "\n";
    }
}


// Función para buscar y validar si el número existe en la carta
bool validarPosicion(int carta[NUM_FILAS][NUM_COLUMNAS], int fila, int col, int numero) {
    return carta[fila][col] == numero;
}

// Función para permitir al jugador seleccionar dónde está el número
bool seleccionarPosicion(int carta[NUM_FILAS][NUM_COLUMNAS], int numero, int jugador) {
    int fila, col;
    cout << "Jugador " << jugador << ", ¿en qué posición (fila, columna) está el número " << numero << "? (FILAS Y COLUMNAS INICIAN EN 0 Y LLEGAN HASTA 4 )\n";
    cout << "Fila: ";
    cin >> fila;
    cout << "Columna: ";
    cin >> col;

    // Validar posición
    if (fila >= 0 && fila < NUM_FILAS && col >= 0 && col < NUM_COLUMNAS) {
        if (validarPosicion(carta, fila, col, numero)) {
            carta[fila][col] = -1; // Marcar el número
            return true;
        } else {
            cout << "La posición seleccionada no contiene el número " << numero << ".\n";
        }
    } else {
        cout << "Posición inválida. Intenta nuevamente.\n";
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

bool preguntarYMarcar(int carta[NUM_FILAS][NUM_COLUMNAS], int numero, int jugador) {
    char respuesta;
    cout << "Jugador " << jugador << ", ¿tienes el número " << numero << " en tu carta? (s/n): ";
    cin >> respuesta;

    if (respuesta == 's' || respuesta == 'S') {
        bool marcado = false;
        int intentos = 0; // Contador de intentos
        while (!marcado && intentos < 3) {
            intentos++;
            cout << "Intento " << intentos << " de 3.\n";
            marcado = seleccionarPosicion(carta, numero, jugador);
            if (!marcado) {
                cout << "La posición seleccionada no es válida. Intenta nuevamente.\n";
            }
        }
        if (!marcado) {
            cout << "Se agotaron los intentos. Pierdes este turno.\n";
        }
        return marcado;
    } else if (respuesta == 'n' || respuesta == 'N') {
        cout << "Turno pasado.\n";
    } else {
        cout << "Respuesta no válida. Intenta nuevamente.\n";
        return preguntarYMarcar(carta, numero, jugador);
    }
    return false;
}


int menu(int option) {
    bool ganador = false;
    set<int> numerosLlamados;

    while (true) {
        switch (option) {
        case 1:
            srand(time(0)); // Semilla para números aleatorios
            int cartaJugador1[NUM_FILAS][NUM_COLUMNAS];
            int cartaJugador2[NUM_FILAS][NUM_COLUMNAS];

            // Generar cartas para cada jugador
            generarCartaBingo(cartaJugador1);
            generarCartaBingo(cartaJugador2);

            // Mostrar cartas iniciales
            cout << "\nCartas iniciales:\n";
            imprimirCartasLadoALado(cartaJugador1, cartaJugador2);

            while (!ganador) {
                // Generar un número aleatorio que no se haya llamado antes
                int numero;
                do {
                    numero = 1 + rand() % 75;
                } while (numerosLlamados.count(numero) > 0);

                numerosLlamados.insert(numero);

                // Mostrar el número sacado
                cout << "\nNúmero sacado: " << numero << "\n";

                // Turno del Jugador 1
                cout << "Turno del Jugador 1\n";
                bool marcado1 = preguntarYMarcar(cartaJugador1, numero, 1);

                // Verificar si Jugador 1 ha ganado
                if (marcado1 && verificarGanador(cartaJugador1)) {
                    cout << "\n¡Jugador 1 ha ganado!\n";
                    ganador = true;
                    break;
                }

                // Turno del Jugador 2
                cout << "Turno del Jugador 2\n";
                bool marcado2 = preguntarYMarcar(cartaJugador2, numero, 2);

                // Verificar si Jugador 2 ha ganado
                if (marcado2 && verificarGanador(cartaJugador2)) {
                    cout << "\n¡Jugador 2 ha ganado!\n";
                    ganador = true;
                    break;
                }

                // Mostrar cartas actualizadas
                cout << "\nCartas actualizadas:\n";
                imprimirCartasLadoALado(cartaJugador1, cartaJugador2);

                if (!ganador) {
                    cout << "\nPresiona Enter para continuar al siguiente número...\n";
                    cin.ignore();
                    cin.get();
                }
            }
            break;

        case 2:
            cout << "                                        Reglas \n";
            cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n";
            cout << "* 1. Se te asignará una carta.                                                                                             * \n";
            cout << "* 2. Revisa los números de tu carta.                                                                                       * \n";
            cout << "* 3. Se generará un número y se te mostrará.                                                                             * \n";
            cout << "* 4. Verifica si tienes el número o no.                                                                                    * \n";
            cout << "* 5. Si lo tienes tendras que seleccionar en la fila y columna en la que se encuentra y se marcara una 'x' en la posicion.  * \n";
            cout << "* 6. Ten en cuenta que las filas y columnas inician en 0 y finalizan en 4.                                                  * \n";
            cout << "*    Es decir si quieres ubicar el numero en la primera fila y tercera columna deberas introducir '0' y '2'.                * \n";
            cout << "* 7. El primer jugador en tener 5 'x' seguidas en filas, columnas o en diagonal gana.                                       * \n";
            cout << "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n";
            break;

        case 3:
            cout << "Ranking aún no disponible.\n";
            break;

        case 4:
            cout << "Salir \n";
            return 0; // Sale del programa

        case 5:
            return option; // Regresar al menú principal

        default:
            cout << "Opción inválida \n";
            break;
        }

        // Después de cada acción, preguntar si el jugador desea regresar al menú
        cout << "\n¿Quieres regresar al menú principal? (5 para regresar o 4 para salir): ";
        cin >> option;
        if (option == 4) {
            cout << "Gracias por jugar. ¡Hasta luego!\n";
            break;  // Sale del ciclo
        }
    }
    return option;
}




int main() {
    int option = bienvenida(option);
    menu(option);
    return 0;
}
