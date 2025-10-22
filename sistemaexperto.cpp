#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "colores.cpp"
using namespace std;

/*
ANGEL EDUARDO MUÑOZ PEREZ
SISTEMA EXPERTO - ONE PIECE (9 dimensiones)
ICOM_ CUALTOS [25B]
*/

/*
COMO FUNCIONA?
Este programa actua como un sistema experto estilo "Akinator" que intenta adivinar un personaje
de One Piece basandose en preguntas que mueven un vector del usuario dentro de un espacio de 9 dimensiones.

Cada personaje se representa como un punto (vector de 9 enteros).
Cada dimension mide una caracteristica, y la distancia euclidiana se usa para determinar similitud.

Dimensiones:
0 -> Rol           (0 = Pirata, 1 = Marine, 2 = Revolucionario, 3 = Civil)
1 -> Origen        (0 = Humano, 1 = Gyojin, 2 = Gigante, 3 = Tontata, 4 = Animal)
2 -> Edad          (0 - 139)
3 -> Poder         (0 = Ninguno, 1 = FrutaDelDiablo, 2 = Haki, 3 = Ambos)
4 -> Fruta         (0 = No tiene, 1 = Zoan, 2 = Logia, 3 = Paramecia)
5 -> Personalidad  (0 = Alegre, 1 = Serio, 2 = Agresivo, 3 = Tranquilo, 4 = Frio)
6 -> Bondad        (0 = Muy malo, 3 = Neutral, 6 = Muy bueno)
7 -> Motivacion    (0 = Justicia/deber, 1 = Aventura/libertad, 2 = Venganza/poder,
                    3 = Proteccion, 4 = Sin motivacion clara)
8 -> Color de pelo (0=Negro,1=Cafe,2=Rojo/Rosa,3=Azul,4=Verde,5=Naranja,6=Rubio,7=Blanco/Gris,8=Calvo)
*/

struct Personaje {
    string nombre;
    int vector[9];
};

vector<Personaje> basePersonajes;
int usuarioVector[9] = {0,0,20,0,0,0,3,1,0}; // Inicializacion por defecto

// ----------------------------------------------------------------
// ----- FUNCIONES AUXILIARES ------
// ----------------------------------------------------------------

double distanciaEuclidiana(const int a[9], const int b[9]) {
    double suma = 0;
    for (int i = 0; i < 9; i++) {
        double peso = 1.0; // peso normal
        //  Dar mucha mas importancia al ROL (dimension 0)
        if (i == 0) peso = 100.0;  // puedes ajustar este numero
        suma += pow((a[i] - b[i]) * peso, 2);
    }
    return sqrt(suma);
}

