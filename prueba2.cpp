//Se empieza incluyendo las librerias a utilizar en el juego//
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);
COORD PosicionCursor;

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
    cout << "Presiona cualquier tecla para volver al menú.";
    getch(); //la variable "getch" se saca de la libreria Conio.h para detectar cualquier tecla que precione el usuario//
}

//Se hace uso de una funcion para ver el puntaje del jugador//
void actualizarPuntaje() {
    moverCursor(ANCHO_JUEGO + 7, 5);
    cout << "Puntaje: " << puntaje;
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
void jugar() {

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

//Luego de todas las funciones se realiza el cuerpo main del codigo//
int main() {
    configurarCursor(0, 0);
    srand((unsigned)time(NULL));
    int opcion, regresar;
        
    do {
        system("cls");
        cout << "----Bhuitos----" << endl;
        cout << "1. Como jugar" << endl;
        cout << "2. Jugar" << endl;
        cout << "3. Puntaje final" << endl;
        cout << "4. Salir" << endl;
        cout << "Selecciona una opcion: ";
        cin >> opcion;

        switch (opcion) {
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
            jugar();
            break;
 
        case 3:
            system("cls");
            cout << "Puntaje final: " << puntaje << endl;
            cout << "Presiona cualquier tecla para regresar al menu principal.";
            getch();
            break;

        case 4:
            return 0;

        default:
            cout << "ERROR: Opcion no valida. Intentalo de nuevo." << endl;
            Sleep(1000);
            break;
        }

    } while (opcion != 4);

    return 0;
}

//Bibliografia:
//La librería conio.h. (2013, domingo, 26 de mayo d). https://programavideojuegos.blogspot.com/2013/05/la-libreria-conioh.html//
//Marticho, J. (2018, -11-30). ¿Cómo hacer una función de un frame (cuadro) para un menú en C++? https://es.stackoverflow.com/q/218221//
//https://github.com/AngularsCoding/Flappy-Bird/blob/main/flappybird.cpp//