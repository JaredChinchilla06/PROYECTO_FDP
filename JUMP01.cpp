#include <iostream>
#include <conio.h>
#include <vector>
#include <dos.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
using namespace std;

HANDLE consola = GetStdHandle(STD_OUTPUT_HANDLE);
COORD PosicionCursor;

const int ANCHO_PANTALLA = 90; // Ancho total de la pantalla
const int ALTO_PANTALLA = 26; // Alto total de la pantalla
const int ANCHO_JUEGO = 70;   // Ancho de la sección donde se juega
const int ANCHO_OBJETO = 5;   // Ancho del búho u otros objetos
const int ALTO_OBJETO = 4;    // Alto del búho u otros objetos
const int TAMANIO_HUECO = 7;  // Tamaño del espacio en las tuberías

int posicionTuberias[3];
int posicionEspacio[3];
int banderaTuberias[3];

int posicionBuho = 6;  // Posición vertical inicial del pájaro
int puntaje = 0; //puntaje del jugador

void moverCursor(int x, int y) {
    PosicionCursor.X = x;
    PosicionCursor.Y = y;
    SetConsoleCursorPosition(consola, PosicionCursor);
}

void configurarCursor(bool visible, DWORD tamano) {
    if (tamano == 0)
        tamano = 20;
    
    CONSOLE_CURSOR_INFO informacionCursor;
    informacionCursor.bVisible = visible;
    informacionCursor.dwSize = tamano;
    SetConsoleCursorInfo(consola, &informacionCursor);
}

void dibujarBorde() {
    for (int i = 0; i < ANCHO_PANTALLA; i++) {
        moverCursor(i, 0); cout << '*';  // Borde superior
        moverCursor(i, ALTURA_PANTALLA); cout << '*';  // Borde inferior
    }
    for (int i = 0; i < ALTURA_PANTALLA; i++) {
        moverCursor(0, i); cout << '*';  // Borde izquierdo
        moverCursor(ANCHO_PANTALLA, i); cout << '*';  // Borde derecho
    }
    for (int i = 0; i < ALTURA_PANTALLA; i++) {
        moverCursor(ANCHO_JUEGO, i); cout << '*';  // Separador del área de juego y la UI
    }
}

void dibujarBuho(int x, int y) {
    moverCursor(x, y);     cout << "  ___ ";
    moverCursor(x, y + 1); cout << " {o,o}";
    moverCursor(x, y + 2); cout << " /)  )";
    moverCursor(x, y + 3); cout << "  \" \" ";
}

void borrarBuho(int x, int y) {
    moverCursor(x, y);     cout << "     ";
    moverCursor(x, y + 1); cout << "     ";
    moverCursor(x, y + 2); cout << "     ";
    moverCursor(x, y + 3); cout << "     ";
}

int detectarColision() {
    if (posicionTuberias[0] >= 61) {
        if (posicionBuho < posicionEspacio[0] || posicionBuho > posicionEspacio[0] + TAM_GAP) {
            return 1;  // Hay colisión
        }
    }
    return 0;  // No hay colisión
}

void finDelJuego() {
    system("cls");
    cout << endl;
    cout << "------------------------------" << endl;
    cout << "-------- Fin del Juego -------" << endl;
    cout << "------------------------------" << endl << endl;
    cout << "Presiona cualquier tecla para volver al menú.";
    getch();
}

void actualizarPuntaje() {
    moverCursor(ANCHO_JUEGO + 7, 5);
    cout << "Puntaje: " << puntaje << endl;
}

void generarTuberia(int indice) {
    posicionEspacio[indice] = 3 + rand() % 14;  // Posición aleatoria del espacio
}

void dibujarTuberia(int indice) {
    if (banderaTuberias[indice] == true) {
        for (int i = 0; i < posicionEspacio[indice]; i++) {  // Parte superior de la tubería
            moverCursor(ANCHO_JUEGO - posicionTuberias[indice], i + 1); cout << "***";
        }
        for (int i = posicionEspacio[indice] + TAM_GAP; i < ALTURA_PANTALLA - 1; i++) {  // Parte inferior
            moverCursor(ANCHO_JUEGO - posicionTuberias[indice], i + 1); cout << "***";
        }
    }
}

