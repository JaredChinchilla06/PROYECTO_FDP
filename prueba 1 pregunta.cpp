#include <iostream>
#include <string>

using namespace std;

const int NUM_PREGUNTAS = 20; // Número total de preguntas
const int PUNTOS_POR_CORRECTA = 5; // Puntos que otorga cada respuesta correcta
const int MAX_INTENTOS = 5; // Máximo de intentos antes de terminar el juego

// Función para mostrar una pregunta y capturar la respuesta del usuario
int hacerPregunta(int indice, string preguntas[], string opciones[][4], int respuestas[]);

// Función para ejecutar el juego
void ejecutarJuego();

int main() {
    ejecutarJuego();
    return 0;
}

void ejecutarJuego() {
    // Arreglo de preguntas
    string preguntas[NUM_PREGUNTAS] = {
        "¿Cuál es el planeta más cercano al sol?", 
        "¿Cuál es el océano más grande?", 
        "¿Quién pintó la Mona Lisa?", 
        "¿Qué gas es necesario para respirar?", 
        "¿Cuál es el animal terrestre más rápido?", 
        "¿Cuántos colores hay en el arcoíris?",
        "¿Cuál es el país más grande del mundo?", 
        "¿En qué año llegó el hombre a la luna?", 
        "¿Cuál es el idioma más hablado en el mundo?", 
        "¿Quién escribió 'Romeo y Julieta'?",
        "¿Cuál es el metal más ligero?", 
        "¿Qué país tiene forma de bota?", 
        "¿Qué deporte se practica en Wimbledon?", 
        "¿Qué animal produce la miel?", 
        "¿Cuál es la capital de Japón?",
        "¿Quién desarrolló la teoría de la relatividad?", 
        "¿Cuál es el río más largo del mundo?", 
        "¿Qué órgano bombea la sangre?", 
        "¿Qué instrumento tiene teclas blancas y negras?", 
        "¿Cuántos minutos tiene una hora?"
    };
    
    // Opciones para cada pregunta
    string opciones[NUM_PREGUNTAS][4] = {
        {"Mercurio", "Venus", "Marte", "Júpiter"},
        {"Océano Atlántico", "Océano Índico", "Océano Pacífico", "Océano Ártico"},
        {"Vincent van Gogh", "Leonardo da Vinci", "Pablo Picasso", "Miguel Ángel"},
        {"Nitrógeno", "Dióxido de carbono", "Oxígeno", "Hidrógeno"},
        {"León", "Tigre", "Guepardo", "Elefante"},
        {"5", "6", "7", "8"},
        {"China", "Rusia", "Estados Unidos", "Canadá"},
        {"1959", "1961", "1969", "1972"},
        {"Español", "Inglés", "Mandarín", "Hindú"},
        {"Cervantes", "Shakespeare", "Dante", "Goethe"},
        {"Oro", "Hierro", "Plata", "Litio"},
        {"España", "Francia", "Italia", "Portugal"},
        {"Baloncesto", "Tenis", "Fútbol", "Natación"},
        {"Abeja", "Mariposa", "Avispa", "Mosca"},
        {"Pekín", "Tokio", "Seúl", "Kioto"},
        {"Newton", "Tesla", "Einstein", "Hawking"},
        {"Nilo", "Amazonas", "Yangtsé", "Mississippi"},
        {"Pulmones", "Corazón", "Riñón", "Hígado"},
        {"Violín", "Guitarra", "Piano", "Flauta"},
        {"60", "100", "120", "90"}
    };

    // Respuestas correctas (índice de la opción correcta en cada pregunta)
    int respuestas[NUM_PREGUNTAS] = {0, 2, 1, 2, 2, 2, 1, 2, 2, 1, 3, 2, 1, 0, 1, 2, 1, 1, 2, 0};

    int puntaje = 0; // Puntaje total del usuario
    int intentos = MAX_INTENTOS; // Intentos restantes

    cout << "¡Bienvenido al juego de preguntas tipo Preguntados!" << endl;
    cout << "Tienes " << MAX_INTENTOS << " intentos. Cada respuesta correcta vale " << PUNTOS_POR_CORRECTA << " puntos." << endl;
    cout << "¡Buena suerte!\n" << endl;

    // Ciclo de preguntas
    for (int i = 0; i < NUM_PREGUNTAS && intentos > 0; i++) {
        int resultado = hacerPregunta(i, preguntas, opciones, respuestas);
        
        if (resultado == 1) {
            puntaje += PUNTOS_POR_CORRECTA;
            cout << "¡Correcto! Puntos actuales: " << puntaje << endl;
        } else {
            intentos--;
            cout << "Incorrecto. Intentos restantes: " << intentos << endl;
        }
        cout << "-------------------------------------" << endl;
    }

    cout << "\nJuego terminado. Puntaje total: " << puntaje << " puntos." << endl;
}

// Función para hacer una pregunta al usuario y verificar si es correcta
int hacerPregunta(int indice, string preguntas[], string opciones[][4], int respuestas[]) {
    int eleccion;
    cout << preguntas[indice] << endl;

    for (int j = 0; j < 4; j++) {
        cout << j + 1 << ". " << opciones[indice][j] << endl;
    }

    cout << "Tu respuesta (1-4): ";
    cin >> eleccion;

    // Validar la entrada del usuario
    while (eleccion < 1 || eleccion > 4) {
        cout << "Opción no válida. Intenta de nuevo: ";
        cin >> eleccion;
    }

    // Verificar si la respuesta es correcta
    return (eleccion - 1 == respuestas[indice]) ? 1 : 0;
}
