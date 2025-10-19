#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "colores.cpp"
using namespace std;

/*
ANGEL EDUARDO MUÑOZ PEREZ come 8=D
SISTEMA EXPERTO
ICOM_ CUALTOS[25B]
*/

/*
COMO FUNCIONA?
	Este programa intenta replicar un sistema inteligente actuando como un Akinator de personajes de One Piece.
	Para hacer esto utilizaremos un numero de preguntas y una forma de representar las caracteristicas
		de cada personaje en un espacio vectorial de varias dimensiones, cada personajes estar dentro de una 
		estrcutura de n dimensiones representadas en arreglos, cada eje o dimension representara una cualidad
		que se puede medir de forma discreta o no discreta, por ejemplo, un vector de rol para distinguir dependiendo
		de su pocision si es pirata o si es marin, otro vector para distinguir su edad dependiendo de su pocision en 
		el mismo y las propias preguntas loq ue haran seran que desde el punto de origen, dependiendo de la pregunta
		dezplazar la pocision del puntero dentro de este espacio de n dimensiones hacia la direccion y magnitud 
		correspondiente dependiendo de la pregunta. Cuando se decide que se tomo una decision para adivinar el perso
		naje, soltara el nombre del personaje que este en la pocision acutal, o en su defecto, el mas cercano utilizando
		una compociosion de hipotenusas sobre el espacio
*/

/*
FUNCIONAMIENTO GENERAL:
    - Este sistema intenta adivinar un personaje de One Piece a partir de 5 características fundamentales:
        1. Rol
        2. Edad
        3. Poder
        4. Tripulación u organización
        5. Personalidad
    - Cada personaje es un punto dentro de un espacio de 5 dimensiones.
    - El usuario, a través de respuestas, construye su propio vector de posición.
    - Se calcula la distancia euclidiana entre la posición del usuario y cada personaje.
    - El personaje más cercano se considera la mejor predicción.
*/

/// Estructura que representa un personaje como un punto en 5D
struct Personaje {
    string nombre;
    int vector[5];
};

/// Base de datos estática de personajes
vector<Personaje> basePersonajes;

/// Vector que representa la posición del usuario
int usuarioVector[5] = {0,0,0,0,0};//{rol, Edad, Poder, Tripulacion, Personalidad}

