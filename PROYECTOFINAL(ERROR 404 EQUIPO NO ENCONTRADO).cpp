#include <iostream>  // entrada y salida de datos
#include <vector>    // almacenar datos 
#include <ctime>     // necesario para usar funcion rand 
#include <cstdlib>   // para generar numeros aleatorios
#include <string>    // posibilidad de trabajar con cadenas de texto
#include <fstream>   // manejo de archivos
#include <algorithm> // permite usar funciones como swap() para intercambiar valores
#include <conio.h>   // validacion para el uso de teclas             
#include <iomanip>   // permite alinear texto, anchura de columnas, etc
#include <set>       // almacenar elementos unicos en orden 
#include <limits>    // validacion de datos ingresados
#include <windows.h> // funciones para la consola de windows
#include <stdlib.h>  // 
#include <time.h>
#include <map>       // almacenar datos en el ranking de bingo
using namespace std;

HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);
COORD PosicionCursor;

//INICIO BUHITOS
const int ANCHO_PANTALLA = 90; //Ancho total de la pantalla//
const int ALTO_PANTALLA = 26; //Alto total de la pantalla//
const int ANCHO_JUEGO = 70;   //Ancho de la sección donde se juega//
const int ANCHO_OBJETO = 5;   //Ancho del búho u otros objetos//
const int ALTO_OBJETO = 4;    //Alto del búho u otros objetos//
const int TAMANIO_HUECO = 7;  //Tamaño del espacio en las tuberías//

//Variables que hacen uso de arreglos para la posicion de las tuberias//
int posicionTuberias[3];
int posicionEspacio[3];
int banderaTuberias[3];

int ultimoPuntajeVelocidad = 0;
int puntajeMaximo = 0;
int posicionBuho = 6;  // Posición vertical inicial del búho
int puntaje = 0; // Puntaje del jugador

void moverCursor(int x, int y) {
    PosicionCursor.X = x;
    PosicionCursor.Y = y;
    SetConsoleCursorPosition(consola, PosicionCursor);
}

void configurarCursor(bool visible, DWORD tamano) {
    CONSOLE_CURSOR_INFO informacionCursor;
    informacionCursor.bVisible = visible;
    informacionCursor.dwSize = tamano;
    SetConsoleCursorInfo(consola, &informacionCursor);
}

//Se hace uso de una funcion para dibujar lo que es el marco, haciendo uso de matrices//
void dibujoMarco() {
    for (int i = 0; i < ANCHO_PANTALLA; i++) {
        moverCursor(i, 0);
        cout << '*';
        moverCursor(i, ALTO_PANTALLA);
        cout << '*';
    }
    for (int i = 0; i < ALTO_PANTALLA; i++) {
        moverCursor(0, i); 
        cout << '*';
        moverCursor(ANCHO_PANTALLA - 1, i); 
        cout << '*';
    }
    for (int i = 0; i < ALTO_PANTALLA; i++) {
        moverCursor(ANCHO_JUEGO, i); cout << '*';
    }
}

//Se utiliza una funcion para dibujar el buho//
void dibujarBuho(int x, int y) {
    moverCursor(x, y);     cout << "  ___ ";
    moverCursor(x, y + 1); cout << " {o,o}";
    moverCursor(x, y + 2); cout << " /)  )";
    moverCursor(x, y + 3); cout << "  \" \" ";
}

//Se utiliza otra funcion seguido de dibujar el buho para poder borrar el buho//
void borrarBuho(int x, int y) {
    moverCursor(x, y);     cout << "     ";
    moverCursor(x, y + 1); cout << "     ";
    moverCursor(x, y + 2); cout << "     ";
    moverCursor(x, y + 3); cout << "     ";
}

//Se usa una funcion con una veriable de tipo entera para detectar si el buho ha cochado con una tuberia//
int detectarColision() {
    if (posicionTuberias[0] >= 61) {
        if (posicionBuho < posicionEspacio[0] || posicionBuho > posicionEspacio[0] + TAMANIO_HUECO) {
            return 1;  // Hay colisión
        }
    }
    return 0;  // No hay colisión
}

//Se hace en una funcion un marco que indica el Fin del juego//
void finDelJuego() {
    system("cls");
    cout << "------------------------------" << endl;
    cout << "-------- Fin del Juego -------" << endl;
    cout << "------------------------------" << endl;
    cout << "Puntaje final: " << puntaje << endl;
    cout << "Puntaje más alto: " << puntajeMaximo << endl; // Mostrar el máximo
    
    if (puntaje > puntajeMaximo) {
        puntajeMaximo = puntaje;
        cout << "¡Felicidades! ¡Nuevo récord!" << endl;
    }
    cout << "Presiona cualquier tecla para volver al menú.";
    getch();
}

//Se hace uso de una funcion para ver el puntaje del jugador//
void actualizarPuntaje() {
    moverCursor(ANCHO_JUEGO + 7, 5);
    cout << "Puntaje: " << puntaje;

    moverCursor(ANCHO_JUEGO + 7, 6);
    cout << "Maximo: " << puntajeMaximo << endl; // Mostrar el puntaje más alto
}

//Se empieza a trabajar los tubos o tuberias que seran los obstavulos que tendra el juego, para ello se utilizan 3 funciones//
void generarTuberia(int indice) {
    posicionEspacio[indice] = 3 + rand() % 14;
}

