#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "colores.cpp" 
using namespace std;

/*
ANGEL EDUARDO MUÑOZ PEREZ
Ing COMPUTACIÓN – CUALTOS 25B
Programación Paralela y Concurrente – Prof. Carlos Javier
ACTIVIDAD 4: (lock) Bloque Grueso y Granular
No
*/

/*
COMO FUNCIONA?
El programa implementa dos hilos, uno es Caja(): que se encarga
	de crear 1000 tareas las cuales son crear 1000 numeros aleatorios
	dentro de <lista_de_tareas>.
	y otro es Cocina(): que se encarga de procesar 1000 tareas lo cual
	consiste en dependiendo del numero de <lista_de_tareas>, mete en
	<pizzas_hechas> un tipo de pizza usando la funcion tipoPizza(), 
	ademas de aumentar en uno los contadores de pizza por cada iteracion
	para poder ver la cantidad final de cada tipo de pizza.
	Estos dos hilos pueden trabajar con bloqueo granular o grueso y se 
	decide cual metodo sera desde el main usando la variable modo para
	que dentro de cada hilo puedas hacerlo de una forma u otra gracias a un if.
*/

// -------------------- VARIABLES GLOBALES --------------------
mutex mtx; 
vector<int> lista_de_tareas(1000, 0);
vector<string> pizzas_hechas(1000, "");
// Contadores de pizzas
int margarita = 0, peperoni = 0, vegetariana = 0, carnes_frias = 0, hawaiana = 0, italiana = 0, desconocida = 0;

// -------------------- FUNCIONES --------------------
string tipoPizza(int n) {
    switch (n) {
    	case 0:
    		return "Margarita";
        case 1: 
			return "Peperoni";
        case 2: 
			return "Vegetariana";
        case 3: 
			return "Carnes Frias";
        case 4: 
			return "Hawaiana";
        case 5: 
			return "Italiana";
        default: 
			return "Desconocida";
    }
}

void reiniciarVectores() {
    fill(lista_de_tareas.begin(), lista_de_tareas.end(), 0);
    fill(pizzas_hechas.begin(), pizzas_hechas.end(), "");
    peperoni=0; vegetariana=0; carnes_frias=0; hawaiana=0; italiana=0; desconocida=0;
}

// -------------------- HILO CAJA --------------------
void Caja(int modo) {
    srand(time(0));
    
    if (modo == 2) {
        // BLOQUE GRUESO
        while (!mtx.try_lock()) {}
        for (int i = 0; i < 1000; ++i)
            lista_de_tareas[i] = (rand() % 5) + 1;
        mtx.unlock();
    } else {
        // BLOQUE GRANULAR
        for (int i = 0; i < 1000; ++i) {
            bool locked = false;
            while (!locked) {
                if (mtx.try_lock()) {
                    lista_de_tareas[i] = (rand() % 6);
                    mtx.unlock();
                    locked = true;
                }
            }//fin del while
        }//fin del for
    }//fin del if modo
}

// -------------------- HILO COCINERO --------------------
void Cocinero(int modo) {
    if (modo == 2) {
        // BLOQUE GRUESO
        while (!mtx.try_lock()) {}
        for (int i = 0; i < 1000; ++i) {
            string pizza = tipoPizza(lista_de_tareas[i]);
            pizzas_hechas[i] = pizza;

            // Contadores
            if (pizza == "Peperoni") peperoni++;
            else if (pizza == "Margarita") margarita++;
            else if (pizza == "Vegetariana") vegetariana++;
            else if (pizza == "Carnes Frias") carnes_frias++;
            else if (pizza == "Hawaiana") hawaiana++;
            else if (pizza == "Italiana") italiana++;
            else desconocida++;
        }
        mtx.unlock();
    } else {
        // BLOQUE GRANULAR
        for (int i = 0; i < 1000; ++i) {
            bool locked = false;
            while (!locked) {
                if (mtx.try_lock()) {
                    string pizza = tipoPizza(lista_de_tareas[i]);
                    pizzas_hechas[i] = pizza;

                    if (pizza == "Peperoni") peperoni++;
                    else if (pizza == "Margarita") margarita++;
                    else if (pizza == "Vegetariana") vegetariana++;
                    else if (pizza == "Carnes Frias") carnes_frias++;
                    else if (pizza == "Hawaiana") hawaiana++;
                    else if (pizza == "Italiana") italiana++;
                    else desconocida++;

                    mtx.unlock();
                    locked = true;
                }
            }
        }
    }
}

