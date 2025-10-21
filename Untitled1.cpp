#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;

// --- CONFIGURACIÓN ---
const int N = 1000;
bool modoBloqueoGrueso = true; // cambia a false para usar bloqueo granular

// --- DATOS COMPARTIDOS ---
vector<int> numeros(N, 0);
vector<string> pizzas(N, "");

// --- MUTEX ---
mutex mtxGrueso;               // para bloqueo grueso
vector<mutex> mtxGranular(N);  // para bloqueo granular

// --- FUNCIONES DE TRABAJO ---
void productor() {
    srand(time(0));
    for (int i = 0; i < N; i++) {
        bool hecho = false;
        while (!hecho) {
            if (modoBloqueoGrueso) {
                // Bloqueo grueso: proteger todo el arreglo
                if (mtxGrueso.try_lock()) {
                    numeros[i] = rand() % 5 + 1;
                    mtxGrueso.unlock();
                    hecho = true;
                }
            } else {
                // Bloqueo granular: solo esa posición
                if (mtxGranular[i].try_lock()) {
                    numeros[i] = rand() % 5 + 1;
                    mtxGranular[i].unlock();
                    hecho = true;
                }
            }
            this_thread::yield(); // ceder CPU si no pudo bloquear
        }
    }
}

void consumidor() {
    for (int i = 0; i < N; i++) {
        bool hecho = false;
        while (!hecho) {
            if (modoBloqueoGrueso) {
                if (mtxGrueso.try_lock()) {
                    int val = numeros[i];
                    if (val != 0) {
                        switch (val) {
                            case 1: pizzas[i] = "peperoni"; break;
                            case 2: pizzas[i] = "vegetariana"; break;
                            case 3: pizzas[i] = "carnes frias"; break;
                            case 4: pizzas[i] = "italiana"; break;
                            case 5: pizzas[i] = "mexicana"; break;
                        }
                        mtxGrueso.unlock();
                        hecho = true;
                    } else {
                        mtxGrueso.unlock();
                    }
                }
            } else {
                if (mtxGranular[i].try_lock()) {
                    int val = numeros[i];
                    if (val != 0) {
                        switch (val) {
                            case 1: pizzas[i] = "peperoni"; break;
                            case 2: pizzas[i] = "vegetariana"; break;
                            case 3: pizzas[i] = "carnes frias"; break;
                            case 4: pizzas[i] = "italiana"; break;
                            case 5: pizzas[i] = "mexicana"; break;
                        }
                        hecho = true;
                    }
                    mtxGranular[i].unlock();
                }
            }
            this_thread::yield();
        }
    }
}

// --- MAIN ---
int main() {
    cout << "Simulacion de pizzeria con bloqueos ";
    if (modoBloqueoGrueso)
        cout << "GRUESOS\n";
    else
        cout << "GRANULARES\n";

    auto inicio = chrono::high_resolution_clock::now();

    thread t1(productor);
    thread t2(consumidor);

    t1.join();
    t2.join();

    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double> duracion = fin - inicio;

    cout << "\nTodas las tareas completadas." << endl;
    cout << "Tiempo total: " << duracion.count() << " segundos." << endl;

    // Comprobación rápida de algunos resultados
    cout << "\nEjemplo de resultados:" << endl;
    for (int i = 0; i < 10; i++)
        cout << i << ": " << numeros[i] << " -> " << pizzas[i] << endl;

    return 0;
}

