#include <iostream>
#include <fstream>   // se usara para manejar archivos 
#include <string>    // nos servira para para trabajar con cadenas de texto
#include <algorithm> // es para usar funciones como swap() para intercambiar valores
#include <cstdlib>   // para usar funciones relacionadas con números aleatorios
#include <ctime>     // se usa para generar semillas de números aleatorios
#include <vector>    // para manejar estructuras dinámicas como vectores

using namespace std;

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

int main() {
    while (true) { // Ciclo infinito para mantener el programa en ejecución hasta que el usuario decida salir
        mostrarBienvenida_preguntas(); // llama la funcion para mostrar mensaje de bienvenida
        mostrarMenu_preguntas(); // Llama a la funcion para mostrar el menu principal
        int opcion_preguntas; // Variable para almacenar la opción seleccionada
        cin >> opcion_preguntas; // Lee la opcion ingresada por el usuario

        switch (opcion_preguntas) { // Estructura de control para decidir que hacer segun la opción
            case 1:
                jugarPartida_preguntas(); // Inicia una partida
                break;
            case 2:
                mostrarPuntajes_preguntas(); // Muestra los puntajes almacenados
                break;
            case 3:
                cout << "salio del juego" << endl; // Mensaje de despedida
                return 0; // Sale del programa
            default:
                cout << "no valio, seleccione otra vez" << endl; // Mensaje para opcion no valida
        }
    }
    return 0; // Fin del programa principal
}

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