// -------------------- REGISTRO DE TIEMPO --------------------
void registrarTiempo(int modo, double tiempo) {
    ofstream archivo("registro_tiempos.txt", ios::app);
    if (archivo.is_open()) {
        archivo << "[" << (modo == 1 ? "Bloque Granular" : "Bloque Grueso  ") 
                << "] - " << tiempo << " segundos\n";
        archivo.close();
    }
}

// -------------------- FUNCIÓN PRINCIPAL --------------------
int main() {
    bool continuar = true;
    while (continuar) {
        system("cls");
        color(2); cout << "============================================="<<endl;
		color(10);cout << "       SIMULACION DE PIZZERIA CON LOCKS"<<endl;
		color(2); cout << "============================================="<<endl;
        color(3); cout << "                     MENU"<<endl;
        color(7); cout << "     peperoni - vegetariana - carnes frias "<<endl;
        		  cout << "              Hawaina - Italiana"<<endl;			
        color(2); cout << "---------------------------------------------"<<endl;
		color(10);cout << "Seleccione el tipo de bloqueo:"<<endl;
        color(7); cout << "  [1] Bloque Granular (lock por cada tarea)"<<endl;
        	      cout << "  [2] Bloque Grueso (un solo lock)"<<endl;
        color(2); cout << "---------------------------------------------"<<endl;
		color(8); cout << "Ingrese opcion: ";
        
        int modo;
        cin >> modo;
        if (modo != 1 && modo != 2) {
            color(12);cout << "Opcion invalida."<<endl;
            continue;
        }

        auto inicio = chrono::high_resolution_clock::now();

        thread t1(Caja, modo);
        thread t2(Cocinero, modo);

        t1.join();
        t2.join();

        auto fin = chrono::high_resolution_clock::now();
        chrono::duration<double> tiempo = fin - inicio;

        // Registro en archivo
        registrarTiempo(modo, tiempo.count());

        // Mostrar resultados
        color(2); cout << "\n=============================================\n";
        color(10);cout << "MODO: " << (modo == 1 ? "Bloque Granular" : "Bloque Grueso") << endl;
        color(10);cout << "Tiempo total de ejecucion: ";color(12); cout<< tiempo.count(); color(10);cout<< " segundos\n";
        color(2); cout << "============================================="<<endl;

        color(8); cout << "Cantidad de pizzas procesadas:"<<endl;
        color(3); cout << " Margarita:     " << margarita << endl;
        color(3); cout << " Peperoni:      " << peperoni << endl;
        color(3); cout << " Vegetariana:   " << vegetariana << endl;
        color(3); cout << " Carnes Frias:  " << carnes_frias << endl;
        color(3); cout << " Hawaiana:      " << hawaiana << endl;
        color(3); cout << " Italiana:      " << italiana << endl;
        color(3); cout << " Desconocida:   " << desconocida << endl;

        color(15);cout << "Primera pizza procesadas:"<<pizzas_hechas[0]<<endl;
        /*for (int i = 0; i < 1000; ++i)
            cout << "Orden #" << i + 1 << ": " << pizzas_hechas[i] << endl;
		*/
		color(15);cout << "Ultima pizza procesada:  "<<pizzas_hechas[999]<<endl;
        color(8); cout << "¿Desea realizar otra simulación? (1 = Si, 0 = No): "<<endl;
        int opcion;
        cin >> opcion;
        if (opcion == 1) {
            reiniciarVectores();
        } else {
            continuar = false;
            color(12);cout << "Fin del programa.\n";
        }
    }
    return 0;
}


