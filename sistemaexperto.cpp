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
	Para hacer esto utilizaremos un número de preguntas y una forma de representar las características
	de cada personaje en un espacio vectorial de varias dimensiones. Cada eje o dimensión representa
	una cualidad que se puede medir de forma discreta o no discreta.

	Dimensiones utilizadas:
	1. Rol (0 = Pirata, 1 = Marine, 2 = Revolucionario, 3 = Civil/Otro)
	2. Edad (0 - 139)
	3. Poder (0 = Ninguno, 1 = Paramecia, 2 = Zoan, 3 = Logia)
	4. Tripulación u organización (índices predefinidos)
	5. Personalidad (0 = Alegre, 1 = Serio, 2 = Agresivo, 3 = Tranquilo, 4 = Frío)
	6. Bondad (0 = muy malo, 3 = neutral, 6 = muy bueno)

	El usuario, a través de respuestas, construye su propio vector de posición.
	Se calcula la distancia euclidiana entre la posición del usuario y cada personaje.
	El personaje más cercano se considera la mejor predicción.
*/

/// Estructura que representa un personaje como un punto en 6D
struct Personaje {
    string nombre;
    int vector[6];
};

/// Base de datos estática de personajes
vector<Personaje> basePersonajes;

/// Vector que representa la posición del usuario
int usuarioVector[6] = {0,0,0,0,0,3}; // Inicializamos la dimensión de bondad en 3

/// Inicializa la base con 100 personajes de One Piece con coordenadas predefinidas
void inicializarBase() {
    basePersonajes.reserve(100);
	//{Rol, Edad, Poder, Tripulación, Personalidad, Bondad}

    // Piratas Sombrero de Paja
    basePersonajes.push_back({"Monkey D. Luffy", {0, 19, 1, 0, 0, 6}});
    basePersonajes.push_back({"Roronoa Zoro", {0, 21, 0, 0, 1, 5}});
    basePersonajes.push_back({"Nami", {0, 20, 0, 0, 0, 6}});
    basePersonajes.push_back({"Usopp", {0, 19, 0, 0, 0, 6}});
    basePersonajes.push_back({"Sanji", {0, 21, 0, 0, 2, 6}});
    basePersonajes.push_back({"Tony Tony Chopper", {0, 17, 2, 0, 0, 6}});
    basePersonajes.push_back({"Nico Robin", {0, 30, 0, 0, 1, 4}});
    basePersonajes.push_back({"Franky", {0, 36, 0, 0, 0, 5}});
    basePersonajes.push_back({"Brook", {0, 90, 0, 0, 0, 6}});
    basePersonajes.push_back({"Jinbe", {0, 46, 0, 0, 1, 6}});

    // Marina (ejemplo)
    basePersonajes.push_back({"Sakazuki (Akainu)", {1, 55, 1, 1, 2, 1}});
    basePersonajes.push_back({"Borsalino (Kizaru)", {1, 58, 3, 1, 3, 3}});
    basePersonajes.push_back({"Kuzan (Aokiji)", {1, 49, 3, 1, 3, 5}});
    basePersonajes.push_back({"Garp", {1, 78, 0, 1, 0, 6}});
    basePersonajes.push_back({"Smoker", {1, 36, 3, 1, 2, 4}});
    basePersonajes.push_back({"Tashigi", {1, 23, 0, 1, 1, 5}});
    basePersonajes.push_back({"Koby", {1, 18, 0, 1, 0, 6}});
    basePersonajes.push_back({"Helmeppo", {1, 20, 0, 1, 0, 4}});
    basePersonajes.push_back({"Sengoku", {1, 79, 0, 1, 1, 5}});
    basePersonajes.push_back({"Tsuru", {1, 74, 0, 1, 1, 5}});

    
    
}

/// Realiza preguntas que afectan el vector del usuario
void hacerPreguntas() {
    cout << "Bienvenido al Sistema Experto de One Piece!" << endl;
    cout << "Responde a las siguientes preguntas para adivinar el personaje que piensas.\n\n";

    /// Pregunta sobre Rol
    cout << "1. Rol: (0=Pirata, 1=Marine, 2=Revolucionario, 3=Civil/Otro): ";
    cin >> usuarioVector[0];

    /// Preguntas sobre Edad (en rangos)
    bool mayor20 = false, menor60 = false;
    char r;
    cout << "2. Tu personaje es mayor de 20 años? (s/n): ";
    cin >> r;
    if (r == 's' || r == 'S') mayor20 = true;

    cout << "3. Tu personaje es menor de 60 años? (s/n): ";
    cin >> r;
    if (r == 's' || r == 'S') menor60 = true;

    if (!mayor20 && menor60) usuarioVector[1] = 15;         // Joven
    else if (mayor20 && menor60) usuarioVector[1] = 40;     // Adulto
    else if (mayor20 && !menor60) usuarioVector[1] = 70;    // Anciano
    else usuarioVector[1] = 25;                             // Valor por defecto

    /// Pregunta sobre Poder
    cout << "4. Poder (0=Ninguno, 1=Paramecia, 2=Zoan, 3=Logia): ";
    cin >> usuarioVector[2];

    /// Pregunta sobre Tripulación
    cout << "5. Tripulación (0=Sombrero de paja, 1=Marina, 2=Revolucionarios, 3=Shanks, ... etc): ";
    cin >> usuarioVector[3];

    /// Pregunta sobre Personalidad
    cout << "6. Personalidad (0=Alegre, 1=Serio, 2=Agresivo, 3=Tranquilo, 4=Frío): ";
    cin >> usuarioVector[4];

    /// Preguntas sobre Bondad
    cout << "7. Consideras que tu personaje es bueno o malo? (b=bueno, m=malo, n=neutral): ";
    cin >> r;
    if (r == 'b' || r == 'B') usuarioVector[5] += 2;
    else if (r == 'm' || r == 'M') usuarioVector[5] -= 2;

    cout << "8. Ha matado o robado a alguien? (s/n): ";
    cin >> r;
    if (r == 's' || r == 'S') usuarioVector[5] -= 1;
    else usuarioVector[5] += 1;

    if (usuarioVector[5] < 0) usuarioVector[5] = 0;
    if (usuarioVector[5] > 6) usuarioVector[5] = 6;
}

/// Calcula la distancia euclidiana entre el vector del usuario y el de un personaje
double calcularDistancia(const int v1[6], const int v2[6]) {
    double suma = 0;
    for (int i = 0; i < 6; i++) {
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
    color(2); cout << resultado.nombre << endl;

    return 0;
}

