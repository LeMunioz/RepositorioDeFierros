#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <vector>
#include <chrono>
#include <atomic>
#include <cstdlib>
#include "colores.cpp"
using namespace std;

/*
ANGEL EDUARDO MUÑOZ PEREZ
Programacion Paralela y Concurrente_ Prof. Carlos Javier
ICOM[CUALTOS25B] 
==============================================================
PROBLEMA DE LOS FILOSOFOS_ Usando memoria compartida y bloqueos
*/

//VARIABLES GLOBALES
const int comiendo = 12; //para cambiar el color cuando comen
const int pensando = 3;  //para cambiar el color cuando piensan

// Palillos compartidos
mutex palillos[5];

// Mutex para actualizar pantalla de forma ordenada
mutex pantalla;

// Colores y estados actuales de cada filosofo
int cfilosofo[5] = {pensando, pensando, pensando, pensando, pensando};
string estado[5] = {"pensando","pensando","pensando","pensando","pensando"};

// Control de ejecución
atomic<bool> ejecutando(true);

//FUNCION PARA REDIBUJAR PANTALLA (respeta tu forma de dibujo)
void dibujar() {
    system("cls");
    color(1);
    cout<<"	BIENVENIDO A MI PROGRAMA"<<endl;
    cout<<"====================================="<<endl; 
    color(15);

    //DIBUJO DE LOS FILOSOFOS
    gotoxy(6,4);color(cfilosofo[0]);cout<<"@";//Filosofo 1(el de arriba)
    gotoxy(7,4);color(cfilosofo[0]);cout<<"@";
    gotoxy(6,5);color(cfilosofo[0]);cout<<"%";
    gotoxy(7,5);color(cfilosofo[0]);cout<<"%";
    
    gotoxy(2,6);color(cfilosofo[1]);cout<<"@";//Filosofo 2(el izquierdo)
    gotoxy(2,7);color(cfilosofo[1]);cout<<"@";
    gotoxy(3,6);color(cfilosofo[1]);cout<<"%";
    gotoxy(3,7);color(cfilosofo[1]);cout<<"%";
    
    gotoxy(4,9);color(cfilosofo[2]);cout<<"%";//Filosofo 3(el abajoizquierdo)
    gotoxy(5,9);color(cfilosofo[2]);cout<<"%";
    gotoxy(4,10);color(cfilosofo[2]);cout<<"@";
    gotoxy(5,10);color(cfilosofo[2]);cout<<"@";
    
    gotoxy(8,9);color(cfilosofo[3]);cout<<"%";//Filosofo 4(el abajoderecho)
    gotoxy(9,9);color(cfilosofo[3]);cout<<"%";
    gotoxy(8,10);color(cfilosofo[3]);cout<<"@";
    gotoxy(9,10);color(cfilosofo[3]);cout<<"@";
    
    gotoxy(10,6);color(cfilosofo[4]);cout<<"%";//Filosofo 5(el derecho)
    gotoxy(11,6);color(cfilosofo[4]);cout<<"@";
    gotoxy(10,7);color(cfilosofo[4]);cout<<"%";
    gotoxy(11,7);color(cfilosofo[4]);cout<<"@";

    //ESTADOS
    gotoxy(1,12);color(7);cout<<"FILOSOFO 1 ESTA: "<<estado[0]<<endl;
    gotoxy(1,13);color(7);cout<<"FILOSOFO 2 ESTA: "<<estado[1]<<endl;
    gotoxy(1,14);color(7);cout<<"FILOSOFO 3 ESTA: "<<estado[2]<<endl;
    gotoxy(1,15);color(7);cout<<"FILOSOFO 4 ESTA: "<<estado[3]<<endl;
    gotoxy(1,16);color(7);cout<<"FILOSOFO 5 ESTA: "<<estado[4]<<endl;
}

//FUNCION DE CADA FILOSOFO
void filosofo(int id) {
    int palilloIzq = id;             // cada filosofo tiene palillo izquierdo = id
    int palilloDer = (id + 1) % 5;   // palillo derecho ciclico

    while(ejecutando) {
        // Pensando
        {
            lock_guard<mutex> lock(pantalla);
            cfilosofo[id] = pensando;
            estado[id] = "pensando";
            dibujar();
        }
        this_thread::sleep_for(chrono::seconds(2));

        // Intentar tomar palillos
        while (true) {
            if (palillos[palilloIzq].try_lock()) {
                if (palillos[palilloDer].try_lock()) {
                    // Comer
                    {
                        lock_guard<mutex> lock(pantalla);
                        cfilosofo[id] = comiendo;
                        estado[id] = "comiendo";
                        dibujar();
                    }
                    this_thread::sleep_for(chrono::seconds(10));
                    
                    // Soltar palillos
                    palillos[palilloDer].unlock();
                    palillos[palilloIzq].unlock();
                    break; // termina de comer, vuelve a pensar
                } else {
                    palillos[palilloIzq].unlock();
                }
            }
            this_thread::sleep_for(chrono::milliseconds(200));
        }
    }
}

// MAIN
int main(){
	ajustarConsola(80, 30);

	// Dibujo inicial
	{
	    lock_guard<mutex> lock(pantalla);
	    dibujar();
	}

	// Crear hilos de filosofos
	vector<thread> hilos;
	for(int i=0; i<5; i++){
	    hilos.emplace_back(filosofo, i);
	}

	// Mantener programa corriendo (CTRL+C para terminar)
	for(auto &h: hilos) h.join();
}//FIN DEL MAIN ///////////////////////////////////////////////

