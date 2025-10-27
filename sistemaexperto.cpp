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
Cada dimension mide una caracteristica, y la pocision dentro de ese vector sirve para cuantificar
o medir sus cualidades. Las preguntas dezplazan un puntero sobre esos ejes ciertas magnitudes y al final 
la distancia euclidiana se usa para determinar similitud y dicernir que personaje se intenta adivinar

Dimensiones:
	0 -> Rol           
	1 -> Origen        
	2 -> Edad          
	3 -> Poder         
	4 -> Fruta         
	5 -> Personalidad  
	6 -> Bondad        
	7 -> Motivacion                 
	8 -> Color de pelo 
	9 -> hombre o mujer
*/

// ----------------------------------------------------------------
// ----- VARIABLES GLOBALES Y ESTRUCTURAS ------
// ----------------------------------------------------------------

struct Personaje {
    string nombre;
    int vector[10];
};

vector<Personaje> basePersonajes;
int usuarioVector[10] = {0,0,20,0,0,0,3,1,0,1}; // Inicializacion por defecto

// ----------------------------------------------------------------
// ----- FUNCIONES AUXILIARES ------
// ----------------------------------------------------------------
//Sacar al personaje mas cercano de las 9 dimensiones usando una contatenacion de hipotenusas
//los ejes 0, 1, 8 y 10 les aumento el peso porque son diferencias muy marcada que ayudan a distinguir mejor el personaje 
double distanciaEuclidiana(const int a[10], const int b[10]) {
    double suma = 0;
    for (int i = 0; i < 9; i++) {
    	
        double peso = 1.0; // peso normal
        if (i == 0) peso = 5.0;   // Rol
        if (i == 1) peso = 10.0;  // Origen 
		if (i == 8) peso = 2.0;	  // Pelo
		if (i == 10)peso = 10.0;  // Sexo
        suma += pow((a[i] - b[i]) * peso, 2);
    }
    return sqrt(suma);
}


void mostrarTop3(const vector<pair<double,string>>& distancias) {
	int coloraqui;
    gotoxy(1,10);color(12);cout << "Los 3 personajes mas cercanos a tus respuestas son:\n";
    for (int i = 0; i < 3 && i < distancias.size(); i++) {
    	if (i == 0) coloraqui=3;
    	else coloraqui =1;
        gotoxy(1,11+i);color(coloraqui);cout << i+1 << ". " << distancias[i].second << " (distancia = " << distancias[i].first << ")\n";
    }
}

// ----------------------------------------------------------------
// ----- VALIDACION DE RESPUESTAS ------
// ----------------------------------------------------------------

//Valido primero con los parametros por si la repsuesta esta dentro del rango de ocpiones y luego si coincide el tipo de dato
int leerOpcion(int min, int max) {
    int opcion;
    while (true) {
        cin >> opcion;
        if (!cin.fail() && opcion >= min && opcion <= max) break;
        cin.clear();
        cin.ignore(10000, '\n');
        cout << " Entrada inválida. Intenta nuevamente: ";
    }
    return opcion;
}

// ----------------------------------------------------------------
// ----- BASE DE DATOS DE PERSONAJES ------
// ----------------------------------------------------------------

