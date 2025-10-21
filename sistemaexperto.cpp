#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

/*
ANGEL EDUARDO MUÑOZ PEREZ
SISTEMA EXPERTO - ONE PIECE (9 dimensiones)
ICOM_ CUALTOS [25B]
*/

/*
COMO FUNCIONA?
Este programa actúa como un sistema experto estilo "Akinator" que intenta adivinar un personaje
de One Piece basándose en preguntas que mueven un vector del usuario dentro de un espacio de 9 dimensiones.

Cada personaje se representa como un punto (vector de 9 enteros).
Cada dimensión mide una característica, y la distancia euclidiana se usa para determinar similitud.

Dimensiones:
0 -> Rol           (0 = Pirata, 1 = Marine, 2 = Revolucionario, 3 = Civil)
1 -> Origen        (0 = Humano, 1 = Gyojin, 2 = Gigante, 3 = Tontata, 4 = Animal)
2 -> Edad          (0 - 139)
3 -> Poder         (0 = Ninguno, 1 = FrutaDelDiablo, 2 = Haki, 3 = Ambos)
4 -> Fruta         (0 = No tiene, 1 = Zoan, 2 = Logia, 3 = Paramecia)
5 -> Personalidad  (0 = Alegre, 1 = Serio, 2 = Agresivo, 3 = Tranquilo, 4 = Frío)
6 -> Bondad        (0 = Muy malo, 3 = Neutral, 6 = Muy bueno)
7 -> Motivación    (0 = Justicia/deber, 1 = Aventura/libertad, 2 = Venganza/poder,
                    3 = Protección, 4 = Sin motivación clara)
8 -> Color de pelo (0=Negro,1=Café,2=Rojo,3=Azul,4=Verde,5=Naranja,6=Rubio,7=Blanco/Gris,8=Calvo)
*/

struct Personaje {
    string nombre;
    int vector[9];
};

vector<Personaje> basePersonajes;
int usuarioVector[9] = {0,0,20,0,0,0,3,1,0}; // Inicialización por defecto

// ----------------------------------------------------------------
// ----- FUNCIONES AUXILIARES ------
// ----------------------------------------------------------------

double distanciaEuclidiana(const int a[9], const int b[9]) {
    double suma = 0;
    for (int i = 0; i < 9; i++)
        suma += pow(a[i] - b[i], 2);
    return sqrt(suma);
}

void mostrarTop3(const vector<pair<double,string>>& distancias) {
    cout << "\n?? Los 3 personajes más cercanos a tus respuestas son:\n";
    for (int i = 0; i < 3 && i < distancias.size(); i++) {
        cout << i+1 << ". " << distancias[i].second << " (distancia = " << distancias[i].first << ")\n";
    }
}

// ----------------------------------------------------------------
// ----- BASE DE DATOS DE PERSONAJES ------
// ----------------------------------------------------------------

void inicializarBase() {
    basePersonajes.reserve(120);
    /*
    Dimensiones:
	0 -> Rol           (0 = Pirata, 1 = Marine, 2 = Revolucionario, 3 = Civil)
	1 -> Origen        (0 = Humano, 1 = Gyojin, 2 = Gigante, 3 = Tontata, 4 = Animal)
	2 -> Edad          (0 - 139)
	3 -> Poder         (0 = Ninguno, 1 = FrutaDelDiablo, 2 = Haki, 3 = Ambos)
	4 -> Fruta         (0 = No tiene, 1 = Zoan, 2 = Logia, 3 = Paramecia)
	5 -> Personalidad  (0 = Alegre, 1 = Serio, 2 = Agresivo, 3 = Tranquilo, 4 = Frío, 5=miedoso)
	6 -> Bondad        (0 = Muy malo, 3 = Neutral, 6 = Muy bueno)
	7 -> Motivación    (0 = Justicia/deber, 1 = Aventura/libertad, 2 = Venganza/poder,
	                    3 = Protección, 4 = Sin motivación clara)
	8 -> Color de pelo (0=Negro,1=Café,2=Rojo,3=Azul,4=Verde,5=Naranja,6=Rubio,7=Blanco/Gris,8=Calvo,9=rosita)
    */

    basePersonajes.push_back({"Monkey D. Luffy",  {0,0,19,3,3,0,6,1,0}});
    basePersonajes.push_back({,{,,,,,,,,}});
    
    //MARINES
    basePersonajes.push_back({"Monkey D Garp",{1,0,78,2,0,0,4,0,7}});
    basePersonajes.push_back({"Sengoku"	,{1,0,79,3,1,1,5,0,7}});
    basePersonajes.push_back({"Aokiji"	,{1,0,49,2,2,4,4,0,0}});
    basePersonajes.push_back({"Akainu"	,{1,0,55,3,2,2,1,0,0}});
    basePersonajes.push_back({"Borsalino",{1,0,58,3,2,3,3,0,0}});
    basePersonajes.push_back({"Koby"	,{1,0,18,2,0,5,6,0,2}});
    basePersonajes.push_back({"Helmepo"	,{1,0,22,2,0,5,4,3,6}});
    basePersonajes.push_back({"Fujitora",{1,0,54,3,3,3,6,0,0}});
    basePersonajes.push_back({"Smoker",	{1,0,36,3,2,4,5,0,7}});
    
    //SHICHIBUKAIS
    basePersonajes.push_back({"Mihawk",	{0,0,43,2,0,1,3,4,0}});
    basePersonajes.push_back({"Crocodile",{0,0,46,3,2,4,1,2,0}});
    basePersonajes.push_back({"Kuma",	{0,0,47,3,3,3,6,3,0}});
    basePersonajes.push_back({"Boa Hanccok",{0,0,31,3,3,4,2,4,0}});
    basePersonajes.push_back({"Gecko Moria",{0,4,50,1,3,2,2,2,0}});
    basePersonajes.push_back({"Doflamingo", {0,0,41,3,3,4,0,2,6}});
    
    //YONKOS
    basePersonajes.push_back({,{,,,,,,,,}});
    basePersonajes.push_back({,{,,,,,,,,}});
    basePersonajes.push_back({,{,,,,,,,,}});
    basePersonajes.push_back({,{,,,,,,,,}});
    
    //PERSONAES SECUNDARIOS
}