void dibujarTuberia(int indice) {
    if (banderaTuberias[indice]) {
        for (int i = 0; i < posicionEspacio[indice]; i++) {
            moverCursor(ANCHO_JUEGO - posicionTuberias[indice], i + 1); cout << "***";
        }
        for (int i = posicionEspacio[indice] + TAMANIO_HUECO; i < ALTO_PANTALLA - 1; i++) {
            moverCursor(ANCHO_JUEGO - posicionTuberias[indice], i + 1); cout << "***";
        }
    }
}

void borrarTuberia(int indice) {
    if (banderaTuberias[indice]) {
        for (int i = 0; i < posicionEspacio[indice]; i++) {
            moverCursor(ANCHO_JUEGO - posicionTuberias[indice], i + 1); cout << "   ";
        }
        for (int i = posicionEspacio[indice] + TAMANIO_HUECO; i < ALTO_PANTALLA - 1; i++) {
            moverCursor(ANCHO_JUEGO - posicionTuberias[indice], i + 1); cout << "   ";
        }
    }
}

//Luego se empieza a trabajar en la funcion donde esta toda la logica del juego//
void jugarB() {

    //Se declaran variables para delimitar, puntaje, posicion del buho, tuberias, etc...//
    posicionBuho = 6;
    puntaje = 0;
    banderaTuberias[0] = 1;
    banderaTuberias[1] = 0;
    posicionTuberias[0] = 4;
    
    //Se limpia la consola con la palabra reservada "cls", tambien se llaman las funciones que dibujan el marco, la que genera las tuberias y la que actualiza el puntaje//
    system("cls");
    dibujoMarco();
    generarTuberia(0);
    actualizarPuntaje();
    
    //Se utiliza un ciclo While para verificar que sea verdad para empezar el juego//
    while (true) {
        if (kbhit()) {
            char ch = getch();
            if (ch == 32 && posicionBuho > 3) {
                posicionBuho -= 3;
            } if (ch == 27) 
            
            break;
        }
        
        dibujarBuho(2, posicionBuho);
        dibujarTuberia(0);
        if (detectarColision()) {
            finDelJuego();
            return;
        }
        Sleep(100);
        borrarBuho(2, posicionBuho);
        borrarTuberia(0);
        posicionBuho += 1;
        
        if (posicionBuho > ALTO_PANTALLA - 2) {
            finDelJuego();
            return;
        }
        
        posicionTuberias[0] += 2;
        
        if (posicionTuberias[0] > 68) {
            puntaje++;
            actualizarPuntaje();
            posicionTuberias[0] = 4;
            generarTuberia(0);
        }
    }
}
//FIN BUHITOS

