#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <chrono>
#include "colores.cpp"
using namespace std;
/*
ANGEL EDUARDO MUÑOZ PEREZ
Ing Computacion [CUALTOS25B]
Programacion Paralela y Concurrente_ Prof. Carlos Javier
*/

// Variable compartida
long long contador = 0;  

// Mutex para corregir la condición de carrera
mutex mtx;

// FUNCIÓN SIN SINCRONIZACIÓN (produce condición de carrera) ####
void incrementarSinMutex(int repeticiones){
    for (int i = 0; i < repeticiones; i++){
        contador++; 
	}
}

// FUNCIÓN CON SINCRONIZACIÓN (uso de mutex) #####
void incrementarConMutex(int repeticiones){
    for (int i = 0; i < repeticiones; i++){
        lock_guard<mutex> lock(mtx);  // acceso protegido -> no hay condición de carrera
        contador++;  
    }
}

int main() {
	color(3);
	cout<<"BIENVENIDO A MI PROGRAMA"<<endl;
	cout<<" ======================\n"<<endl;
	
    const int numHilos = 5;
    const int repeticiones = 100000;

    // CASO 1: SIN MUTEX 
    contador = 0;color(7);
    cout<<"Valor inicial es: "<<contador<<endl;
    auto inicio = chrono::high_resolution_clock::now();
    
    {
        vector<thread> hilos;

        for (int i = 0; i < numHilos; i++) {
        	//creo lista de hilos con la funcion thread los mando con la funcion y el paramtro de la funcion
            hilos.push_back(thread(incrementarSinMutex, repeticiones));
        }
        for (size_t i = 0; i < hilos.size(); i++) {
    		hilos[i].join();
		}
    }
    
    //Para ver cuatno tiempo le tomo
	auto fin = chrono::high_resolution_clock::now();
    auto duracion = chrono::duration_cast<chrono::milliseconds>(fin - inicio);
    
    color(7);
	cout << "Valor final SIN mutex: " << contador <<endl; color(9);
    cout <<	" y le tomo "<<duracion.count()  <<" milisegundos"<< endl;

    // CASO 2: CON MUTEX 
    contador = 0;color(7);
    cout<<"Valor inicial es: "<<contador<<endl;
    auto inicio2 = chrono::high_resolution_clock::now();
    
	{	
        vector<thread> hilos;
        for (int i = 0; i < numHilos; i++) {
        	//creo lista de hilos con la funcion thread los mando con la funcion y el paramtro de la funcion
            hilos.push_back(thread(incrementarConMutex, repeticiones)); 
        }
        for (size_t i = 0; i < hilos.size(); i++) {
    		hilos[i].join();
		}
    }
    
    //Para ver cuatno tiempo tomo
    auto fin2 = chrono::high_resolution_clock::now();
    auto duracion2 = chrono::duration_cast<chrono::milliseconds>(fin2 - inicio2);
    
    color(7);
    cout << "Valor final CON mutex: " << contador<<endl; color(9);
	cout << " y le tomo "<<duracion2.count()  <<" milisegundos" <<endl;

    color(15);return 0;
}