void inicializarBase() {
    basePersonajes.reserve(120);   
	/* 
	Dimensiones: 
	0 -> Rol (0 = Pirata, 1 = Marine, 	2 = Revolucionario, 3 = Civil)
	1 -> Origen (0 = Humano, 1 = Gyojin, 2 = Gigante, 3 = Tontata, 4 = Animal) 
	2 -> Edad (0 - 139) 
	3 -> Poder (0 = Ninguno, 1 = FrutaDelDiablo, 2 = Ambos, 3 = Haki) 
	4 -> Fruta (0 = No tiene, 1 = Zoan, 2 = Logia, 3 = Paramecia) 
	5 -> Personalidad (0 = Miedoso, 1 = Alegre, 2 = Tranquilo, 3= serio, 4 = Frio, 5 = Agresivo) 
	6 -> Bondad (0 = Muy malo, 3 = Neutral, 6 = Muy bueno) 
	7 -> Motivacion (0 = Justicia/deber, 1 = Proteccion/ayudar a otros, 2= conocimiento/ciencia, 3 = lealtad o amor, 
				     4 =Aventura/libertad, 5 = sueño individual, 6 = Venganza/poder, 7 = Sin motivacion clara) 
	8 -> Color de pelo (0=Negro,1=Cafe,2=verde,3=Rojo/Rosa,4=Azul,5=Naranja,6=Rubio,7=Blanco/Gris,8=Calvo,9=rosa) 
	9 -> Sexo (0 = hombre, 2 = mujer)
	*/
    //SOMBREROS DE PAJA
    basePersonajes.push_back({"Monkey D. Luffy",{0,0,19,2,1,1,5,4,0,0}});
    basePersonajes.push_back({"Roronoa Zoro",	{0,0,21,3,0,3,5,3,2,0}});
    basePersonajes.push_back({"Nami",			{0,0,20,0,0,3,5,5,5,2}});
    basePersonajes.push_back({"Ussop",			{0,0,19,3,0,0,5,4,0,0}});
    basePersonajes.push_back({"Sanji",			{0,0,21,3,0,2,6,5,6,0}});
    basePersonajes.push_back({"Tony Tony Chopper",{0,4,17,1,1,0,6,2,2,0}});
    basePersonajes.push_back({"Nico Robin",		{0,0,30,1,3,4,4,2,0,2}});
    basePersonajes.push_back({"Franky",			{0,0,34,0,0,1,5,4,4,0}});
    basePersonajes.push_back({"Brook",			{0,0,80,1,3,1,5,3,0,0}});
    basePersonajes.push_back({"Jimbe",			{0,1,45,3,0,2,5,1,0,0}});
    
    //MARINES
	basePersonajes.push_back({"Monkey D. Garp",	{1,0,78,3,0,1,4,0,7,0}});
	basePersonajes.push_back({"Sengoku",		{1,0,79,2,1,3,5,0,7,0}});
	basePersonajes.push_back({"Akainu",			{1,0,55,2,2,5,1,0,0,0}});
	basePersonajes.push_back({"Kisaru",			{1,0,58,2,2,4,3,0,0,0}});
	basePersonajes.push_back({"Aokiji",			{1,0,49,2,2,4,4,0,0,0}});
	basePersonajes.push_back({"Fujitora",		{1,0,54,2,3,2,6,0,0,0}});
	basePersonajes.push_back({"Smoker",			{1,0,36,2,2,4,5,0,7,0}});
	basePersonajes.push_back({"Tashigi",	    {1,0,23,0,0,1,6,0,1,2}});
	basePersonajes.push_back({"Koby",			{1,0,18,3,0,0,6,1,9,0}});
	basePersonajes.push_back({"Helmepo",		{1,0,22,3,0,0,3,0,7,0}});
	basePersonajes.push_back({"John Giant",     {1,2,63,3,0,3,3,0,7,0}});
	    
    //SHICHIBUKAIS
	basePersonajes.push_back({"Dracule Mihawk",	{0,0,43,3,0,4,3,7,0,0}});
	basePersonajes.push_back({"Crocodile",		{0,0,46,2,2,5,1,6,0,0}});
	basePersonajes.push_back({"Gecko Moria",	{0,0,48,2,3,5,2,6,0,0}});
	basePersonajes.push_back({"Bartholomeo Kuma",{0,0,47,1,3,2,6,1,0,0}});
	basePersonajes.push_back({"Boah Hancok",	{0,0,31,2,3,4,3,7,0,2}});
	basePersonajes.push_back({"Donxijote Doflamingo",{0,0,41,2,3,4,0,6,6,0}});
		
    //REVOLUCIONARIOS
	basePersonajes.push_back({"Monkey D. Dragon",	{2,0,55,1,3,3,5,0,0,0}});
	basePersonajes.push_back({"Emporio Ivankok",	{2,0,53,1,3,1,5,0,4,0}});
	basePersonajes.push_back({"Sabo",				{2,0,22,2,2,2,5,0,6,0}});
		
    //YONKOS
    basePersonajes.push_back({"Kaido"				,{0,0,59,2,1,5,2,6,0,0}});
    basePersonajes.push_back({"Edward Newgate (Barba Blanca)",{0,0,72,2,3,5,6,1,7,0}});
    basePersonajes.push_back({"Marco"				,{0,0,45,2,1,2,4,7,6,0}});
    basePersonajes.push_back({"Portgas D. Ace"		,{0,0,20,2,2,1,3,4,0,0}});
    basePersonajes.push_back({"Charlote Linlin (Big Mom)",{0,0,68,2,3,5,1,6,9,2}});
    basePersonajes.push_back({"Charlotte Katakuri",  {0,0,48,2,3,3,4,1,7,0}});
    basePersonajes.push_back({"Shanks"				,{0,0,39,3,0,1,4,7,3,0}});
    basePersonajes.push_back({"Ben Beckman"			,{0,0,50,0,0,3,3,7,7,0}});
    basePersonajes.push_back({"Marshall D. Teach (Black Beard)",{0,0,40,2,2,4,0,6,0,0}});
    basePersonajes.push_back({"Buggy"				,{0,0,39,1,3,0,3,6,4,0}});
    
	// PERSONAJES SECUNDARIOS	
	// East blue
	basePersonajes.push_back({"Alvida",			     {0,0,27,1,3,5,0,6,0,2}});
	basePersonajes.push_back({"Rika (la niña de las bolas de arroz)",{3,0,8,0,0,1,6,1,1,2}});
	basePersonajes.push_back({"Shushu",              {3,4,14,0,0,5,5,1,7,0}});
	basePersonajes.push_back({"Jango",	  	  	  	 {1,0,29,0,0,5,1,7,1,0}});
	basePersonajes.push_back({"Kaya",                {3,0,17,0,0,2,5,2,6,2}});
	basePersonajes.push_back({"Kuro",		         {0,0,27,0,0,4,0,6,0,0}});
	basePersonajes.push_back({"Johny and Yosaku",    {3,0,23,0,0,1,5,4,0,0}});
	basePersonajes.push_back({"Zeff",                {3,0,65,0,0,5,6,1,6,0}});
	basePersonajes.push_back({"Don Krieg",           {0,0,42,0,0,5,0,6,7,0}});
	basePersonajes.push_back({"Señor Genn",          {3,0,44,0,0,3,5,1,0,0}});
	basePersonajes.push_back({"Arlong",              {0,1,41,0,0,5,1,6,0,0}});
	basePersonajes.push_back({"Bellmere",  		     {3,0,30,0,0,1,6,1,3,2}});
	basePersonajes.push_back({"Nojiko",		         {3,0,22,0,0,2,5,7,4,2}});
	// Alabasta
	basePersonajes.push_back({"Laboon",              {3,4,54,0,0,1,4,3,8,0}});
	basePersonajes.push_back({"Igaram",			     {3,2,50,0,0,1,6,1,6,0}});
	basePersonajes.push_back({"Nefertari D. Vivi",   {3,0,18,0,0,1,6,1,4,2}});
	basePersonajes.push_back({"Karoo",			     {3,4,17,0,0,1,6,1,6,0}});
	basePersonajes.push_back({"Dorry y Broggy",      {3,2,160,0,0,1,5,4,1,0}});
	basePersonajes.push_back({"Mr 3 Galdino.",	     {0,0,37,1,3,0,2,7,0,0}});
	basePersonajes.push_back({"Dr. Hiruluk",         {3,0,50,0,0,1,6,1,7,0}});
	basePersonajes.push_back({"Kosa",                {2,0,27,0,0,3,5,0,2,0}});
	basePersonajes.push_back({"Nefertari D. Cobra",	 {3,0,50,0,0,2,6,0,7,0}});
	basePersonajes.push_back({"Mr. 2 Bon Clay",      {0,0,30,1,3,1,5,3,0,0}});
	basePersonajes.push_back({"Pell",	 	  	     {3,0,27,1,1,3,5,1,1,0}});
	basePersonajes.push_back({"Pestañas",			 {3,4,20,0,0,1,3,7,1,0}});
	basePersonajes.push_back({"Hina",			     {1,0,32,1,3,3,3,0,9,2}});
	// Skypea	
	basePersonajes.push_back({"Bellamy",             {0,0,24,2,3,5,2,6,6,0}});
	basePersonajes.push_back({"Masira (los simios)", {3,4,25,0,0,1,6,3,1,0}});
	basePersonajes.push_back({"Mont Blanc Cricket",  {3,0,41,0,0,1,6,2,6,0}});
	basePersonajes.push_back({"South Bird",			 {3,4,5,0,0,5,3,4,2,0}});
	basePersonajes.push_back({"Enel",                {3,0,39,2,2,4,0,6,6,0}});
	basePersonajes.push_back({"Mont Blanc Noland",   {3,0,39,0,0,1,6,2,2,0}});
	basePersonajes.push_back({"Kalgara",             {3,0,40,0,0,5,4,0,3,0}});
	basePersonajes.push_back({"Gan Fall",			 {3,0,60,0,0,2,6,0,7,0}});
	basePersonajes.push_back({"Aisa",				 {3,0,11,0,0,5,5,5,1,2}});	
	basePersonajes.push_back({"Connis",				 {3,0,22,0,0,2,6,7,5,2}});	
	// Water 7
	basePersonajes.push_back({"Capitan Shepherd",	 {1,0,30,0,0,3,3,0,1,0}});
	basePersonajes.push_back({"Condoriano",			 {1,0,25,0,0,1,6,3,1,0}});
	basePersonajes.push_back({"Foxy",                {0,0,38,1,3,0,1,6,0,0}});
	basePersonajes.push_back({"Rob Lucci",           {3,0,30,2,1,5,1,7,0,0}});
	basePersonajes.push_back({"Kaku",                {3,0,25,2,1,2,3,7,6,0}});
	basePersonajes.push_back({"Iceberg",             {3,0,38,0,0,3,4,0,4,0}});
	basePersonajes.push_back({"Pauly",               {3,0,26,0,0,1,4,0,6,0}});
	basePersonajes.push_back({"Spandam",             {1,0,41,0,0,5,0,0,4,0}});
	basePersonajes.push_back({"Kokoro",              {3,0,70,0,0,1,5,4,2,2}});
	basePersonajes.push_back({"Tom",                 {3,1,67,0,0,1,6,1,6,0}});
	basePersonajes.push_back({"Chimmey",             {3,0,10,0,0,1,5,3,2,2}});
	basePersonajes.push_back({"Gonbe",	             {3,4,8,0,0,1,5,7,4,0}});
	// Thriller bark
	basePersonajes.push_back({"Perona",              {3,0,25,1,3,5,3,7,9,2}});
	basePersonajes.push_back({"Dr. Hogback",         {3,0,45,0,0,4,0,2,4,0}});
	// MarineFord
	basePersonajes.push_back({"Duval",               {0,0,32,0,0,1,4,6,6,0}});
	basePersonajes.push_back({"Trafalgar D. Water Law",{0,0,26,2,3,4,4,6,0,0}});
	basePersonajes.push_back({"Bepo",              	 {0,4,22,3,0,1,6,3,7,0}});
	basePersonajes.push_back({"Eustass Kid",         {0,0,27,2,3,5,3,7,3,0}});
	basePersonajes.push_back({"Killer",				 {0,0,25,3,0,3,3,3,6,0}});
	basePersonajes.push_back({"Jewelry Bonney",      {0,0,22,1,3,5,3,3,9,2}});
	basePersonajes.push_back({"Sentomaru",           {1,0,34,3,0,3,3,0,0,0}});
	basePersonajes.push_back({"Momonga",			 {1,0,50,3,0,3,3,0,0,0}});
	basePersonajes.push_back({"Boa Marigold",		 {0,0,30,1,1,5,3,3,0,2}});
	basePersonajes.push_back({"Boa Sandersonia",	 {0,0,28,1,1,5,3,3,2,2}});
	basePersonajes.push_back({"Magellan",            {1,0,47,1,2,3,4,0,0,0}});
	basePersonajes.push_back({"Dadan", 		         {3,0,53,0,0,5,5,1,5,2}});
	basePersonajes.push_back({"Tsuru",				 {1,0,63,1,3,4,6,0,7,2}});
	// Fishmen island
	basePersonajes.push_back({"Caribou",             {0,0,30,1,3,5,0,6,7,0}});
	basePersonajes.push_back({"Shirahoshi",          {3,1,16,0,0,0,6,1,9,2}});
	basePersonajes.push_back({"Hody Jones",          {0,1,30,2,0,5,0,6,0,0}});
	basePersonajes.push_back({"Fisher Tiger",        {0,1,48,2,0,4,6,1,3,0}});
	basePersonajes.push_back({"Camie",               {3,1,18,0,0,1,6,3,3,2}});
	basePersonajes.push_back({"Hatchan",             {0,1,38,0,0,1,4,1,0,0}});
	// Dressrosa
	basePersonajes.push_back({"Vergo",               {1,0,41,2,0,4,1,0,0,0}});
	basePersonajes.push_back({"Caesar Clown",		 {3,0,40,1,2,4,0,2,3,0}});
	basePersonajes.push_back({"Senor Pink",          {0,0,42,1,3,4,3,3,0,0}});
	basePersonajes.push_back({"Leo",                 {3,3,25,0,0,2,6,1,1,0}});   // Líder tontatta, leal, protector
	basePersonajes.push_back({"Mansherry",           {3,3,20,0,0,1,6,1,3,2}});   // Princesa curandera, tierna y compasiva
	basePersonajes.push_back({"Hajrudin",            {0,2,81,0,0,5,3,4,7,0}});
	basePersonajes.push_back({"Bartolomeo",          {0,0,24,1,3,1,5,3,2,0}});
	basePersonajes.push_back({"Koala",				 {2,0,23,3,0,1,6,1,5,2}});
	// Whole kake
	basePersonajes.push_back({"Carrot",			     {0,4,15,0,0,1,6,4,6,2}});
	basePersonajes.push_back({"Inuarashi",			 {3,4,50,3,0,2,6,1,7,0}});
	basePersonajes.push_back({"Nekomamushi",	 	 {3,4,50,3,0,1,6,1,5,0}});
	basePersonajes.push_back({"Charlotte Pudding",   {3,0,16,1,3,2,5,3,3,2}});
	basePersonajes.push_back({"Vinsmoke Judge",      {1,0,56,2,0,4,1,0,6,0}});
	basePersonajes.push_back({"Vinsmoke Reiju.",	 {3,0,30,1,3,2,5,7,9,2}});
	// Wano
	basePersonajes.push_back({"Yamato",              {0,0,28,2,1,1,5,4,6,0}});
	basePersonajes.push_back({"Kin'emon",            {0,0,36,2,0,3,4,0,0,0}});
	basePersonajes.push_back({"Kozuki Oden",         {0,0,39,2,0,5,6,4,0,0}});
	basePersonajes.push_back({"Kanjuro",             {0,0,39,1,0,4,0,6,0,0}});
	basePersonajes.push_back({"Momonosuke",          {3,0,8,0,0,1,5,4,0,0}});
	basePersonajes.push_back({"King",				 {0,4,47,1,1,4,0,6,7,0}});
	basePersonajes.push_back({"Queen",				 {0,0,48,1,1,1,0,6,6,0}});
	// Egghead
	basePersonajes.push_back({"Vegapunk",            {1,0,65,2,0,3,5,2,7,0}});
	
	// LEGENDARIOS
	basePersonajes.push_back({"Gol D. Roger",        {0,0,59,3,0,1,5,4,0,0}}); 
	basePersonajes.push_back({"Silvers Rayleigh",    {0,0,78,3,0,3,3,4,7,0}}); 
	basePersonajes.push_back({"Scopper Gaban",       {0,0,80,3,0,3,3,4,0,0}}); 
	basePersonajes.push_back({"Crocus",              {3,0,66,0,0,2,6,2,7,0}});
	basePersonajes.push_back({"Saint Jaygarcia Saturn",{3,0,80,3,0,4,0,6,7,0}});
	basePersonajes.push_back({"Saint Marcus Mars",	 {3,0,75,3,0,4,0,6,7,0}});
	basePersonajes.push_back({"Saint Topman Warcury",{3,0,82,3,0,4,0,6,7,0}});
	basePersonajes.push_back({"Saint Ethanbaron V. Nusjuro",{3,0,76,3,0,4,0,6,7,0}});
	basePersonajes.push_back({"Saint Shepherd Ju Peter",{3,0,79,3,0,4,0,6,7,0}});

	basePersonajes.push_back({"Imu", 	             {3,0,139,2,3,5,0,6,0,1}});	
}