/// Inicializa la base con 100 personajes de One Piece con coordenadas predefinidas
void inicializarBase() {
    basePersonajes.reserve(100);
	//{rol, Edad, Poder, Tripulacion, Personalidad}
    // Piratas Sombrero de Paja
    basePersonajes.push_back({"Monkey D. Luffy", {0, 19, 1, 0, 0}});
    basePersonajes.push_back({"Roronoa Zoro", {0, 21, 0, 0, 1}});
    basePersonajes.push_back({"Nami", {0, 20, 0, 0, 0}});
    basePersonajes.push_back({"Usopp", {0, 19, 0, 0, 0}});
    basePersonajes.push_back({"Sanji", {0, 21, 0, 0, 2}});
    basePersonajes.push_back({"Tony Tony Chopper", {0, 17, 2, 0, 0}});
    basePersonajes.push_back({"Nico Robin", {0, 30, 0, 0, 1}});
    basePersonajes.push_back({"Franky", {0, 36, 0, 0, 0}});
    basePersonajes.push_back({"Brook", {0, 90, 0, 0, 0}});
    basePersonajes.push_back({"Jinbe", {0, 46, 0, 0, 1}});

    // Marina
    basePersonajes.push_back({"Sakazuki (Akainu)", {1, 55, 1, 1, 2}});
    basePersonajes.push_back({"Borsalino (Kizaru)", {1, 58, 3, 1, 3}});
    basePersonajes.push_back({"Kuzan (Aokiji)", {1, 49, 3, 1, 3}});
    basePersonajes.push_back({"Garp", {1, 78, 0, 1, 0}});
    basePersonajes.push_back({"Smoker", {1, 36, 3, 1, 2}});
    basePersonajes.push_back({"Tashigi", {1, 23, 0, 1, 1}});
    basePersonajes.push_back({"Koby", {1, 18, 0, 1, 0}});
    basePersonajes.push_back({"Helmeppo", {1, 20, 0, 1, 0}});
    basePersonajes.push_back({"Sengoku", {1, 79, 0, 1, 1}});
    basePersonajes.push_back({"Tsuru", {1, 74, 0, 1, 1}});

    // Revolucionarios
    basePersonajes.push_back({"Monkey D. Dragon", {2, 50, 0, 2, 1}});
    basePersonajes.push_back({"Sabo", {2, 22, 1, 2, 0}});
    basePersonajes.push_back({"Ivankov", {2, 53, 1, 2, 0}});
    basePersonajes.push_back({"Belo Betty", {2, 31, 1, 2, 0}});
    basePersonajes.push_back({"Karasu", {2, 39, 1, 2, 1}});
    basePersonajes.push_back({"Lindbergh", {2, 36, 0, 2, 0}});
    basePersonajes.push_back({"Morley", {2, 160, 2, 2, 0}});
    basePersonajes.push_back({"Koala", {2, 23, 0, 2, 0}});

    // Yonkou y tripulaciones importantes
    basePersonajes.push_back({"Shanks", {0, 39, 0, 3, 0}});
    basePersonajes.push_back({"Marshall D. Teach", {0, 40, 1, 4, 2}});
    basePersonajes.push_back({"Edward Newgate", {0, 72, 1, 5, 3}});
    basePersonajes.push_back({"Charlotte Linlin", {0, 68, 1, 6, 2}});
    basePersonajes.push_back({"Kaido", {0, 59, 2, 7, 2}});
    basePersonajes.push_back({"Marco", {0, 45, 2, 5, 3}});
    basePersonajes.push_back({"King", {0, 47, 2, 7, 1}});
    basePersonajes.push_back({"Katakuri", {0, 48, 1, 6, 1}});
    basePersonajes.push_back({"Perospero", {0, 50, 1, 6, 0}});
    basePersonajes.push_back({"Queen", {0, 56, 2, 7, 0}});
    basePersonajes.push_back({"Jack", {0, 28, 2, 7, 2}});

    // Shichibukai / ex Shichibukai
    basePersonajes.push_back({"Dracule Mihawk", {0, 43, 0, 8, 1}});
    basePersonajes.push_back({"Boa Hancock", {0, 31, 1, 9, 0}});
    basePersonajes.push_back({"Bartholomew Kuma", {2, 47, 1, 2, 1}});
    basePersonajes.push_back({"Buggy", {0, 39, 1, 10, 0}});
    basePersonajes.push_back({"Crocodile", {0, 46, 1, 11, 1}});
    basePersonajes.push_back({"Jinbe", {0, 46, 0, 0, 1}});
    basePersonajes.push_back({"Doflamingo", {0, 41, 1, 12, 2}});
    basePersonajes.push_back({"Law", {0, 26, 1, 13, 1}});
    basePersonajes.push_back({"Weevil", {0, 35, 2, 14, 2}});

    // CP0 / Gobierno
    basePersonajes.push_back({"Rob Lucci", {3, 30, 2, 15, 1}});
    basePersonajes.push_back({"Spandam", {3, 41, 0, 15, 1}});
    basePersonajes.push_back({"Kaku", {3, 25, 2, 15, 0}});
    basePersonajes.push_back({"Stussy", {3, 40, 0, 15, 1}});

    // Civiles / otros
    basePersonajes.push_back({"Makino", {3, 31, 0, 16, 3}});
    basePersonajes.push_back({"Higuma", {3, 45, 0, 16, 2}});
    basePersonajes.push_back({"Kaya", {3, 17, 0, 16, 3}});
    basePersonajes.push_back({"Laboon", {3, 80, 0, 16, 0}});
    basePersonajes.push_back({"Iceburg", {3, 38, 0, 16, 1}});
    basePersonajes.push_back({"Tom", {3, 70, 0, 16, 0}});

    // Supernovas adicionales (para llegar a 100 aprox.)
    basePersonajes.push_back({"Eustass Kid", {0, 23, 1, 17, 2}});
    basePersonajes.push_back({"Killer", {0, 25, 0, 17, 1}});
    basePersonajes.push_back({"Capone Bege", {0, 40, 1, 18, 0}});
    basePersonajes.push_back({"Basil Hawkins", {0, 31, 1, 19, 3}});
    basePersonajes.push_back({"X Drake", {0, 33, 2, 20, 1}});
    basePersonajes.push_back({"Scratchmen Apoo", {0, 31, 1, 21, 0}});
    basePersonajes.push_back({"Urouge", {0, 47, 0, 22, 3}});
    basePersonajes.push_back({"Bonney", {0, 24, 1, 23, 0}});

    // Tripulación de Roger
    basePersonajes.push_back({"Gol D. Roger", {0, 53, 0, 24, 0}});
    basePersonajes.push_back({"Silvers Rayleigh", {0, 78, 0, 24, 1}});
    basePersonajes.push_back({"Scopper Gaban", {0, 50, 0, 24, 0}});
    basePersonajes.push_back({"Shanks (joven)", {0, 15, 0, 24, 0}});
    basePersonajes.push_back({"Buggy (joven)", {0, 15, 0, 24, 0}});
}

/// Realiza preguntas que afectan el vector del usuario
void hacerPreguntas() {
    cout << "Bienvenido al Sistema Experto de One Piece!" << endl;
    cout << "Responde a las siguientes preguntas para adivinar el personaje que piensas.\n\n";

    cout << "1. Rol: (0=Pirata, 1=Marine, 2=Revolucionario, 3=Civil/Otro): ";
    cin >> usuarioVector[0];

    cout << "2. Edad aproximada (entre 0 y 139): ";
    cin >> usuarioVector[1];
    if(usuarioVector[1] < 0) usuarioVector[1] = 0;
    if(usuarioVector[1] > 139) usuarioVector[1] = 139;

    cout << "3. Poder (0=Ninguno, 1=Paramecia, 2=Zoan, 3=Logia): ";
    cin >> usuarioVector[2];

    cout << "4. Tripulación (0=Sombrero de paja, 1=Marina, 2=Revolucionarios, 3=Shanks, ... etc): ";
    cin >> usuarioVector[3];

    cout << "5. Personalidad (0=Alegre, 1=Serio, 2=Agresivo, 3=Tranquilo, 4=Frío): ";
    cin >> usuarioVector[4];
}

/// Calcula la distancia euclidiana entre el vector del usuario y el de un personaje
double calcularDistancia(const int v1[5], const int v2[5]) {
    double suma = 0;
    for (int i = 0; i < 5; i++) {
        double d = v1[i] - v2[i];
        suma += d * d;
    }
    return sqrt(suma);
}

/// Busca el personaje más cercano
Personaje encontrarMasCercano() {
    double mejorDistancia = 1e9;
    Personaje mejor = basePersonajes[0];

    for (const auto &p : basePersonajes) {
        double dist = calcularDistancia(usuarioVector, p.vector);
        if (dist < mejorDistancia) {
            mejorDistancia = dist;
            mejor = p;
        }
    }
    return mejor;
}

int main() {
    inicializarBase();
    hacerPreguntas();
    Personaje resultado = encontrarMasCercano();

    cout << "\nEl personaje que más coincide con tus respuestas es: ";
    color(2);cout  << resultado.nombre << endl;

    return 0;
}