// ----------------------------------------------------------------
// ----- PREGUNTAS ------
// ----------------------------------------------------------------

void hacerPreguntas() {
    int opcion = 0;

    cout << "\nBienvenido al sistema experto de One Piece ?????\n";
    cout << "Responde las siguientes preguntas para descubrir qué personaje eres.\n";

    // 1. Rol
    cout << "\n1?? ¿Qué rol tiene el personaje?\n";
    cout << "0) Pirata  1) Marine  2) Revolucionario  3) Civil\n> ";
    while(!(cin >> usuarioVector[0]) || usuarioVector[0] < 0 || usuarioVector[0] > 3){
        cout << "Opción inválida, intenta de nuevo: ";
        cin.clear(); cin.ignore(1000,'\n');
    }

    // 2. Origen
    cout << "\n2?? ¿Qué especie u origen tiene?\n";
    cout << "0) Humano  1) Gyojin  2) Gigante  3) Tontata  4) Animal\n> ";
    while(!(cin >> usuarioVector[1]) || usuarioVector[1] < 0 || usuarioVector[1] > 4){
        cout << "Opción inválida: ";
        cin.clear(); cin.ignore(1000,'\n');
    }

    // 3. Edad (nuevo sistema de rangos)
    cout << "\n3?? ¿En qué rango de edad está el personaje?\n";
    cout << "0) Niño (0-12)  1) Joven (13-25)  2) Adulto (26-50)  3) Anciano (51+)\n> ";
    while(!(cin >> opcion) || opcion < 0 || opcion > 3){cin.clear();cin.ignore(1000,'\n');}
    switch(opcion){
        case 0: usuarioVector[2] = 6; break;   // centro de 0-12
        case 1: usuarioVector[2] = 19; break;  // centro de 13-25
        case 2: usuarioVector[2] = 38; break;  // centro de 26-50
        case 3: usuarioVector[2] = 65; break;  // centro de 51+
    }

    cout << "¿Está más hacia el inicio, la mitad o el final de ese rango?\n";
    cout << "1) Inicio  2) Mitad  3) Final\n> ";
    while(!(cin >> opcion) || opcion < 1 || opcion > 3){cin.clear();cin.ignore(1000,'\n');}
    if(opcion == 1) usuarioVector[2] -= 3;
    if(opcion == 3) usuarioVector[2] += 3;

    // 4. Poder y fruta
    cout << "\n4?? ¿Qué tipo de poder tiene?\n";
    cout << "0) Ninguno  1) Fruta del Diablo  2) Haki  3) Ambos\n> ";
    while(!(cin >> usuarioVector[3]) || usuarioVector[3] < 0 || usuarioVector[3] > 3){
        cin.clear();cin.ignore(1000,'\n');
    }

    if(usuarioVector[3] == 1 || usuarioVector[3] == 3){
        cout << "¿Qué tipo de fruta tiene?\n";
        cout << "1) Zoan  2) Logia  3) Paramecia\n> ";
        while(!(cin >> usuarioVector[4]) || usuarioVector[4] < 1 || usuarioVector[4] > 3){
            cin.clear();cin.ignore(1000,'\n');
        }
    } else usuarioVector[4] = 0;

    // 5. Personalidad
    cout << "\n5?? ¿Cómo describirías su personalidad?\n";
    cout << "0) Alegre  1) Serio  2) Agresivo  3) Tranquilo  4) Frío\n> ";
    while(!(cin >> usuarioVector[5]) || usuarioVector[5] < 0 || usuarioVector[5] > 4){
        cin.clear();cin.ignore(1000,'\n');
    }

    // 6. Bondad (nuevo sistema simplificado)
    cout << "\n6?? ¿El personaje es bueno, malo o neutral?\n";
    cout << "0) Malo  1) Neutral  2) Bueno\n> ";
    while(!(cin >> opcion) || opcion < 0 || opcion > 2){cin.clear();cin.ignore(1000,'\n');}
    switch(opcion){
        case 0: usuarioVector[6] = 1; break;
        case 1: usuarioVector[6] = 3; break;
        case 2: usuarioVector[6] = 5; break;
    }

    cout << "¿Tiende a ser más cruel o más heroico?\n";
    cout << "1) Más cruel  2) Neutro  3) Más heroico\n> ";
    while(!(cin >> opcion) || opcion < 1 || opcion > 3){cin.clear();cin.ignore(1000,'\n');}
    if(opcion == 1 && usuarioVector[6] > 0) usuarioVector[6] -= 1;
    if(opcion == 3 && usuarioVector[6] < 6) usuarioVector[6] += 1;

    // 7. Motivación
    cout << "\n7?? ¿Qué lo motiva principalmente?\n";
    cout << "0) Justicia/deber  1) Aventura/libertad  2) Venganza/poder  3) Protección  4) Sin motivación clara\n> ";
    while(!(cin >> usuarioVector[7]) || usuarioVector[7] < 0 || usuarioVector[7] > 4){
        cin.clear();cin.ignore(1000,'\n');
    }

    // 8. Color de pelo
    cout << "\n8?? ¿De qué color es su cabello?\n";
    cout << "0) Negro 1) Café 2) Rojo 3) Azul 4) Verde 5) Naranja 6) Rubio 7) Blanco/Gris 8) Calvo\n> ";
    while(!(cin >> usuarioVector[8]) || usuarioVector[8] < 0 || usuarioVector[8] > 8){
        cin.clear();cin.ignore(1000,'\n');
    }

    // 9. Pregunta aleatoria (se mantiene igual)
    srand(time(0));
    int aleatoria = rand() % 3;
    switch(aleatoria){
        case 0:
            cout << "\n?? Pregunta extra: ¿Su poder es más físico o sobrenatural?\n";
            cout << "1) Físico  2) Sobrenatural\n> ";
            cin >> opcion;
            if(opcion == 1 && usuarioVector[3] > 0) usuarioVector[3] -= 1;
            if(opcion == 2 && usuarioVector[3] < 3) usuarioVector[3] += 1;
            break;
        case 1:
            cout << "\n?? Pregunta extra: ¿El personaje ha mostrado actos heroicos?\n";
            cout << "1) Sí  2) No\n> ";
            cin >> opcion;
            if(opcion == 1 && usuarioVector[6] < 6) usuarioVector[6] += 1;
            if(opcion == 2 && usuarioVector[6] > 0) usuarioVector[6] -= 1;
            break;
        case 2:
            cout << "\n?? Pregunta extra: ¿Qué tan tranquilo suele ser?\n";
            cout << "1) Muy impulsivo  2) Normal  3) Muy tranquilo\n> ";
            cin >> opcion;
            if(opcion == 1 && usuarioVector[5] != 2) usuarioVector[5] = 2;
            if(opcion == 3 && usuarioVector[5] != 3) usuarioVector[5] = 3;
            break;
    }
}

// ----------------------------------------------------------------
// ----- MAIN -----
// ----------------------------------------------------------------

int main() {
    inicializarBase();
    hacerPreguntas();

    // Calcular distancias
    vector<pair<double,string>> distancias;
    for (auto& p : basePersonajes) {
        double d = distanciaEuclidiana(usuarioVector, p.vector);
        distancias.push_back({d, p.nombre});
    }

    // Ordenar
    sort(distancias.begin(), distancias.end(),
    [](const pair<double,string>& a, const pair<double,string>& b) {
        return a.first < b.first;
	    }
	);


    mostrarTop3(distancias);

    cout << "\nGracias por jugar al sistema experto de One Piece ?\n";
    return 0;
}


