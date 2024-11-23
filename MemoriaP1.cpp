#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <conio.h>

using namespace std;

// funcion para generar números aleatorios
string generarNumeros(int longitud) {
    string numeros;
    for (int i = 0; i < longitud; i++) {
        numeros += to_string(rand() % 10);
    }
    return numeros;
}

// funcion pausa
void pausa(int milisegundos) {
    clock_t start_time = clock();
    while (clock() < start_time + milisegundos * CLOCKS_PER_SEC / 1000);
}

// funcion para jugar
void jugar() {
    system("cls"); 
    srand(time(0)); 
    string nombre;
    cout << "\nIngresa tu nombre: ";
    cin >> nombre;

    int nivel = 1;  
    bool gano = true;

    while (nivel <= 5 && gano) { 
        system("cls"); 
        cout << "\nNivel " << nivel << ": Memoriza los numeros\n";
        string numeros = generarNumeros(nivel + 2); 
        cout << numeros << endl;
        pausa(3000); // mostrar numeros por 3 segundos

        cout << string(50, '\n');

        cout << "Escribe los numeros que recuerdas: ";
        string respuesta;
        cin >> respuesta;

        if (respuesta == numeros) {
            cout << "¡Correcto! Pasas al siguiente nivel.\n";
            nivel++;
        } else {
            cout << "¡Incorrecto! El numero correcto era: " << numeros << endl;
            gano = false;
        }
    }

    if (gano) {
        cout << "¡Has completado los niveles disponibles!\n";
    } else {
        cout << "Juego terminado. Intentalo de nuevo.\n";
    }

    cout << "\nPresiona cualquier tecla para regresar al menu principal...";
    getch();
}

// funcion menu principal
void menu() {
    int opcion;

    do {
        system("cls"); 
        cout << "======= JUEGO DE MEMORIA =======" << endl;
        cout << "1. Jugar" << endl;
        cout << "2. Salir" << endl;
        cout << "================================" << endl;
        cout << "Selecciona una opcion\n: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                jugar();
                break;
            case 2:
                cout << "Saliendo del juego. ¡Hasta luego!\n";
                break;
            default:
                cout << "Opcion no valida. Intentalo de nuevo.\n";
                pausa(2000); 
        }
    } while (opcion != 2);
}

// funcion principal
int main() {
    menu();        
    return 0;
}