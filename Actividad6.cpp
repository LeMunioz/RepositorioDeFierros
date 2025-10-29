#include <iostream>
#include <vector>
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <random>
#include <chrono>
#include <conio.h>
#include "validacionEntradas.cpp"
#include "colores.cpp"
using namespace std;

/*
ANGEL EDUARDO MUÑOZ PEREZ
ACTIVIDAD 6_ (HILOS Y MULTIHILOS)
Programacion Paralela y Concurrente_ Prof. Carlos Javier
INGENIERIA EN COMPUTACION_ CUALTOS 25B
*/
/*
COMO FUNCIONA?
	Este programa se divide en 3 modulos principales que albarcan temas vistos hasta ahora en clases
	1. CONCURRENCIA
		Cuando desde el main se escoge esta parte del programa: Implementa dos tipos de hilos que interactúen a través de una estructura de datos compartida:
		Hilo Productor: Crea elementos (por ejemplo, números o "panes") y los coloca en una cola compartida.
		Hilo Consumidor: Saca elementos de la cola y los procesa (por ejemplo, los imprime).
	2. PARALELISMO
		Cuando desde el main se escoge esta parte del programa: este se encargar de realizar el calculo de un factorial grande utilizando
			procesamiento paralelo, el factorial objetivo sera el de 2000, habra un conjunto de 4 hilos los cuales calcularan, 
			Dividiendo el rango total de números en subrangos iguales.
			Asigna cada subrango a un Hilo de Trabajo diferente.
			Cada hilo calcula el factorial de los números en su subrango y mantiene una suma parcial.
			El Hilo Principal espera a que todos los hilos terminen.
			Suma los resultados parciales de todos los hilos para obtener el resultado final.
	3. MEMORIA COMPARTIDA y LOCK
		Cuando desde el main se escoge esta parte del programa realizara una funcion donde hay condicion de carrera este hara una simulacion del flujo de trabajo en un puesto
			de elotanas, donde habra 4 hilos. El hilo >elotanero se encargara de realizar dentro de un ciclo 1000 ordenes de forma
			aleatoria meterlos en un arreglo de 3 (elotanas, tostielotes y esquites), y hacerlos hara que aumente un contador para cada uno de estos productos.
			Y los hilos consumidores (cliente1, cliente2, cliente3) Cada uno se encargara de entrar al arreglo de ordenes escoger un espacio del arreglo (escogera al azar cual) 
			comera un producto, lo cual hara que el valor en ese espacio disminuya en 1. Hara esto con condicion de carrera, locks y try.locks para asegurar que otro 
			cliente no entre al espaio de memoria donde ya esta uno comiendo.

/*
ANGEL EDUARDO MUÑOZ PEREZ
ACTIVIDAD 6_ (HILOS Y MULTIHILOS)
Programacion Paralela y Concurrente_ Prof. Carlos Javier
INGENIERIA EN COMPUTACION_ CUALTOS 25B
*/

// ======================================================
// ================   1. CONCURRENCIA   =================
// ======================================================
mutex mtx;
condition_variable cv;
queue<int> colaCompartida;
bool producido = false;

void productor() {
    for (int i = 1; i <= 10; i++) {
        this_thread::sleep_for(chrono::milliseconds(500));
        unique_lock<mutex> lock(mtx);
        colaCompartida.push(i);
        producido = true;
        cout << "?? Productor: produjo elemento " << i << endl;
        lock.unlock();
        cv.notify_one();
    }
}

void consumidor() {
    for (int i = 1; i <= 10; i++) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] { return producido && !colaCompartida.empty(); });
        int valor = colaCompartida.front();
        colaCompartida.pop();
        cout << "?? Consumidor: consumió elemento " << valor << endl;
        if (colaCompartida.empty()) producido = false;
        lock.unlock();
    }
}

void concurrencia() {
    system("cls");
    color(10); cout << "=== CONCURRENCIA: PRODUCTOR - CONSUMIDOR ===\n\n";
    thread t1(productor);
    thread t2(consumidor);
    t1.join();
    t2.join();
    cout << "\nFinalizó el ejemplo de concurrencia.\n";
    system("pause");
}


// ======================================================
// ================   2. PARALELISMO   ==================
// ======================================================
long double factorialParcial(int inicio, int fin) {
    long double resultado = 1;
    for (int i = inicio; i <= fin; i++)
        resultado *= i;
    return resultado;
}

