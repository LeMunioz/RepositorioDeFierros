#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <string>

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
		ordenes y se encarguen de:
		
		1) A partir del numero, determinar el tipo de pizza que es
		2) Asignar los ingredientes que llevan
		3) Calcular el precio de la misma
		4) Llevar un contador de la cantidad de pizzas hechas de cada tipo

		todo esto sera introducido en la estructura > struct pizza{}
*/

// -------------- VARIABLES GLOBALES --------------------
//Estructura que contiene todos los datos de las pizzas, Estas pizzas contienen un Mutex para ser usados en un bloqueo más fino
struct Pizza {
	string NombrePizza;
	string Ingredientes[3];
	int tamano;
	float precio;
	mutex EnPreparacion;
};

//Numeros contiene el tipo y el tamaño de la pizza, está lleno de Números aleatorios del 0 al 7 en ambas columnas
int numeros[2][10000];
//PizzasHechas contiene todas las Pizzas que están pendientes de hacer, y al acabar la ejecución, todas las pizzas que se han hecho
Pizza PizzasHechas[10000];

//Contabiliza todas las pizzas que han sido creadas hasta ahora, y de que tipo son
int contadorMargarita = 0, contadorItaliana = 0, contadorMexicana = 0,
contadorHawaina = 0, contadorPeperoni = 0, contadorCarnesFrias = 0, contadorVegetariana = 0;

//Mutex para bloquear el Contador Global de todos los Hilos Cocineros
mutex MutexDelContador;

int ContadorMutuo = 0;

// -------------- FUNCIONES ------------------------------    
//sirve para convertir el numero que reciba Cocina() en el tipo de pizza para la estructura, y encima aumenta en 1 el contador de las pizzas

string TipoToPizza(int tipo) {
	switch (tipo) {
	case 0: contadorMargarita++; return "Margarita";
	case 1: contadorItaliana++; return "Italiana";
	case 2: contadorMexicana++;  return "Mexicana";
	case 3: contadorHawaina++; return "Hawaina";
	case 4: contadorPeperoni++; return "Peperoni";
	case 5: contadorCarnesFrias++; return "Carnes Frias";
	case 6: contadorVegetariana++; return "Vegetariana";
	default: return "Pizza no reconocida";
	}
}

//Obtiene los Ingredientes de la Pizza en base a su típo, y modifica la Pizza que se pase de argumento para añadirlos
void obtenerIngredientes(int tipo, Pizza& PizzaAProcesar) {
	//Se opera con el Alias de una pizza existente para modificarla de forma directa

	switch (tipo) {

	case 0:
		PizzaAProcesar.Ingredientes[0] = "Mozarella";
		PizzaAProcesar.Ingredientes[1] = "Albahaca";
		PizzaAProcesar.Ingredientes[2] = "Salsa de Jitomate";
		break;
	case 1:
		PizzaAProcesar.Ingredientes[0] = "Mozarella";
		PizzaAProcesar.Ingredientes[1] = "Jitomate";
		PizzaAProcesar.Ingredientes[2] = "Peperoni";
		break;
	case 2:
		PizzaAProcesar.Ingredientes[0] = "Mozarella";
		PizzaAProcesar.Ingredientes[1] = "Chile Verde";
		PizzaAProcesar.Ingredientes[2] = "Chorizo";
		break;
	case 3:
		PizzaAProcesar.Ingredientes[0] = "Mozarella";
		PizzaAProcesar.Ingredientes[1] = "Pinia";
		PizzaAProcesar.Ingredientes[2] = "Pan";
		break;
	case 4:
		PizzaAProcesar.Ingredientes[0] = "Mozarella";
		PizzaAProcesar.Ingredientes[1] = "Peperoni";
		PizzaAProcesar.Ingredientes[2] = "Salsa de Tomate";
		break;
	case 5:
		PizzaAProcesar.Ingredientes[0] = "Mozarella";
		PizzaAProcesar.Ingredientes[1] = "Peperoni";
		PizzaAProcesar.Ingredientes[2] = "Salchicha";
		break;
	case 6:
		PizzaAProcesar.Ingredientes[0] = "Mozarella";
		PizzaAProcesar.Ingredientes[1] = "Pimiento";
		PizzaAProcesar.Ingredientes[2] = "Aguacate";
		break;
	default:
		cout << "No hay ingredientes" << endl;
	}
}

