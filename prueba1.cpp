#include <iostream>
#include <conio.h>
#include <vector>
#include <dos.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
using namespace std;

void coordenadas(int x, int y){
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

void DibujoBuho(char salto){
    cout << "  ___ " << endl;
    cout << " {o,o}" << endl;
    cout << " /)  )" << endl;
    cout << "  \" \" " << endl;
}

void play(){
    system("cls");

    while (1){
        Sleep(100);
    }
}

int main(){

    int filas = 26, columnas = 90;
    int opcion, regresar;
    char jump = 32;
    
    do{
    
        vector<vector<char>> marco(filas, vector<char>(columnas, ' '));
    
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                if (i == 0 || i == filas - 1 || j == 0 || j == columnas - 1) {
                    marco[i][j] = '*';
                }
            }
        }
    
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                cout << marco[i][j];
                }
                cout << endl;
        }

        coordenadas(31, 1);
        cout << "----Bhuitos----" << endl;
        coordenadas(5, 6);
        cout << "1. Como jugar" << endl;
        coordenadas(5, 7);
        cout << "2. Jugar" << endl;
        coordenadas(5, 8);
        cout << "3. Puntaje final" << endl;
        coordenadas(5, 9);
        cin >> opcion;
        
        if (opcion >= 0){
        
        switch (opcion){
        
        case 1:
        do {
        cout << "1. No tienes que dejar caer al Buho." << endl;
        cout << "2. Preciona la barra espaciadora para saltar." << endl;
        cout << "3. Tendras una barra de puntaje." << endl;
        cout << "4. Tienes que evadir todos los obstaculos." << endl;
        cout << "Estas listo para jugar? (Presiona 0 para regresar al menu principal)" << endl;
        cin >> regresar;
        } while (regresar != 1);
        break;

        case 2:
        DibujoBuho(jump);

        Sleep(100);
        break;

        default:
        break;
        }

    } else {
        cout << "ERROR: Opcion no valida. Intentalo de nuevo." << endl;
    }

} while (opcion != 0);

    
    return 0;
}