void Paralelismo() {
    system("cls");
    color(11); cout << "=== PARALELISMO: FACTORIAL DIVIDIDO EN HILOS ===\n\n";

    const int N = 2000;
    int numHilos = 4;
    vector<thread> hilos;
    vector<long double> resultados(numHilos);

    int rango = N / numHilos;

    auto inicio = chrono::high_resolution_clock::now();
    for (int i = 0; i < numHilos; i++) {
        int ini = i * rango + 1;
        int fin = (i == numHilos - 1) ? N : (i + 1) * rango;
        hilos.emplace_back([&, i, ini, fin]() {
            resultados[i] = factorialParcial(ini, fin);
            cout << "?? Hilo " << i + 1 << " calculó de " << ini << " a " << fin << endl;
        });
    }

    for (auto &h : hilos) h.join();

    long double total = 1;
    for (auto r : resultados) total *= r;

    auto fin = chrono::high_resolution_clock::now();
    chrono::duration<double> duracion = fin - inicio;

    cout << "\nFactorial de " << N << " (resultado parcial grande)" << endl;
    cout << "Tiempo total: " << duracion.count() << " segundos.\n";
    cout << "\n*No se muestra el factorial completo por su tamaño (overflow gigante)*\n";
    system("pause");
}


// ======================================================
// ============   3. MEMORIA COMPARTIDA / LOCKS   =======
// ======================================================
mutex mtxElotes;
int productos[3] = {0, 0, 0}; // 0 = Elotes, 1 = Tostielotes, 2 = Esquites
bool trabajando = true;

void elotanero() {
    srand(time(0));
    for (int i = 0; i < 1000; i++) {
        int tipo = rand() % 3;
        lock_guard<mutex> lock(mtxElotes);
        productos[tipo]++;
        cout << "????? Elotanero preparó " 
             << (tipo == 0 ? "Elote" : tipo == 1 ? "Tostielote" : "Esquite") 
             << " (Total: " << productos[tipo] << ")\n";
        this_thread::sleep_for(chrono::milliseconds(10));
    }
    trabajando = false;
}

void cliente(string nombre) {
    srand(time(0) + nombre.length());
    while (trabajando || productos[0] > 0 || productos[1] > 0 || productos[2] > 0) {
        int tipo = rand() % 3;
        if (mtxElotes.try_lock()) {
            if (productos[tipo] > 0) {
                productos[tipo]--;
                cout << "?? " << nombre << " comió un " 
                     << (tipo == 0 ? "Elote" : tipo == 1 ? "Tostielote" : "Esquite")
                     << " (Restante: " << productos[tipo] << ")\n";
            }
            mtxElotes.unlock();
        }
        this_thread::sleep_for(chrono::milliseconds(20));
    }
}

void MemoriaCompartida() {
    system("cls");
    color(14); cout << "=== MEMORIA COMPARTIDA Y LOCKS ===\n\n";
    thread tElotanero(elotanero);
    thread c1(cliente, "Cliente 1");
    thread c2(cliente, "Cliente 2");
    thread c3(cliente, "Cliente 3");

    tElotanero.join();
    c1.join();
    c2.join();
    c3.join();

    cout << "\nTodos los clientes comieron, y el elotanero terminó su turno.\n";
    system("pause");
}


// ======================================================
// ======================= MENÚ =========================
// ======================================================
int mostrarMenu(int seleccionado) {
    gotoxy(1, 9);
    for (int i = 1; i <= 3; i++) {
        if (i == seleccionado) color(10);
        else color(7);

        if (i == 1) cout << " [1] Concurrencia";
        if (i == 2) { gotoxy(36, 9); cout << " [2] Paralelismo"; }
        if (i == 3) { gotoxy(68, 9); cout << " [3] Locks y Memoria compartida"; }
    }
    color(15);
    return seleccionado;
}

int main() {
    system("cls");
    gotoxy(1, 1); color(11); cout << "                                   BIENVENIDO A MI PROGRAMA";
    gotoxy(1, 8); color(5);  cout << "                               Que opcion escoger ver primero?";

    int opcionSeleccionada = 1;
    mostrarMenu(opcionSeleccionada);

    while (true) {
        int tecla = _getch();

        if (tecla >= '1' && tecla <= '3') {
            opcionSeleccionada = tecla - '0';
            break;
        }

        if (tecla == 0 || tecla == 224) {
            int flecha = _getch();
            if (flecha == 75 || flecha == 72) {
                opcionSeleccionada--;
                if (opcionSeleccionada < 1) opcionSeleccionada = 3;
            }
            else if (flecha == 77 || flecha == 80) {
                opcionSeleccionada++;
                if (opcionSeleccionada > 3) opcionSeleccionada = 1;
            }
            mostrarMenu(opcionSeleccionada);
        }

        if (tecla == 13) break;
    }

    switch (opcionSeleccionada) {
        case 1: concurrencia(); break;
        case 2: Paralelismo(); break;
        case 3: MemoriaCompartida(); break;
    }

    system("cls");
    gotoxy(1, 1); color(11); cout << "Gracias por usar el programa :D\n";
    return 0;
}

