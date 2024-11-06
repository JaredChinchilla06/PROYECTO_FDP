#include <iostream>
#include <conio.h>
using namespace std;

void DibujoBuho(char salto){
    cout << "  ___ " << endl;
    cout << " {o,o}" << endl;
    cout << " /)  )" << endl;
    cout << "  \" \" " << endl;
}

int main(){

    int opcion, regresar;
    char jump = 32;

    do{
        cout << "----Bhuitos----" << endl;
        cout << "1. Como jugar" << endl;
        cout << "2. Jugar" << endl;
        cout << "3. Puntaje final" << endl;
        cin >> opcion;
        
        if (opcion >= 0){
        
        switch (opcion){
        
        case 1:
        cout << "1. No tienes que dejar caer al Buho." << endl;
        cout << "2. Preciona la barra espaciadora para saltar." << endl;
        cout << "3. Tendras una barra de puntaje." << endl;
        cout << "4. Tienes que evadir todos los obstaculos." << endl;
        cout << "Estas listo para jugar? (Presiona 0 para regresar al menu principal)" << endl;
        cin >> regresar;
        break;

        case 2:
        DibujoBuho(jump);
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