// ----------------------------------------------------------------
// ----- LOGO  ------
// ----------------------------------------------------------------
void dibujarlogo(){
	color(12);
	gotoxy(1,1); cout<<" _____ _           __        ___ _ _          __   ____        _        ";    
	gotoxy(1,2); cout<<"|_   _| |__   ___  | |      / (_) | |   ___  / _| |  _ |  __ _| |_ __ _ ";
	gotoxy(1,3); cout<<"  | | | '_ | / _ |  | | /| / /| | | |  / _ || |_  | | | |/ _` | __/ _` |";
	gotoxy(1,4); cout<<"  | | | | | |  __/   | V  V / | | | | | (_) |  _| | |_| | (_| | || (_| |";
	gotoxy(1,5); cout<<"  |_| |_| |_||___|    |_/|_/  |_|_|_|  |___/|_|   |____/ |__,_||__|__,_|";
	//contorno superior
	for(int i=0; i <98; i++){
		color(3);
		gotoxy(i,6); cout<<"=";
	}
	//contorno derecho
	for(int i=7; i <25; i++){
		color(3); 
		gotoxy(98,i);cout<<"|";
	}
	//contorno izquierdo
	for(int i=7; i <25; i++){
		color(3); 
		gotoxy(0,i);cout<<"|";
	}
	//contorno inferior
	for(int i=0; i <98; i++){
		color(3);
		gotoxy(i,24); cout<<"=";
	}
	color(15);  	                                                               	
}