void borrarTuberia(int indice) {
    if (banderaTuberias[indice] == true) {
        for (int i = 0; i < posicionEspacio[indice]; i++) {
            moverCursor(ANCHO_JUEGO - posicionTuberias[indice], i + 1); cout << "   ";
        }
        for (int i = posicionEspacio[indice] + TAM_GAP; i < ALTURA_PANTALLA - 1; i++) {
            moverCursor(ANCHO_JUEGO - posicionTuberias[indice], i + 1); cout << "   ";
        }
    }
}

void jugar() {
    posicionPajaro = 6;
    puntaje = 0;
    banderaTuberias[0] = 1;
    banderaTuberias[1] = 0;
    posicionTuberias[0] = posicionTuberias[1] = 4;
    
    system("cls");
    dibujarBorde();
    generarTuberia(0);
    actualizarPuntaje();
    
    moverCursor(ANCHO_JUEGO + 5, 2); 
    cout << "--Buhitos--";

    moverCursor(ANCHO_JUEGO + 6, 4);
    cout << "-----------";

    moverCursor(ANCHO_JUEGO + 7, 12);
    cout << "Controles";

    moverCursor(ANCHO_JUEGO + 7, 13);
    cout << "----------";

    moverCursor(ANCHO_JUEGO + 2, 14);
    cout << " Barra espaciadora = saltar";
    
    moverCursor(10, 5);
    cout << "Presiona cualquier tecla para comenzar";
    getch();

    moverCursor(10, 5);
    
    cout << "                              ";
    
    while (1) {
        // Detectar si se presiona una tecla
        if (kbhit()) {
            char ch = getch();
            if (ch == 32) {  // Barra espaciadora
                if (posicionPajaro > 3)
                    posicionPajaro -= 3;  // Mueve al pájaro hacia arriba
            }
            if (ch == 27) {  // Tecla ESC
                break;
            }
        }
        
        // Dibujar y borrar elementos en la pantalla
        dibujarPajaro();
        dibujarTuberia(0);
        dibujarTuberia(1);
        if (detectarColision() == 1) {
            finDelJuego();
            return;
        }
        Sleep(100);
        borrarPajaro();
        borrarTuberia(0);
        borrarTuberia(1);
        posicionPajaro += 1;  // Mueve al pájaro hacia abajo
    
        if (posicionPajaro > ALTURA_PANTALLA - 2) {
            finDelJuego();
            return;
        }
        
        // Mueve las tuberías y genera nuevas si es necesario
        if (banderaTuberias[0] == 1)
            posicionTuberias[0] += 2;
        
        if (banderaTuberias[1] == 1)
            posicionTuberias[1] += 2;
        
        if (posicionTuberias[0] >= 40 && posicionTuberias[0] < 42) {
            banderaTuberias[1] = 1;
            posicionTuberias[1] = 4;
            generarTuberia(1);
        }
        if (posicionTuberias[0] > 68) {
            puntaje++;
            actualizarPuntaje();
            banderaTuberias[1] = 0;
            posicionTuberias[0] = posicionTuberias[1];
            posicionEspacio[0] = posicionEspacio[1];
        }
    }
}

int main() {
    configurarCursor(0, 0); 
    srand((unsigned)time(NULL)); // Inicializa la semilla para los números aleatorios

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
            jugar();  // Llama a la función `play()` para comenzar el juego
            break;

        case 3:
            system("cls");
            cout << "Puntaje final: " << score << endl; // Muestra el puntaje final
            cout << "Presiona cualquier tecla para regresar al menu principal.";
            getch();
            break;

        case 4:
            exit(0); // Sale del juego
            break;

        default:
            cout << "ERROR: Opcion no valida. Intentalo de nuevo." << endl;
            Sleep(1000);
            break;
        }

    } while (opcion != 4);

    return 0;
}