#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

/*
ANGEL EDUARDO MUÑOZ PEREZ
Ing COMPUTACIÓN – CUALTOS 25B
Programación Paralela y Concurrente – Prof. Carlos Javier
ACTIVIDAD 4: (lock) Bloque Grueso y Granular

Simulación de pizzería:
- Un hilo "caja" genera los pedidos (números aleatorios del 1 al 5).
- Un hilo "cocinero" procesa las órdenes y las convierte en nombres de pizza.
- Se mide el tiempo de ejecución en dos modos:
    1. Bloque Grueso
    2. Bloque Granular
*/

// -------------------- VARIABLES GLOBALES --------------------
mutex mtx; // Lock compartido
vector<int> lista_de_tareas(1000, 0);  // Lista que representa las órdenes
vector<string> pizzas_hechas(1000, ""); // Lista de pizzas terminadas

// -------------------- FUNCIONES AUXILIARES --------------------
string tipoPizza(int n) {
    switch (n) {
        case 1: return "Peperoni";
        case 2: return "Vegetariana";
        case 3: return "Carnes Frias";
        case 4: return "Hawaiana";
        case 5: return "Italiana";
        default: return "Desconocida";
    }
}

// -------------------- CAJA (PRODUCTOR) --------------------
// Si modo == 1 ? granular  |  Si modo == 2 ? grueso
void Caja(int modo) {
    srand(time(0));
    if (modo == 2) {
        // BLOQUE GRUESO
        while (!mtx.try_lock()) {} // intentar bloquear
        for (int i = 0; i < 1000; ++i)
            lista_de_tareas[i] = (rand() % 5) + 1;
        mtx.unlock();
    } else {
        // BLOQUE GRANULAR
        for (int i = 0; i < 1000; ++i) {
            bool locked = false;
            while (!locked) {
                if (mtx.try_lock()) {
                    lista_de_tareas[i] = (rand() % 5) + 1;
                    mtx.unlock();
                    locked = true;
                }
            }
        }
    }
}

// -------------------- COCINERO (CONSUMIDOR) --------------------
void Cocinero(int modo) {
    if (modo == 2) {
        // BLOQUE GRUESO
        while (!mtx.try_lock()) {} // esperar hasta que se libere
        for (int i = 0; i < 1000; ++i)
            pizzas_hechas[i] = tipoPizza(lista_de_tareas[i]);
        mtx.unlock();
    } else {
        // BLOQUE GRANULAR
        for (int i = 0; i < 1000; ++i) {
            bool locked = false;
            while (!locked) {
                if (mtx.try_lock()) {
                    pizzas_hechas[i] = tipoPizza(lista_de_tareas[i]);
                    mtx.unlock();
                    locked = true;
                }
            }
        }
    }
}

// -------------------- FUNCIÓN PRINCIPAL --------------------
int main() {
    system("cls");
    cout << "=============================================\n";
    cout << "   SIMULACION DE PIZZERIA CON LOCKS\n";
    cout << "=============================================\n";
    cout << "Seleccione el tipo de bloqueo:\n";
    cout << "  [1] Bloque Granular (lock por cada tarea)\n";
    cout << "  [2] Bloque Grueso (un solo lock)\n";
    cout << "---------------------------------------------\n";
    cout << "Ingrese opcion: ";
    
    int modo;
    cin >> modo;
    if (modo != 1 && modo != 2) {
        cout << "Opción inválida.\n";
        return 0;
    }

    // ----- Medir tiempo -----
    auto inicio = chrono::high_resolution_clock::now();

    thread t1(Caja, modo);
    thread t2(Cocinero, modo);

    t1.join();
    t2.join();

    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double> tiempo = fin - inicio;

    // ----- Mostrar resultados -----
    cout << "\n=============================================\n";
    cout << "MODO: " << (modo == 1 ? "Bloque Granular" : "Bloque Grueso") << endl;
    cout << "Tiempo total de ejecucion: " << tiempo.count() << " segundos\n";
    cout << "=============================================\n";

    cout << "\nPrimeras 10 pizzas procesadas:\n";
    for (int i = 0; i < 10; ++i)
        cout << "Orden #" << i + 1 << ": " << pizzas_hechas[i] << endl;

    cout << "\nFin del programa.\n";
    return 0;
}

