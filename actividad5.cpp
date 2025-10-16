#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <string>
#include "colores.cpp"
using namespace std;

/*
ANGEL EDUARDO MUÑOZ PEREZ
Programacion Paralela y Concurrente
ICOMP_ CUALTOS 25b
Prof. Carlos Javier
*/

/*
COMO FUNCIONA EL PROGRAMA?
	Implemento paralelismo simulando la produccion de pizzas en un local con varios trabajadores
	Para lograr esto hay una funcion > Caja() la cual se encargara de crear la lista de 10000 
		pizzas que en este caso seran representadas en una matriz > int<numeros>. donde cada columna
		es un numero para el tipo de pizza y el tamaño de la misma 
	Despues se realizan un conjunto de n hilos > Cocinero() que seran quienes procesen las 
		ordenes y se encarguen de: 1) a partir del numero determinar el tipo de pizza que es,
		2) Asignar los ingredientes que llevan, 3) calcular el precio de la misma 
		y 4) llevar un contador de la cantidad de pizzas hechas de cada tipo,todo esto 
		sera introducido en la estructura > struct pizza{}	
*/

// -------------- VARIABLES GLOBALES --------------------
struct Pizza {
	string NombrePizza;
	string Ingredientes[3];
	int tamano;
	float precio;
};
int numeros [2][10000];
int contadorMargarita =0, contadorItaliana=0, contadorMexicana=0,
    contadorHawaina=0, contadorPeperoni=0, contadorCarnesFrias=0, contadorVegetariana=0;

// -------------- FUNCIONES ------------------------------    
//sirve para convertir el numero que reciba Cocina() en el tipo de pizza para la estructura
string TipoToPizza(int tipo){
	switch(tipo){
		case 0: return "margarita";
		case 1: return "Italiana";
		case 2: return "Mexicana";
		case 3: return "Hawaina";
		case 4: return "Peperoni";
		case 5: return "CarnesFrias";
		case 6: return "Vegetariana";
		default: return "Pizza no reconocida";	
	}
}  

int main(){
	
}  