// INICIO 21BLACKJACK
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
        simboloPalo = "";  // Corazones
    } else if (palo == 'D') {
        simboloPalo = "";  // Diamantes
    } else if (palo == 'C') {
        simboloPalo = "";  // Tréboles
    } else if (palo == 'S') {
        simboloPalo = "";  // Picas
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
void jugarBlackjack(const string& nombreJugador1BJ, const string& nombreJugador2BJ, Resultados& resultadosJugador1BJ, Resultados& resultadosJugador2BJ) {
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

    mostrarMano(manoJugador1, palos, nombreJugador1BJ);  // Muestra la mano del jugador 1
    char eleccion;
    // Jugador 1 pide cartas hasta que se pase o decida plantarse
    while (calcularValorMano(manoJugador1) < 21) {
        cout << nombreJugador1BJ << ", quieres pedir otra carta? (s/n)? ";
        cin >> eleccion;

        if (eleccion == 's' || eleccion == 'S') {
            repartirCarta(mazo, palos, manoJugador1);
            mostrarMano(manoJugador1, palos, nombreJugador1BJ);

            if (calcularValorMano(manoJugador1) > 21) {
                cout << nombreJugador1BJ << ", te pasaste de 21. Perdiste!!!" << endl;
                resultadosJugador1BJ.perdidos++; 
                return;
            }
        } else {
            break; 
        }
    }

    mostrarMano(manoJugador2, palos, nombreJugador2BJ);  // Muestra la mano del jugador 2
    while (calcularValorMano(manoJugador2) < 21) {
        cout << nombreJugador2BJ << ", quieres pedir otra carta? (s/n)? ";
        cin >> eleccion;

        if (eleccion == 's' || eleccion == 'S') {
            repartirCarta(mazo, palos, manoJugador2);
            mostrarMano(manoJugador2, palos, nombreJugador2BJ);

            if (calcularValorMano(manoJugador2) > 21) {
                cout << nombreJugador2BJ << ", te pasaste de 21. Perdiste!!!" << endl;
                resultadosJugador2BJ.perdidos++;  
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
                cout << nombreJugador1BJ << " gana!!!" << endl;
                resultadosJugador1BJ.ganados++;
                resultadosJugador2BJ.perdidos++;
            } else if (valorJugador2 > valorJugador1) {
                cout << nombreJugador2BJ << " gana!!!" << endl;
                resultadosJugador2BJ.ganados++;
                resultadosJugador1BJ.perdidos++;
            } else {
                cout << "Empate entre los jugadores!!!" << endl;
                resultadosJugador1BJ.empatados++;
                resultadosJugador2BJ.empatados++;
            }
        } else if (valorJugador1 <= 21) {
            cout << nombreJugador1BJ << " gana!!!" << endl;
            resultadosJugador1BJ.ganados++;
            resultadosJugador2BJ.perdidos++;
        } else {
            cout << nombreJugador2BJ << " gana!!!" << endl;
            resultadosJugador2BJ.ganados++;
            resultadosJugador1BJ.perdidos++;
        }
    } else {
        // Si el dealer no se pasa de 21, se comparan las manos de los jugadores
        if (valorJugador1 > 21) {
            cout << nombreJugador1BJ << " se paso de 21. Dealer gana." << endl;
            resultadosJugador1BJ.perdidos++;
        } else if (valorJugador1 > valorDealer) {
            cout << nombreJugador1BJ << " gana." << endl;
            resultadosJugador1BJ.ganados++;
        } else if (valorJugador1 == valorDealer) {
            cout << nombreJugador1BJ << " empata con el Dealer." << endl;
            resultadosJugador1BJ.empatados++;
        } else {
            cout << "Dealer gana a " << nombreJugador1BJ << "." << endl;
            resultadosJugador1BJ.perdidos++;
        }

        if (valorJugador2 > 21) {
            cout << nombreJugador2BJ << " se paso de 21. Dealer gana." << endl;
            resultadosJugador2BJ.perdidos++;
        } else if (valorJugador2 > valorDealer) {
            cout << nombreJugador2BJ << " gana." << endl;
            resultadosJugador2BJ.ganados++;
        } else if (valorJugador2 == valorDealer) {
            cout << nombreJugador2BJ << " empata con el Dealer." << endl;
            resultadosJugador2BJ.empatados++;
        } else {
            cout << "Dealer gana a " << nombreJugador2BJ << "." << endl;
            resultadosJugador2BJ.perdidos++;
        }
    }
}
// FIN 21BlackJack

// INICIOMEMORIA
struct Jugador {
    string nombre;
    int puntaje;
    Jugador(string n, int p) : nombre(n), puntaje(p) {}
};

//vector para almacenar la tabla de posiciones
vector<Jugador> tablaPosiciones;

//funcion para guardar la tabla de posiciones en un archivo
void guardarTabla() {
    ofstream archivo("tabla_posiciones.txt");
    for (const auto& jugador : tablaPosiciones) {
        archivo << jugador.nombre << " " << jugador.puntaje << endl;
    }
    archivo.close();
}

//funcion para cargar la tabla de posiciones desde un archivo txt
void cargarTabla() {
    ifstream archivo("tabla_posiciones.txt");
    string nombre;
    int puntaje;

    while (archivo >> nombre >> puntaje) {
        tablaPosiciones.push_back(Jugador(nombre, puntaje));
    }
    archivo.close();
}

//funcion para mostrar la tabla
void mostrarTablaPosiciones() {
    system("cls"); 
    cout << "\n======= TABLA DE POSICIONES =======\n";
    cout << "Posicion\tNombre\t\tPuntaje\n";
    cout << "----------------------------------\n";

    sort(tablaPosiciones.begin(), tablaPosiciones.end(), [](const Jugador& a, const Jugador& b) {
        return a.puntaje > b.puntaje;
    });
    for (size_t i = 0; i < tablaPosiciones.size() && i < 10; ++i) {
        cout << (i + 1) << "\t\t" << tablaPosiciones[i].nombre << "\t\t" << tablaPosiciones[i].puntaje << endl;
    }
    cout << "==================================\n";

    cout << "\nPresiona cualquier tecla para regresar al menu principal...";
    getch(); //espera a que el usuario presione una tecla
}

//funcion para generar los numeros de forma aleatoria
string generarNumeros(int longitud) {
    string numeros;
    for (int i = 0; i < longitud; i++) {
        numeros += to_string(rand() % 10); 
    }
    return numeros;
}

//funcion para una pausa
void pausa(int milisegundos) {
    clock_t start_time = clock();
    while (clock() < start_time + milisegundos * CLOCKS_PER_SEC / 1000);
}

//funcion para jugar
void jugar() {
    system("cls"); 
    srand(time(0)); 
    string nombre;
    cout << "\nIngresa tu nombre: ";
    cin >> nombre;

    int nivel = 1;  
    int puntaje = 0;
    bool gano = true;

    while (nivel <= 20 && gano) {
        system("cls"); //limpiar pantalla antes de cada nivel
        cout << "\nNivel " << nivel << ": Memoriza los numeros\n";
        string numeros = generarNumeros(nivel + 2); 
        cout << numeros << endl;
        pausa(3000); 

        cout << string(50, '\n');

        cout << "Escribe los numeros que recuerdas: ";
        string respuesta;
        cin >> respuesta;

        if (respuesta == numeros) {
            cout << "¡Correcto! Pasas al siguiente nivel." << endl;
            puntaje += 5; 
            nivel++;
        } else {
            cout << "¡Incorrecto! El numero correcto era: " << numeros << endl;
            gano = false;
        }
    }

    if (gano) {
        cout << "Has completado todos los niveles." << endl;
    } else {
        cout << "Juego terminado. Tu puntaje final es: " << puntaje << endl;
    }

    tablaPosiciones.push_back(Jugador(nombre, puntaje));
    guardarTabla();
}

//funcion menú principal
void menu() {
    int opcionM;

    do {
        system("cls"); //limpiar la pantalla antes de mostrar el menú
        cout << "======= JUEGO DE MEMORIA =======" << endl;
        cout << "1. Jugar" << endl;
        cout << "2. Tabla de posiciones" << endl;
        cout << "3. Salir" << endl;
        cout << "================================" << endl;
        cout << "Selecciona una opcion: ";
        cin >> opcionM;

        switch (opcionM) {
            case 1:
                jugar();
                break;
            case 2:
                mostrarTablaPosiciones();
                break;
            case 3:
                cout << "Regresando al menu principal...\n";
                Sleep(1500);
                break;
                
            default:
                cout << "Opcion no valida. Intentalo de nuevo." << endl;
                pausa(2000); //pausa mostrar el mensaje
        }
    } while (opcionM != 3);
}
// FIN MEMORIA

//INICIO BINGO
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
    int bingoption;
    do {
        cout << " Bienvenido a BINGO \n";
        cout << "* * * * * * * * * * * \n";
        cout << "* 1. Jugar          * \n";
        cout << "* 2. Como jugar?    * \n";
        cout << "* 3. Ranking        * \n";
        cout << "* 4. Salir          * \n";
        cout << "* * * * * * * * * * * \n";
        cout << "Opcion: ";
        cin >> bingoption;

        if (cin.fail() || bingoption < 1 || bingoption > 4) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Opcion invalida. Por favor, elige una opcion valida.\n";
        }
    } while (bingoption < 1 || bingoption > 4);
    return bingoption;
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
void jugarbingo(const string& archivoRanking) {
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
// FIN BINGO

// INCNIO PREGUNTADOS
// constantes 
const int NUM_PREGUNTAS_preguntas = 20;      // total de preguntas 
const int PUNTOS_POR_CORRECTA_preguntas = 5; // puntaje por cada respuesta contestada correctamente
const int MAX_INTENTOS_preguntas = 5;        // los intentos maximos de equivocarse 

// funciones 
void mostrarMenu_preguntas();                     // Funcion para mostrar el menú principal
void mostrarBienvenida_preguntas();               // Funcion para mostrar la introducción del juego
void inicializarJuego_preguntas(string[], string[][4], int[]); // Carga las preguntas, opciones y respuestas correctas
void mezclarPreguntas_preguntas(string[], string[][4], int[]); // Mezcla las preguntas y respuestas aleatoriamente
int hacerPregunta_preguntas(int, string[], string[][4], int[]); // Realiza una pregunta al jugador
int jugar_preguntas(string[], string[][4], int[], string);      // Maneja el juego de un jugador
void jugarPartida_preguntas();                    // Inicia una partida para dos jugadores
void mostrarPuntajes_preguntas();                 // Muestra los puntajes almacenados
void guardarPuntaje_preguntas(const string&, int); // Guarda el puntaje de un jugador en un archivo
// PAUSA PREGUNTADOS

//MARCO MENU
const int ANCHO_PANTALLA_MENU = 100;
const int ALTO_PANTALLA_MENU = 30;
const int ANCHO_JUEGO_MENU = 65;

// Función para mover el cursor en la consola
void Cursor(int x, int y) {
    PosicionCursor.X = x;
    PosicionCursor.Y = y;
    SetConsoleCursorPosition(consola, PosicionCursor);
}

// Dibuja un marco en la pantalla
void Marco() {
    for (int i = 0; i < ANCHO_PANTALLA_MENU; i++) {
        Cursor(i, 0);
        cout << '*';
        Cursor(i, ALTO_PANTALLA_MENU);
        cout << '*';
    }
    for (int i = 0; i < ALTO_PANTALLA_MENU; i++) {
        Cursor(0, i);
        cout << '*';
        Cursor(ANCHO_PANTALLA_MENU - 1, i);
        cout << '*';
    }
    for (int i = 0; i < ALTO_PANTALLA_MENU; i++) {
        Cursor(ANCHO_JUEGO_MENU, i);
        cout << '*';
    }
}

// Función para mostrar el nombre del juego en la interfaz
void nombreJuego() {
    // Ajustamos las coordenadas para centrar el texto
    int xTexto = ANCHO_JUEGO_MENU + ((ANCHO_PANTALLA_MENU - ANCHO_JUEGO_MENU) / 2) - 7; // -7 para compensar el ancho del texto
    int yTexto = 2; // Altura fija para mostrar el título
    moverCursor(xTexto, yTexto);
    cout << "MINI JUEGOS UCA";
}

// Función para mostrar un logo ficticio
void mostrarTitulo() {
    int xLogo = ANCHO_JUEGO + 5; // Misma alineación que el título
    int yLogo = 4;               // Justo debajo del título
    Cursor(xLogo, yLogo);
    cout << "[ PROYECTO FINAL ]"; // Simulación de logo
}

// Función para mostrar nombres adicionales
void mostrarNombres() {
    int xNombres = ANCHO_JUEGO + 5; // Misma alineación que el título
    int yNombresInicio = 7;         // Debajo del logo

    // Mostrar los nombres proporcionados
    Cursor(xNombres, yNombresInicio);
    cout << "1. Miguel Escobar";
    Cursor(xNombres, yNombresInicio + 2);
    cout << "2. Eyler Guido";
    Cursor(xNombres, yNombresInicio + 4);
    cout << "3. Rogelio Benitez";
    Cursor(xNombres, yNombresInicio + 6);
    cout << "4. Adrian Mendez";
    Cursor(xNombres, yNombresInicio + 8);
    cout << "5. Jared Chinchilla";
    Cursor(xNombres, yNombresInicio + 10);
    cout << "Ing. Miguel Rivas";
}

void mostrarLogoASCII() {
    int xLogo = ANCHO_JUEGO + 5;  // Ajustamos la posición horizontal para centrarlo
    int yLogoInicio = 20;          // Bajamos el inicio del logo para centrarlo verticalmente

    Cursor(xLogo, yLogoInicio);
    cout << "   +-------+";        // Parte superior del cuadro
    Cursor(xLogo, yLogoInicio + 1);
    cout << "   |  UCA  |";        // Texto en la primera línea
    Cursor(xLogo, yLogoInicio + 2);
    cout << "   | GAMES |";        // Texto en la segunda línea
    Cursor(xLogo, yLogoInicio + 3);
    cout << "   +-------+";        // Parte inferior del cuadro
}
// MAIN DEL JUEGO FINAL
int main() {
    srand(time(0));
    const string archivoRanking = "ranking.txt"; // Nombre del archivo de ranking
    int opcionB;
    int opcionjuego,opcion, option, opcionBuho, regresar, opcion21, opcion_preguntas; // Variable para almacenar la opción seleccionada;
    string nombreJugador1BJ, nombreJugador2BJ;
    Resultados resultadosJugador1BJ, resultadosJugador2BJ;

    do {
        system("cls"); // Limpia la consola
        Marco();       // Dibuja el marco de la interfaz
        nombreJuego(); // Muestra el nombre en el margen derecho
        mostrarTitulo(); // Muestra el logo ficticio
        mostrarNombres(); // Muestra los nombres adicionales
        mostrarLogoASCII(); // Muestra el logo en formato ASCII

        // Menú de opciones
        Cursor(5, 3);
        cout << "----BIENVENIDO A MINIJUEGOS UCA----" << endl;
        Cursor(5, 5);
        cout << "--Puede elegir entre estos juegos--" << endl;
        Cursor(5, 7);
        cout << "1. Bingo" << endl;
        Cursor(5, 8);
        cout << "2. Buhitos" << endl;
        Cursor(5, 9);
        cout << "3. Memoria" << endl;
        Cursor(5, 10);
        cout << "4. 21BlackJack" << endl;
        Cursor(5, 11);
        cout << "5. Preguntados" << endl;
        Cursor(5, 12);
        cout << "6. Salir" << endl;
        Cursor(5, 14);
        cout << "Seleccione una opcion: ";
        cin >> opcionjuego;

        // Procesa la opción seleccionada
        switch (opcionjuego){
        case 1:
            system("cls");
            cout << "Cargando el juego 'Bingo'..." << endl;
            Sleep(1500);
                srand(time(0));

                do {
                    opcion = bienvenida();
                    switch (opcion) {
                        case 1:
                            jugarbingo(archivoRanking);
                            break;
                        case 2:
                            mostrarReglas();
                            break;
                        case 3:
                            // Leer y mostrar el ranking actualizado
                            mostrarRanking(leerRanking(archivoRanking));
                            break;
                        case 4:
                        cout << "Regresando al menu principal...\n";
                        Sleep(1500);
                        break;
                    }
                } while (opcion != 4);

                cout << "Gracias por jugar! Hasta la proxima.\n";
                            break;

            //buho
            configurarCursor(0, 0);
            srand((unsigned)time(NULL));
        case 2:
            system("cls");
            cout << "Cargando el juego 'Buhitos'..." << endl;
            Sleep(1500);
            // Aquí podrías llamar a la función del juego "Bingo"
            do {
            system("cls");
            cout << "----Buhitos----" << endl;
            cout << "1. Como jugar" << endl;
            cout << "2. Jugar" << endl;
            cout << "3. Puntaje final" << endl;
            cout << "4. Volver al menu principal" << endl;
            cout << "5. Salir" << endl;
            cout << "Selecciona una opcion: ";
            cin >> opcionBuho;

            switch (opcionBuho) {
            case 1:
                system("cls");
                cout << "Instrucciones del juego:" << endl;
                cout << "1. No tienes que dejar caer al Buho." << endl;
                cout << "2. Presiona la barra espaciadora para saltar." << endl;
                cout << "3. Tienes una barra de puntaje." << endl;
                cout << "4. Debes evadir todos los obstaculos." << endl;
                cout << "Estas listo para jugar? (Presiona 0 para regresar al menu principal)" << endl;
                cin >> regresar;
                break;

            case 2:
                jugarB();
                break;
    
            case 3:
                system("cls");
                cout << "Puntaje final: " << puntaje << endl;
                cout << "Presiona cualquier tecla para regresar al menu principal.";
                getch();
                break;
            case 4:
                cout << "Regresando al menu principal...\n";
                Sleep(1500);
                break;
            case 5:
                return 0;

            default:
                cout << "ERROR: Opcion no valida. Intentalo de nuevo." << endl;
                Sleep(1000);
                break;
            }

            } while (opcionBuho != 4);
            break;
        case 3:
            system("cls");
            cout << "Cargando el juego 'Memoria'..." << endl;
            Sleep(1500);
                cargarTabla(); 
                menu(); 
                break;
        case 4:
            system("cls");
            cout << "Cargando el juego '21BlackJack'..." << endl;
            Sleep(1500);


            // Recibe los nombres de los jugadores
            cout << "Introduce el nombre del Jugador 1: ";
            cin >> nombreJugador1BJ;
            cout << "Introduce el nombre del Jugador 2: ";
            cin >> nombreJugador2BJ;

            
            do {
                // Muestra el menú principal
                cout << "\n   ==MENU==\n1. Jugar\n2. Ver Instrucciones\n3. Ver Resultados\n4. Salir\n";
                cout << "Selecciona una opcion: ";
                cin >> opcion21;
                cin.ignore(); // Para ignorar el salto de línea después de leer el número

                // Ejecuta según la opción seleccionada
                switch (opcion21) {
                    case 1:
                        jugarBlackjack(nombreJugador1BJ, nombreJugador2BJ, resultadosJugador1BJ, resultadosJugador2BJ);
                        break;
                    case 2:
                        mostrarInstrucciones();
                        break;
                    case 3:
                        // Muestra los resultados acumulados de cada jugador
                        cout << "\nRESULTADOS:\n";
                        cout << nombreJugador1BJ << " - Ganados: " << resultadosJugador1BJ.ganados 
                            << ", Perdidos: " << resultadosJugador1BJ.perdidos 
                            << ", Empatados: " << resultadosJugador1BJ.empatados << endl;
                        cout << nombreJugador2BJ << " - Ganados: " << resultadosJugador2BJ.ganados 
                            << ", Perdidos: " << resultadosJugador2BJ.perdidos 
                            << ", Empatados: " << resultadosJugador2BJ.empatados << endl;
                        break;
                    case 4:
                        cout << "Regresando al menu principal...\n";
                        Sleep(1500);
                        break;
                    default:
                        cout << "Opcion invalida. Intenta nuevamente." << endl;
                }
                } while (opcion21 != 4);
                break;
                case 5:
                system("cls");
                cout << "Cargando el juego 'Preguntados'..." << endl;
                Sleep(1500);
                do{ // Ciclo infinito para mantener el programa en ejecución hasta que el usuario decida salir
                 
                        mostrarBienvenida_preguntas(); // llama la funcion para mostrar mensaje de bienvenida
                        mostrarMenu_preguntas(); // Llama a la funcion para mostrar el menu principal
                        cin >> opcion_preguntas; // Lee la opcion ingresada por el usuario

                        switch (opcion_preguntas) { // Estructura de control para decidir que hacer segun la opción
                            case 1:
                                jugarPartida_preguntas(); // Inicia una partida
                                break;
                            case 2:
                                mostrarPuntajes_preguntas(); // Muestra los puntajes almacenados
                                break;
                            case 3:
                            cout << "Regresando al menu principal...\n";
                            Sleep(1500);
                                break; // Sale del programa
                            default:
                                cout << "no valio, seleccione otra vez" << endl; // Mensaje para opcion no valida
                        }
                    } while (opcion_preguntas !=3);
                break;
                case 6:
                system("cls");
                cout << "Gracias por jugar! Hasta luego." << endl;
                Sleep(1500);
                break;
                default:
                    system("cls");
                    cout << "Opción no válida. Inténtelo nuevamente." << endl;
                    Sleep(1500);

                }
            } while (opcionjuego != 6); // El menú se repite hasta que se seleccione "Salir"
return 0;
}
// FIN DEL MAIN

// CONTINUACION FUNCIONES PREGUNTADOS
void mostrarMenu_preguntas() {
    // Imprime el menú principal del programa
    cout << "--------------" << endl;
    cout << "menu principal" << endl;
    cout << "--------------" << endl;
    cout << "1. Empezar el juego" << endl;
    cout << "2. Ver los mejores puntajes" << endl;
    cout << "3. Salir del juego" << endl;
    cout << "por favor seleccione una opcion: ";
}

void mostrarBienvenida_preguntas() {
    // Muestra la introducción del juego
    cout << "bienvenido, este juego consiste en responder la mayor cantidad de preguntas de manera correcta en comparacion a tu contrincante " << endl;
    cout << "cuentas con " << MAX_INTENTOS_preguntas << " intentos y cada respuesta correcta vale " << PUNTOS_POR_CORRECTA_preguntas << " puntos." << endl;
    cout << "mucha suerte en tu partida" << endl;
}

void inicializarJuego_preguntas(string preguntas_preguntas[], string opciones_preguntas[][4], int respuestas_preguntas[]) {
    // Carga las preguntas, opciones y respuestas correctas
    preguntas_preguntas[0] = "Cual es el planeta mas cercano al sol";
    preguntas_preguntas[1] = "Cual es el oceano mas grande";
    preguntas_preguntas[2] = "Quien pinto la Mona Lisa";
    preguntas_preguntas[3] = "Que gas es necesario para respirar";
    preguntas_preguntas[4] = "Cual es el animal terrestre mas rapido";
    preguntas_preguntas[5] = "Cuantos colores hay en el arcoiris";
    preguntas_preguntas[6] = "Cual es el pais mas grande del mundo";
    preguntas_preguntas[7] = "En que fecha llego el hombre a la luna";
    preguntas_preguntas[8] = "Cual es el idioma mas hablado en el mundo";
    preguntas_preguntas[9] = "Quien escribio Romeo y Julieta";
    preguntas_preguntas[10] = "Cual es el metal mas ligero";
    preguntas_preguntas[11] = "Que pais tiene forma de bota";
    preguntas_preguntas[12] = "Que deporte se practica en Wimbledon";
    preguntas_preguntas[13] = "Que animal produce la miel";
    preguntas_preguntas[14] = "Cual es la capital de Japon";
    preguntas_preguntas[15] = "Quien desarrollo la teoria de la relatividad";
    preguntas_preguntas[16] = "Cual es el rio mas largo del mundo";
    preguntas_preguntas[17] = "Que organo bombea la sangre";
    preguntas_preguntas[18] = "Que instrumento tiene teclas blancas y negras";
    preguntas_preguntas[19] = "Cuantos minutos tiene una hora";

    // Matriz de opciones para cada pregunta
    string opcionesTemp_preguntas[NUM_PREGUNTAS_preguntas][4] = {
        {"Mercurio", "Venus", "Marte", "Jupiter"},
        {"Oceano Atlantico", "Oceano Indico", "Oceano Pacifico", "Oceano Artico"},
        {"Vincent van Gogh", "Leonardo da Vinci", "Pablo Picasso", "Miguel Angel"},
        {"Nitrogeno", "Dioxido de carbono", "Oxigeno", "Hidrogeno"},
        {"Leon", "Tigre", "Guepardo", "Elefante"},
        {"5", "6", "7", "8"},
        {"China", "Rusia", "Estados Unidos", "Canada"},
        {"1959", "1961", "1969", "1972"},
        {"Espanol", "Ingles", "Mandarin", "Hindu"},
        {"Cervantes", "Shakespeare", "Dante", "Goethe"},
        {"Oro", "Hierro", "Plata", "Litio"},
        {"Espana", "Francia", "Italia", "Portugal"},
        {"Baloncesto", "Tenis", "Futbol", "Natacion"},
        {"Abeja", "Mariposa", "Avispa", "Mosca"},
        {"Pekin", "Tokio", "Seul", "Kioto"},
        {"Newton", "Tesla", "Einstein", "Hawking"},
        {"Nilo", "Amazonas", "Yangtse", "Mississippi"},
        {"Pulmones", "Corazon", "Rinon", "Higado"},
        {"Violin", "Guitarra", "Piano", "Flauta"},
        {"60", "100", "120", "90"}
    };

    // Copiar las opciones a la matriz global
    for (int i = 0; i < NUM_PREGUNTAS_preguntas; i++) {
        for (int j = 0; j < 4; j++) {
            opciones_preguntas[i][j] = opcionesTemp_preguntas[i][j];
        }
    }

    // Respuestas correctas (0 = primera opción, 1 = segunda, etc.)
    int respuestasTemp_preguntas[NUM_PREGUNTAS_preguntas] = {0, 2, 1, 2, 2, 2, 1, 2, 2, 1, 3, 2, 1, 0, 1, 2, 1, 1, 2, 0};
    for (int i = 0; i < NUM_PREGUNTAS_preguntas; i++) {
        respuestas_preguntas[i] = respuestasTemp_preguntas[i];
    }
}
// Mezcla las preguntas, opciones y respuestas de forma aleatoria
void mezclarPreguntas_preguntas(string preguntas_preguntas[], string opciones_preguntas[][4], int respuestas_preguntas[]) {
    srand(time(0)); // Inicializa la semilla para generar números aleatorios
    for (int i = 0; i < NUM_PREGUNTAS_preguntas; i++) {
        int j = rand() % NUM_PREGUNTAS_preguntas; // Selecciona un índice aleatorio
        swap(preguntas_preguntas[i], preguntas_preguntas[j]); // Intercambia las preguntas
        swap(opciones_preguntas[i], opciones_preguntas[j]);   // Intercambia las opciones
        swap(respuestas_preguntas[i], respuestas_preguntas[j]); // Intercambia las respuestas correctas
    }
}

// Realiza una pregunta al jugador y valida su respuesta
int hacerPregunta_preguntas(int numPregunta, string preguntas_preguntas[], string opciones_preguntas[][4], int respuestas_preguntas[]) {
    cout << "Pregunta: " << preguntas_preguntas[numPregunta] << endl; // Muestra la pregunta
    for (int i = 0; i < 4; i++) {
        cout << i + 1 << ". " << opciones_preguntas[numPregunta][i] << endl; // Muestra las opciones
    }
    int respuestaUsuario;
    cout << "Ingrese el numero de su respuesta: "; // Pide al usuario que ingrese su respuesta
    cin >> respuestaUsuario;

    // Valida que la respuesta sea un número entre 1 y 4
    while (respuestaUsuario < 1 || respuestaUsuario > 4) {
        cout << "No valido"; // Mensaje de error si la respuesta no es válida
        cin >> respuestaUsuario;
    }

    return respuestaUsuario - 1; // Devuelve el índice de la respuesta seleccionada
}

// Gestiona la partida para un jugador
int jugar_preguntas(string preguntas_preguntas[], string opciones_preguntas[][4], int respuestas_preguntas[], string jugador) {
    int puntos = 0; // Inicializa los puntos del jugador
    int intentos = MAX_INTENTOS_preguntas; // Inicializa el número de intentos disponibles

    // Itera a través de las preguntas mientras queden intentos
    for (int i = 0; i < NUM_PREGUNTAS_preguntas && intentos > 0; i++) {
        cout << endl << "Turno de " << jugador << endl; // Indica el turno del jugador
        int respuesta = hacerPregunta_preguntas(i, preguntas_preguntas, opciones_preguntas, respuestas_preguntas); // Realiza la pregunta

        // Verifica si la respuesta es correcta
        if (respuesta == respuestas_preguntas[i]) {
            cout << "Correcto +5 puntos." << endl; // Mensaje de respuesta correcta
            puntos += PUNTOS_POR_CORRECTA_preguntas; // Suma puntos
        } else {
            cout << "Incorrecto pierdes un intento." << endl; // Mensaje de respuesta incorrecta
            intentos--; // Resta un intento
        }
    }

    cout << "Fin del juego para " << jugador << ". Puntos: " << puntos << endl; // Muestra los puntos finales del jugador
    return puntos; // Devuelve los puntos obtenidos
}

// Modo de juego de dos jugadores
void jugarPartida_preguntas() {
    // Arreglos para las preguntas, opciones y respuestas
    string preguntas_preguntas[NUM_PREGUNTAS_preguntas];
    string opciones_preguntas[NUM_PREGUNTAS_preguntas][4];
    int respuestas_preguntas[NUM_PREGUNTAS_preguntas];

    // Inicializa las preguntas, opciones y respuestas
    inicializarJuego_preguntas(preguntas_preguntas, opciones_preguntas, respuestas_preguntas);
    // Mezcla las preguntas, opciones y respuestas
    mezclarPreguntas_preguntas(preguntas_preguntas, opciones_preguntas, respuestas_preguntas);

    string jugador1, jugador2; // Nombres de los jugadores
    cout << "Ingrese el nombre del jugador 1: "; // Solicita el nombre del jugador 1
    cin >> jugador1;
    cout << "Ingrese el nombre del jugador 2: "; // Solicita el nombre del jugador 2
    cin >> jugador2;

    // Juega la partida para cada jugador y almacena sus puntajes
    int puntosJugador1 = jugar_preguntas(preguntas_preguntas, opciones_preguntas, respuestas_preguntas, jugador1);
    int puntosJugador2 = jugar_preguntas(preguntas_preguntas, opciones_preguntas, respuestas_preguntas, jugador2);

    // Muestra el resultado final de ambos jugadores
    cout << "Resultado final: " << endl;
    cout << jugador1 << ": " << puntosJugador1 << " puntos." << endl;
    cout << jugador2 << ": " << puntosJugador2 << " puntos." << endl;

    // Determina al ganador o si hay empate
    if (puntosJugador1 > puntosJugador2) {
        cout << "Ganador: " << jugador1 << "!" << endl;
    } else if (puntosJugador2 > puntosJugador1) {
        cout << "Ganador: " << jugador2 << "!" << endl;
    } else {
        cout << "Es un empate" << endl;
    }

    // Guarda los puntajes de ambos jugadores
    guardarPuntaje_preguntas(jugador1, puntosJugador1);
    guardarPuntaje_preguntas(jugador2, puntosJugador2);
}

// Muestra los puntajes guardados en el archivo
void mostrarPuntajes_preguntas() {
    ifstream archivo("puntajes.txt"); // Abre el archivo de puntajes en modo lectura
    if (!archivo) {
        cout << "No hay puntajes guardados." << endl; // Mensaje si no hay archivo
        return;
    }

    string linea;
    cout << "Puntajes guardados:" << endl;
    while (getline(archivo, linea)) { // Lee línea por línea del archivo
        cout << linea << endl; // Muestra cada puntaje
    }

    archivo.close(); // Cierra el archivo
}

// Guarda el puntaje de un jugador en el archivo
void guardarPuntaje_preguntas(const string &jugador, int puntos) {
    ofstream archivo("puntajes.txt", ios::app); // Abre el archivo en modo agregar
    if (archivo) {
        archivo << jugador << ": " << puntos << " puntos" << endl; // Escribe el puntaje del jugador
    }
    archivo.close(); // Cierra el archivo
}
/*Bibliografia:

C++ library - . Retrieved Nov 27, 2024, from https://www.tutorialspoint.com/cpp_standard_library/fstream.htm
C++ programming with visual studio code. Retrieved Nov 27, 2024, from https://code.visualstudio.com/docs/languages/cpp
C++ standard library - cppreference.com. https://en.cppreference.com/w/cpp/standard_library
C++ vectors (with examples). https://www.programiz.com/cpp-programming/vectors
Conio.h. (2009, -10-22). Retrieved Nov 27, 2024, from https://ccodigo.help/tag/conio-h/
Dev - C++ - funciones sleep() y delay(). Retrieved Nov 27, 2024, from https://www.lawebdelprogramador.com/foros/Dev-C/125179-Funciones-sleep-y-delay.html
Dormir. https://pubs.opengroup.org/onlinepubs/009696799/functions/sleep.html
La librería conio.h. (2013, domingo, 26 de mayo d). https://programavideojuegos.blogspot.com/2013/05/la-libreria-conioh.html
Map in C++ standard template library (STL). (2015, -12-07T10:58:42+00:00). Retrieved Nov 27, 2024, from https://www.geeksforgeeks.org/map-associative-containers-the-c-standard-template-library-stl/
Marticho, J. (2018, -11-30). ¿Cómo hacer una función de un frame (cuadro) para un menú en C++? https://es.stackoverflow.com/q/218221
La librería conio.h. (2013, domingo, 26 de mayo d). https://programavideojuegos.blogspot.com/2013/05/la-libreria-conioh.html//
Marticho, J. (2018, -11-30). ¿Cómo hacer una función de un frame (cuadro) para un menú en C++? https://es.stackoverflow.com/q/218221//
https://github.com/AngularsCoding/Flappy-Bird/blob/main/flappybird.cpp// */