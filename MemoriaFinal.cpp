#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <conio.h> 

using namespace std;

// estructura para almacenar la informacion de un jugador
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
    int opcion;

    do {
        system("cls"); //limpiar la pantalla antes de mostrar el menú
        cout << "======= JUEGO DE MEMORIA =======" << endl;
        cout << "1. Jugar" << endl;
        cout << "2. Tabla de posiciones" << endl;
        cout << "3. Salir" << endl;
        cout << "================================" << endl;
        cout << "Selecciona una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                jugar();
                break;
            case 2:
                mostrarTablaPosiciones();
                break;
            case 3:
                cout << "Saliendo del juego. ADIOS PAPU" << endl;
                break;
            default:
                cout << "Opcien no válida. Intentalo de nuevo." << endl;
                pausa(2000); //pausa mostrar el mensaje
        }
    } while (opcion != 3);
}

//funcion principal
int main() {
    cargarTabla(); 
    menu();        
    return 0;
}