void mostrarTop3(const vector<pair<double,string>>& distancias) {
    gotoxy(1,8);color(14);cout << "?? Los 3 personajes mas cercanos a tus respuestas son:\n";
    for (int i = 0; i < 3 && i < distancias.size(); i++) {
        gotoxy(1,9+i);color(7);cout << i+1 << ". " << distancias[i].second << " (distancia = " << distancias[i].first << ")\n";
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
	5 -> Personalidad  (0 = Alegre, 1 = Serio, 2 = Agresivo, 3 = Tranquilo, 4 = Frio, 5=miedoso)
	6 -> Bondad        (0 = Muy malo, 3 = Neutral, 6 = Muy bueno)
	7 -> Motivacion    (0 = Justicia/deber, 1 = Aventura/libertad, 2 = Venganza/poder,
	                    3 = Proteccion, 4 = Sin motivacion clara)
	8 -> Color de pelo (0=Negro,1=Cafe,2=Rojo/Rosa,3=Azul,4=Verde,5=Naranja,6=Rubio,7=Blanco/Gris,8=Calvo)
    */

    //SOMBREROS DE PAJA
    basePersonajes.push_back({"Monkey D. Luffy",{0,0,19,3,3,0,5,1,0}});
    basePersonajes.push_back({"Zoro",			{0,0,21,2,0,1,5,0,4}});
    basePersonajes.push_back({"Ussop",			{0,0,19,2,0,5,5,1,0}});
    basePersonajes.push_back({"Nami",			{0,0,20,0,0,2,5,1,5}});
    basePersonajes.push_back({"Sanji",			{0,0,21,2,0,1,6,2,6}}); //Su motivacion es un intermedio entre Aventura/Libertad y Proteccion
    basePersonajes.push_back({"Tony Tony Chopper",{0,4,17,1,1,5,6,3,1}});
    basePersonajes.push_back({"Franky",			{0,0,37,0,0,0,6,1,3}});
    basePersonajes.push_back({"Brook",			{0,0,90,1,3,0,6,1,0}});
    basePersonajes.push_back({"Jimbe",			{0,1,46,2,0,3,6,0,0}});
    
    //MARINES
    basePersonajes.push_back({"Monkey D Garp",	{1,0,78,2,0,0,4,0,7}});
    basePersonajes.push_back({"Sengoku"	,		{1,0,79,3,1,1,5,0,7}});
    basePersonajes.push_back({"Aokiji"	,		{1,0,49,2,2,4,4,0,0}});
    basePersonajes.push_back({"Akainu"	,		{1,0,55,3,2,2,1,0,0}});
    basePersonajes.push_back({"Borsalino",		{1,0,58,3,2,3,3,0,0}});
    basePersonajes.push_back({"Koby"	,		{1,0,18,2,0,5,6,0,2}});
    basePersonajes.push_back({"Helmepo"	,		{1,0,22,2,0,5,4,3,6}});
    basePersonajes.push_back({"Fujitora",		{1,0,54,3,3,3,6,0,0}});
    basePersonajes.push_back({"Smoker",			{1,0,36,3,2,4,5,0,7}});
    
    //SHICHIBUKAIS
    basePersonajes.push_back({"Mihawk",		{0,0,43,2,0,1,3,4,0}});
    basePersonajes.push_back({"Crocodile",	{0,0,46,3,2,4,1,2,0}});
    basePersonajes.push_back({"Kuma",		{0,0,47,3,3,3,6,3,0}});
    basePersonajes.push_back({"Boa Hanccok",{0,0,31,3,3,4,2,4,0}});
    basePersonajes.push_back({"Gecko Moria",{0,4,50,1,3,2,2,2,0}});
    basePersonajes.push_back({"Doflamingo", {0,0,41,3,3,4,0,2,6}});
		
    //REVOLUCIONARIOS
    basePersonajes.push_back({"Monkey D. Dragon",{2,0,55,1,3,1,5,0,0}});
    basePersonajes.push_back({"Ivankov",		{2,0,53,1,3,0,5,3,3}});
    basePersonajes.push_back({"Sabo",			{2,0,22,3,2,3,5,0,6}});
		
    //YONKOS
    basePersonajes.push_back({"Shanks",		{0,0,39,2,0,0,5,4,2}});
    basePersonajes.push_back({"Barba Blanca",{0,0,72,3,3,2,5,3,7}});
    basePersonajes.push_back({"Marco",		{0,0,45,3,1,3,4,4,6}});
    basePersonajes.push_back({"Portgas D. Ace",{0,0,20,3,2,0,4,1,0}});
    basePersonajes.push_back({"Big mom"		,{0,0,68,3,3,2,2,2,2}});
    basePersonajes.push_back({"Katakuri",	{0,0,48,3,3,4,4,4,2}});
    basePersonajes.push_back({"Kaido",		{0,0,59,3,1,4,2,2,0}});
   	basePersonajes.push_back({"Barba Negra",{0,0,40,3,2,0,0,2,0}});
	basePersonajes.push_back({"Buggy",		{0,0,39,1,3,5,3,2,3}});    
    
	//PERSONAES SECUNDARIOS
    	//eastblue
	basePersonajes.push_back({"Shushu",		{3,4,14,0,0,2,4,3,7}});
    basePersonajes.push_back({"Arlong",		{0,1,41,0,0,2,0,2,0}});
    basePersonajes.push_back({"Kaya",		{3,0,19,0,0,3,5,4,6}});
    basePersonajes.push_back({"Jhonny y Yosaku",{3,0,23,0,0,0,5,1,0}});
    basePersonajes.push_back({"Zeff",		{3,0,43,0,0,2,5,4,6}});
    	//alabasta
    basePersonajes.push_back({"Laboon",		{3,4,0,0,0,4,3,3,8}});
    basePersonajes.push_back({"Vivi",		{3,0,18,0,0,0,6,0,3}});
    basePersonajes.push_back({"Dorry y Broggy",{3,2,139,0,0,0,5,1,1}});
    basePersonajes.push_back({"Hiruluk",	{3,0,68,0,0,0,5,3,7}});
    basePersonajes.push_back({"MR. 2",		{0,0,32,1,3,0,5,3,0}});
    basePersonajes.push_back({"Karoo",		{3,4,17,0,0,0,6,3,6}});
    	//skypea
    basePersonajes.push_back({"Bellamy",	{0,0,27,1,3,2,2,2,6}});
    basePersonajes.push_back({"Enel",		{3,0,39,3,2,4,0,2,6}});
    basePersonajes.push_back({"Noland",		{3,0,39,0,0,0,6,3,1}});
    basePersonajes.push_back({"Kalgara",	{3,0,38,0,0,2,5,3,2}});
    	//water7
    basePersonajes.push_back({"Foxy",		{0,0,31,1,3,5,2,4,0}});
    basePersonajes.push_back({"Lucci",		{3,0,26,3,1,2,1,2,0}});
    basePersonajes.push_back({"Kaku",		{3,0,25,3,1,3,3,4,1}});
    basePersonajes.push_back({"Iceberg",	{3,0,34,0,0,3,4,0,3}});
    basePersonajes.push_back({"Paulie",		{3,0,22,0,0,0,3,4,6}});
    	//thriller bark
    basePersonajes.push_back({"Perona",		{3,0,25,1,3,4,3,4,2}});
    basePersonajes.push_back({"Dr Hogback",	{3,0,35,0,0,4,1,4,3}});
    	//sabaody/marineford
    basePersonajes.push_back({"Kid",		{0,0,23,3,3,2,3,1,2}});
    basePersonajes.push_back({"Trafalgar water D. Law",{0,0,24,3,3,4,4,0,0}});
    basePersonajes.push_back({"Bonney",		{0,0,12,1,3,2,3,1,3}});
    basePersonajes.push_back({"Magellan",	{0,0,47,1,2,1,4,0,0}});
    basePersonajes.push_back({"Duval",		{0,0,30,0,0,0,4,4,6}});
    basePersonajes.push_back({"Sentomaru",	{1,0,34,2,0,1,3,0,0}});
    	//fishman island
    basePersonajes.push_back({"Camie",		{3,1,18,0,0,0,4,4,4}});
    basePersonajes.push_back({"Hachi",		{3,0,36,0,0,3,5,3,7}});
    basePersonajes.push_back({"Hody Jones",	{3,0,30,0,0,2,1,2,0}});
    basePersonajes.push_back({"Fisher Tiger",{3,0,48,0,0,1,5,0,0}});
    basePersonajes.push_back({"Shirahoshi",	{3,3,18,0,0,5,4,1,2}});
		//dressrosa	
     basePersonajes.push_back({"Vergo",		{1,0,45,3,1,1,2,0,0}});
    basePersonajes.push_back({"MR Pink",	{0,0,40,0,0,0,3,3,1}}); 
    basePersonajes.push_back({"Tontatas",	{3,3,20,0,0,0,6,3,5}}); 
    basePersonajes.push_back({"Hajrudin",	{0,2,81,2,0,1,5,1,6}});

    	//whole cake
    basePersonajes.push_back({"Puding",		{3,0,16,1,3,3,4,3,5}}); 
    basePersonajes.push_back({"Vinsmoke Judge",{3,0,56,3,1,4,1,2,6}}); 
    basePersonajes.push_back({"Reiju Vinsmoke",{3,0,24,1,3,3,5,3,2}}); 
    	//wano
    basePersonajes.push_back({"Kin'emon",	{0,0,36,2,0,1,5,3,0}}); 
    basePersonajes.push_back({"Kanjuro",	{0,0,39,2,0,4,0,2,0}}); 
    basePersonajes.push_back({"Yamato",		{0,0,28,2,0,0,6,1,6}}); 
    basePersonajes.push_back({"Oden Kozuki",	{0,0,39,2,0,0,6,1,0}}); 
    	//egghead
    basePersonajes.push_back({"Vegapunk",	{1,0,65,0,0,3,5,0,7}});
}

// ----------------------------------------------------------------
// ----- PREGUNTAS ------
// ----------------------------------------------------------------

void hacerPreguntas() {
    int opcion = 0;

    gotoxy(1,1);color(1);cout << "        Bienvenido al sistema experto de One Piece ?????";
    gotoxy(1,2);color(1);cout << "Responde las siguientes preguntas para descubrir que personaje eres.";
	gotoxy(1,3);color(1);cout << " =================================================================";
    // 1. Rol
    
    gotoxy(1,5);color(2);cout << "1?? Que rol tiene el personaje?                             ";
    gotoxy(1,6);color(10);cout<< "[0] Pirata  [1] Marine  [2] Revolucionario  [3] Civil      ";gotoxy(1,7);color(15);
    while(!(cin >> usuarioVector[0]) || usuarioVector[0] < 0 || usuarioVector[0] > 3){
        color(13);cout << "Opcion invalida, intenta de nuevo: ";
        cin.clear(); cin.ignore(1000,'\n');
    }
																											gotoxy(1,7);cout<<"      ";
    // 2. Origen
    system("cls");

    gotoxy(1,5);color(2);cout << "2?? Que especie u origen tiene?                                                ";
    gotoxy(1,6);color(10);cout<< "[0] Humano  [1] Gyojin  [2] Gigante  [3] Tontata  [4] Animal ";gotoxy(1,7);color(15);
    while(!(cin >> usuarioVector[1]) || usuarioVector[1] < 0 || usuarioVector[1] > 4){
        color(13);cout << "Opcion invalida: ";
        cin.clear(); cin.ignore(1000,'\n');
    }
																											gotoxy(1,7);cout<<"      ";
    // 3. Edad 
    system("cls");

	gotoxy(1,5);color(2);cout << "3?? Que edad tiene aproximadamente el personaje?          ";
	gotoxy(1,6);color(10);cout<< "(Ingresa un numero entre 0 y 139)                            ";gotoxy(1,7);color(15);
	while (!(cin >> opcion) || opcion < 0 || opcion > 139) {
	    color(13);cout << "Edad invalida, intenta de nuevo: ";
	    cin.clear(); cin.ignore(1000, '\n');
	}
	usuarioVector[2] = opcion;
																											gotoxy(1,7);cout<<"      ";
    // 4. Poder y fruta		
    system("cls");

    gotoxy(1,5);color(2);cout << "4?? Que tipo de poder tiene?                                ";
    gotoxy(1,6);color(10);cout <<"[0] Ninguno  [1] Fruta del Diablo  [2] Haki  [3] Ambos       ";gotoxy(1,7);color(15);
    while(!(cin >> usuarioVector[3]) || usuarioVector[3] < 0 || usuarioVector[3] > 3){
        cin.clear();cin.ignore(1000,'\n');
    }
																											gotoxy(1,7);cout<<"      ";
    if(usuarioVector[3] == 1 || usuarioVector[3] == 3){
        system("cls");

		gotoxy(1,5);color(2);cout <<  "Que tipo de fruta tiene?                                    ";
        gotoxy(1,6);color(10);cout<< "[1] Zoan  [2] Logia  [3] Paramecia\n>                        ";gotoxy(1,7);color(15);
        while(!(cin >> usuarioVector[4]) || usuarioVector[4] < 1 || usuarioVector[4] > 3){
            cin.clear();cin.ignore(1000,'\n');
        }
    } else usuarioVector[4] = 0;
																											gotoxy(1,7);cout<<"      ";
    // 5. Personalidad
    system("cls");

    gotoxy(1,5);color(2);cout << "5?? Como describirias su personalidad?                      ";
    gotoxy(1,6);color(10);cout<< "[0] Alegre  [1] Serio  [2] Agresivo  [3] Tranquilo  [4] Frio [5] Miedoso ";gotoxy(1,7);color(15);
    while(!(cin >> usuarioVector[5]) || usuarioVector[5] < 0 || usuarioVector[5] > 5){
        cin.clear();cin.ignore(1000,'\n');
    }
																											gotoxy(1,7);cout<<"      ";
    // 6. Bondad (nuevo sistema simplificado)
    system("cls");

    gotoxy(1,5);color(2);cout << "6?? El personaje es bueno, malo o neutral?                                     ";
    gotoxy(1,6);color(10);cout<< "[0] Malo  [1] Neutral  [2] Bueno                                               ";gotoxy(1,7);color(15);
    while(!(cin >> opcion) || opcion < 0 || opcion > 2){cin.clear();cin.ignore(1000,'\n');}
    switch(opcion){
        case 0: usuarioVector[6] = 1; break;
        case 1: usuarioVector[6] = 3; break;
        case 2: usuarioVector[6] = 5; break;
    }
	system("cls");
																										gotoxy(1,7);cout<<"      ";
   	gotoxy(1,5);color(2);cout << "Tiende a ser mas cruel o mas heroico?                                                          ";
    gotoxy(1,6);color(10);cout<< "[1] Mas cruel  [2] Neutro  [3] Mas heroico                                                    ";gotoxy(1,7);color(15);
    while(!(cin >> opcion) || opcion < 1 || opcion > 3){cin.clear();cin.ignore(1000,'\n');}
    if(opcion == 1 && usuarioVector[6] > 0) usuarioVector[6] -= 1;
    if(opcion == 3 && usuarioVector[6] < 6) usuarioVector[6] += 1;
																											gotoxy(1,7);cout<<"      ";
    // 7. Motivacion
    system("cls");

    gotoxy(1,5);color(2);cout << "7?? Que lo motiva principalmente?                            ";
    gotoxy(1,6);color(10);cout<< "[0] Justicia/deber  [1] Aventura/libertad  [2] Venganza/poder  [3] Proteccion  [4] Sin motivacion clara ";gotoxy(1,7);color(15);
    while(!(cin >> usuarioVector[7]) || usuarioVector[7] < 0 || usuarioVector[7] > 4){
        cin.clear();cin.ignore(1000,'\n');
    }
																											gotoxy(1,7);cout<<"      ";
    // 8. Color de pelo
    system("cls");

    gotoxy(1,5);color(2);cout << "8?? De que color es su cabello?                                                                            ";
    gotoxy(1,6);color(10);cout<< "[0] Negro [1] Cafe [2] Rojo/Rosa [3] Azul [4] Verde [5] Naranja [6] Rubio [7] Blanco/Gris [8] Calvo         ";gotoxy(1,7);color(15);
    while(!(cin >> usuarioVector[8]) || usuarioVector[8] < 0 || usuarioVector[8] > 8){
        cin.clear();cin.ignore(1000,'\n');
    }
																											gotoxy(1,7);cout<<"      ";
    // 9. Pregunta aleatoria (se mantiene igual)
    srand(time(0));
    int aleatoria = rand() % 3;
    switch(aleatoria){
        case 0:
        	system("cls");

        	gotoxy(1,7);cout<<"      ";
            gotoxy(1,5);color(2);cout << "?? Pregunta extra: Su poder es mas fisico o sobrenatural?                        ";
            gotoxy(1,6);color(10);cout<< "[1] Fisico  [2] Sobrenatural                                                         ";gotoxy(1,7);color(15);
            cin >> opcion;
            if(opcion == 1 && usuarioVector[3] > 0) usuarioVector[3] -= 1;
            if(opcion == 2 && usuarioVector[3] < 3) usuarioVector[3] += 1;
            break;
        case 1:
        	system("cls");

        	gotoxy(1,7);cout<<"      "; 
            gotoxy(1,5);color(2);cout << "?? Pregunta extra: El personaje ha matado o robado a alguien?                                           ";
            gotoxy(1,6);color(10);cout<< "[1] Si  [2] No\n>                                                                                      ";gotoxy(1,7);color(15);
            cin >> opcion;
            if(opcion == 1 && usuarioVector[6] < 6) usuarioVector[6] -= 1;
            if(opcion == 2 && usuarioVector[6] > 0) usuarioVector[6] += 1;
            break;
        case 2:
        	system("cls");

        	gotoxy(1,7);cout<<"      ";
            gotoxy(1,5);color(2);cout << "?? Pregunta extra: Que tan tranquilo suele ser?                        ";
            gotoxy(1,6);color(10);cout<< "[1] Muy impulsivo  [2] Normal  [3] Muy tranquilo                        ";gotoxy(1,7);color(15);
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
	color(3);
    gotoxy(3,14);cout << "Gracias por jugar al sistema experto de One Piece ";
    return 0;
}