//Regresa el costo base de la pizza en base a su tipo y su tamaño
int getPrice(int PizzaType, int PizzaSize) {

	int price = 120;

	switch (PizzaType) {
	
	case 0: price += 10; break;
	case 1: price += 20; break;
	case 2: price += 35; break;
	case 3: price += 40; break;
	case 4: price += 40; break;
	case 5: price += 50; break;
	case 6: price += 30; break;
	default: cout << "Tipo no Reconocido" << endl; break;
	}

	switch (PizzaSize) {
	case 0: price += 0; break;
	case 1: price += 10; break;
	case 2: price += 20; break;
	case 3: price += 30; break;
	case 4: price += 35; break;
	case 5: price += 40; break;
	case 6: price += 50; break;
	default: cout << "Tamanio no Reconocido" << endl; break;
	}

	return price;
}

//Hilo principal de trabajo para todos los cocineros
void Cocinero(string nombre){

	string Name = nombre;

	//Ciclo dónde sucede todo el trabajo de obtención de Pizzas
	while (true) {

		//Bloqueamos el Mutex del Contador, ya que cada cocinero va a tomar un turno, y aumentar el Contador el contador mutuo en 1
		lock_guard<mutex> Counter_Lock(MutexDelContador);

			//Creamos una variable de turno Actual cuyo valor es: El valor actual del contador grupal, y después aumentamos el contador en 1
			int LocalCounter = ContadorMutuo++;


			//Si ve que su turno es mayor a 10000, termina la ejecución del ciclo y su trabajo cómo cocinero
			if (ContadorMutuo > 10000) {
				break;
			}
		

		//Entramos a un segundo mutex, bloqueando la pizza en el índice del turno del hilo actual
		//Debido a que salimos del dominio del primer mutex, este automáticamente se libera para dar paso a otro hilos a usarlo.
		lock_guard<mutex> Pizza_Lock(PizzasHechas[LocalCounter].EnPreparacion);

				cout << "El Contador actual de " << Name << " es: " << LocalCounter + 1 << endl;

				
				//Obtenemos el tipo de la pizza
				PizzasHechas[LocalCounter].NombrePizza = TipoToPizza(numeros[0][LocalCounter]);

				cout << "Tipo de Pizza: " << PizzasHechas[LocalCounter].NombrePizza << endl;

				
				//Obtenemos los ingredientes de la pizza actual, pasandose así mismo apra su modificación directa
				obtenerIngredientes(numeros[0][LocalCounter], PizzasHechas[LocalCounter]);

				for (string ingrediente : PizzasHechas[LocalCounter].Ingredientes) {
					cout << ingrediente << endl;
				}

				//Obtenemos el precio de la Pizza
				PizzasHechas[LocalCounter].precio = getPrice(numeros[0][LocalCounter], numeros[1][LocalCounter]);
				
				cout << "Precio: " << PizzasHechas[LocalCounter].precio << endl;


				//Obtenemos el tamaño de la Pizza
				PizzasHechas[LocalCounter].tamano = numeros[1][LocalCounter];
				
				cout<< "Tamanio: " << PizzasHechas[LocalCounter].tamano << endl;


				//Hemos terminado con la pizza actual, volvemos al ciclo, y tomamos otro número para trabajar en esa otra pizza
				cout << Name << " Ha terminado la pizza numero: " << LocalCounter + 1 << "\n" << endl;
			
	}	
}

//inicializa el array de 10000 tamaños y tipos de pizza para empezar a trabajar
void Caja() {

	srand(time(NULL));
	

	for (int i = 0; i < 2; i++) {
	
		for (int j = 0; j < 10000; j++) {
		
			numeros[i][j] = rand() % 7;
		}

	}

}

int main() {

	Caja();

	thread myCocinero(Cocinero, "Emmanuel");
	thread myCocinero2(Cocinero, "Fabian");
	thread myCocinero3(Cocinero, "Munioz");
	thread myCocinero4(Cocinero, "Javier");
	thread myCocinero5(Cocinero, "Fany");
	myCocinero.join();
	myCocinero2.join();
	myCocinero3.join();
	myCocinero4.join();
	myCocinero5.join();
	
	cout << "Pizzas Preparadas:" << endl;

	cout<< "Margarita: " << contadorMargarita <<endl;
	cout << "Italiana: " << contadorItaliana << endl;
	cout << "Mexicana: " << contadorMexicana << endl;
	cout << "Carnes Frias: " << contadorCarnesFrias << endl;
	cout << "Vegetariana: " << contadorVegetariana << endl;
	cout << "Hawaina: " << contadorHawaina << endl;
	cout << "Peperoni: " << contadorPeperoni << endl;

	return 0;
}