// ----------------------------------------------------------------
// ----- PREGUNTAS ------
// ----------------------------------------------------------------
void hacerPreguntas() {
    int opcion = 0;

    // 1. Rol
    dibujarlogo();
    gotoxy(1,7); color(2); cout << "1?? ¿Qu3 rol tiene el personaje?";
    gotoxy(1,8); color(10); cout << "[0] Pirata  [1] Marine  [2] Revolucionario  [3] Civil/Gobierno";
    gotoxy(1,9); color(15); cout<< " >";
    usuarioVector[0] = leerOpcion(0, 3);
    system("cls");

    // 2. Origen
    dibujarlogo();
    gotoxy(1,7); color(2); cout << "2?? ¿Qu3 especie u origen tiene?";
    gotoxy(1,8); color(10); cout << "[0] Humano  [1] Gyojin  [2] Gigante  [3] Tontata  [4] Animal";
    gotoxy(1,9); color(15); cout<< " >";
    usuarioVector[1] = leerOpcion(0, 4);
    system("cls");

    // 3. Edad
    dibujarlogo();
    gotoxy(1,7); color(2); cout << "3?? ¿Qu3 edad tiene aproximadamente el personaje?";
    gotoxy(1,8); color(10); cout << "(Ingresa un numero entre 0 y 139)";
    gotoxy(1,9); color(15); cout<< " >";
    usuarioVector[2] = leerOpcion(0, 139);
    system("cls");

    // 4. Poder
    dibujarlogo();
    gotoxy(1,7); color(2); cout << "4?? ¿Que tipo de poder tiene?";
    gotoxy(1,8); color(10); cout << "[0] Ninguno  [1] Fruta del Diablo  [2] Ambos  [3] Haki";
    gotoxy(1,9); color(15); cout<< " >";
    usuarioVector[3] = leerOpcion(0, 3);

    if (usuarioVector[3] == 1 || usuarioVector[3] == 2) {
        system("cls");
        dibujarlogo();
        gotoxy(1,7); color(2); cout << "¿Que tipo de fruta tiene?";
        gotoxy(1,8); color(10); cout << "[1] Zoan  [2] Logia  [3] Paramecia";
        gotoxy(1,9); color(15); cout<< " >";
        usuarioVector[4] = leerOpcion(1, 3);
    } else {
        usuarioVector[4] = 0;
    }
    system("cls");

    // 5. Personalidad
    dibujarlogo();
    gotoxy(1,7); color(2); cout << "5?? ¿Como describirías su personalidad?";
    gotoxy(1,8); color(10); cout << "[0] Miedoso  [1] Alegre  [2] Tranquilo  [3] Serio  [4] Frío  [5] Agresivo";
    gotoxy(1,9); color(15); cout<< " >";
    usuarioVector[5] = leerOpcion(0, 5);
    system("cls");

    // 6. Bondad 
    dibujarlogo();
    gotoxy(1,7); color(2); cout << "6?? ¿El personaje es bueno, malo o neutral?";
    gotoxy(1,8); color(10); cout << "[0] Malo  [1] Neutral  [2] Bueno";
    gotoxy(1,9); color(15); cout<< " >";
    opcion = leerOpcion(0, 2);
    switch (opcion) { //lo pone en pocisiones medias (la segunda pocision, en medio o la penultima pocision)
        case 0: usuarioVector[6] = 1; break;
        case 1: usuarioVector[6] = 3; break;
        case 2: usuarioVector[6] = 5; break;
    } 
    system("cls");
				      
    // 7. Motivación
    dibujarlogo();
    gotoxy(1,7); color(2); cout << "7?? ¿Que lo motiva principalmente?";
    gotoxy(1,8); color(10);
    cout << "[0] moral/bien colectivo  [1] sus amigos y la aventura  [2] sueños propios o de si mismo   [3] no se";
    gotoxy(1,9);color(15); cout << "> ";
    opcion=leerOpcion(0, 3);
    switch(opcion){
    	//[7] -> (0=Justicia/deber, 1=Proteccion/ayudar, 2=conocimiento/ciencia, 3=lealtad o amor, 4=Aventura/libertad, 5=sueño individual, 6=Venganza/poder, 7=Sin motivacion clara) 
    	case 0: usuarioVector[7]=0; break;
    	case 1: usuarioVector[7]=3; break;
    	case 2: usuarioVector[7]=5; break;
    	case 3: usuarioVector[7]=7; break;
	}
    system("cls");

    // 8. Color de pelos
    dibujarlogo();
    gotoxy(1,7); color(2); cout << "8?? Su cabello es oscuro o claro?";
    gotoxy(1,8); color(10);
    cout << "[1] oscuro [2] claro [3] no tiene";
    gotoxy(1,9); color(15); cout<< " >";
    opcion = leerOpcion(1,3);
    switch(opcion){
    	case 1: usuarioVector[8]=1; break; //pelo cafe (media)
    	case 2: usuarioVector[8]=6; break; //pelo rubio (media)
    	case 3: usuarioVector[8]=8; break; //pelon
	}
    system("cls");
    
    if (usuarioVector[8] == 6) { //si tiene pelo claro, buscamos el tono exacto
        system("cls");
        dibujarlogo();
        gotoxy(1,7); color(2); cout << "¿De que color es su cabello?";
        gotoxy(1,8); color(10); cout << "[1] Blanco/Gris [2] Rubio [3] Naranja [4] Rosa [5] Azul [6] Verde";
        gotoxy(1,9); color(15); cout<< " >";
        opcion = leerOpcion(1, 6);
        switch (opcion){
        	case 1: usuarioVector[8]=7; break;
        	case 2: usuarioVector[8]=6; break;
        	case 3: usuarioVector[8]=5; break;
        	case 4: usuarioVector[8]=9; break;
        	case 5: usuarioVector[8]=4; break;
        	case 6: usuarioVector[8]=2; break;
		}
	}else if (usuarioVector[8] == 1){ //si tiene pelo oscuro buscamos tono exacto
		system("cls");
        dibujarlogo();
        gotoxy(1,7); color(2); cout << "¿De que color es su cabello?";
        gotoxy(1,8); color(10); cout << "[1] Negro [2] Cafe [3] Verde [4] Rojo [5] Azul";
        gotoxy(1,9); color(15); cout<< " >";
        opcion = leerOpcion(1, 5);
        switch (opcion){
        	case 1: usuarioVector[8]=0; break;
        	case 2: usuarioVector[8]=1; break;
        	case 3: usuarioVector[8]=2; break;
        	case 4: usuarioVector[8]=3; break;
        	case 5: usuarioVector[8]=4; break;
		}		
    } else {
        usuarioVector[8] = 8;
    }
    system("cls");

	// 9. PREGUNTAS ALEATORIAS
	srand(time(0));
	
	// número de preguntas que se harán (1 a 3)
	int numPreguntas = 1 + rand() % 3; 
	gotoxy(0,1);color(7);cout<<numPreguntas;
	// vector de conjunto de preguntas que revolveremos para ver cuales hace de forma alazar
	vector<int> indices = {0, 1, 2, 3, 4};
	random_shuffle(indices.begin(), indices.end());
	
	// ejecutamos solo las primeras preguntas de indice ya revuelto
	for (int i = 0; i < numPreguntas; i++) {
	    int aleatoria = indices[i];
	    switch (aleatoria) {
	        case 0://PREGUNTA: calibrar sus motivaciones
	        	system("cls");
	            dibujarlogo();
	            gotoxy(1,7); color(2); cout << "¿Que impulsa más sus acciones?";
	            switch (usuarioVector[7]){ 
	            	case 0: //el puntero esta en 0, cuando preguntaron sus motivaciones dijeron justicia o deber
	            		gotoxy(1,8);color(10);
	            		cout<<" [1] la justicia y el deber   [2]  Proteccion/ ayudar a los demas   [3] Descubrimiento o ciencia";
	            		gotoxy(1,9); color(15); cout<< " >";
	            		opcion=leerOpcion(1,3);
	            		switch(opcion){
	            			case 1: usuarioVector[7]=0; break;
	            			case 2: usuarioVector[7]=1; break;
	            			case 3: usuarioVector[7]=2; break;
						}
	            		break;
					case 3: //el puntero esta en 3, cuando preguntaron sus motivaciones dijeron sus amigos y la aventura
						gotoxy(1,8);color(10);
	            		cout<<" [1] Descubrimiento o ciencia   [2]  lealtad o amor   [3] Aventura/libertad";
	            		gotoxy(1,9); color(15); cout<< " >";
	            		opcion=leerOpcion(1,3);
	            		switch(opcion){
	            			case 1: usuarioVector[7]=2; break;
	            			case 2: usuarioVector[7]=3; break;
	            			case 3: usuarioVector[7]=4; break;
						}
						break;
	            	case 5: // el puntero esta en 5, cuando preguntaron sus motivaciones dijeron sueños propios o de si mismo
	            		gotoxy(1,8);color(10); 
	            		cout<<" [1] Aventura o libertad   [2]  sueño individual   [3] venganza o poder";
	            		gotoxy(1,9); color(15); cout<< " >";
	            		opcion=leerOpcion(1,3);
	            		switch(opcion){
	            			case 1: usuarioVector[7]=4; break;
	            			case 2: usuarioVector[7]=5; break;
	            			case 3: usuarioVector[7]=6; break;
						}
	            		break;
					case 7:	//el puntero esta en 5, cuando preguntaron sus motivaciones dijeron que no saben
						usuarioVector[7]=7; //por si no sabe cual es
						break;
				}
	
	        case 1://PREGUNTA: Calibrar Bondad
	        	system("cls");
	            dibujarlogo();
	            gotoxy(1,7); color(2); cout << "¿El personaje ha matado o robado a alguien?";
	            gotoxy(1,8); color(10); cout << "[1] Sí  [2] No";
	            gotoxy(1,9); color(15); cout<< " >";
	            opcion = leerOpcion(1, 2);
	            if (opcion == 1 && usuarioVector[6] > 0) usuarioVector[6] -= 1;
	            if (opcion == 2 && usuarioVector[6] < 6) usuarioVector[6] += 1;
	            break;
	
	        case 2://PREGUNTA: Calibrar Personalidad
	        	system("cls");
	            dibujarlogo();
	            //[5] -> Personalidad (0=Miedoso, 1=Alegre, 2=Tranquilo, 3=serio, 4=Frio, 5=Agresivo) 
	            gotoxy(1,7); color(2); cout << "¿Como suele reaccionar ante los problemas?";
	            gotoxy(1,8); color(10); cout << "[1] Se altera  [2] Es optimista [3] Mantiene la calma [4] Analiza antes de actuar";
	            gotoxy(1,9); color(15); cout<< " >";
	            opcion = leerOpcion(1, 4);
	            if (opcion == 1) {
	                int aleatorio = rand() % 2; // si se altera, alazar entre miedoso y agresivo
	                if (aleatorio == 0) usuarioVector[5] = 0; 
	                else usuarioVector[5] = 5;                
	            }else if (opcion == 2) usuarioVector[5] = 1;
	             else if (opcion == 3) usuarioVector[5] = 2;
	             else if (opcion == 4) usuarioVector[5] = 3;
	            break;
	
	        case 3://PREGUNTA: Sexo
	        	system("cls");
	            dibujarlogo();
	            gotoxy(1,7); color(2); cout << "¿Es hombre o mujer?";
	            gotoxy(1,8); color(10); cout << "[1] Hombre  [2] Mujer";
	            gotoxy(1,9); color(15); cout<< " >";
	            opcion = leerOpcion(1, 2);
	            if (opcion == 1) usuarioVector[10] = 0; 
	            else usuarioVector[10] = 2; 
	            break;
	
	        case 4://PREGUNTA: Calibrar Bondad
	        	system("cls");
	            dibujarlogo();
	            gotoxy(1,7); color(2); cout << "¿Tiende a ser mas cruel o más generoso?";
	            gotoxy(1,8); color(10); cout << "[1] Mas cruel  [2] Neutro  [3] Mas heroico";
	            gotoxy(1,9); color(15); cout<< " >";
	            opcion = leerOpcion(1, 3);
	            if (opcion == 1 && usuarioVector[6] > 0) usuarioVector[6] -= 1;
	            if (opcion == 3 && usuarioVector[6] < 6) usuarioVector[6] += 1;
	            break;
	    }//fin del switch
	}//fin del for   		

}


// ----------------------------------------------------------------
// ----- MAIN -----
// ----------------------------------------------------------------

int main() {
    inicializarBase();
    hacerPreguntas();

    // Calcular distancias
    vector<pair<double,string>> distancias;
    for (auto& p : basePersonajes) { //ciclo de rango del vector personaje (auto& saca referecnais por cada elemento, basePersonajes el elemento en cuestion y p es la variable de la iteracion,
        double d = distanciaEuclidiana(usuarioVector, p.vector);
        distancias.push_back({d, p.nombre});
    }

    // Ordenar
    sort(distancias.begin(), distancias.end(),
    //ordena tomando la dupla de cada personaje ubicando uno menor antes de uno mayor y lo hacen por referencia
    [](const pair<double,string>& a, const pair<double,string>& b) {
        return a.first < b.first;
	    }
	);


    mostrarTop3(distancias);
	color(3);
    gotoxy(3,23);cout 			<< "Gracias por jugar al sistema experto de One Piece ";
    gotoxy(3,24);color(15); cout<< "=================================================";
    gotoxy(1,25);color(8); cout<<"               Programa hecho por muñoz";
    return 0;
}

