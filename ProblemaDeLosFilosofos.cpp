#include <iostream>
#include <thread>	//para los hilos de procesos
#include <mutex>	//para memoria compartida
#include <string> 
#include <vector> 	//para los arreglos dinamicos
#include <chrono> 	//para medir y manejar tiempo
#include <atomic> 	//para la variable ejecutando que quiero que no tenga condicion de carrera
#include <cstdlib>
#include <ctime>
#include "colores.cpp"
using namespace std;

/*
ANGEL EDUARDO MUÑOZ PEREZ
Programacion Paralela y Concurrente_ Prof. Carlos Javier
ICOM[CUALTOS25B] 
==============================================================
PROBLEMA DE LOS FILOSOFOS_ Usando memoria compartida y bloqueos
*/

/*
	El problema de los filosofos consiste en 5 filosofos se sientan a comer con
		5 palillos en la mesa, todos deben poder comer y pensar de forma alterna
		con la condicion de que solo pueden comer tomando 2 palillos, se debe 
		buscar una forma en que todos ppuedan alternar su comiendo y su pensando
		sin atascarse 
COMO FUNCIONA?
	Mi program para manejar el problema, usa los palillos en forma de arreglo
		como recurso compartido y cada uno de los filosofos es un hilo donde el comer 
		seran los procesos concurrentes, donde cada uno tiene asignado dos pocisiones 
		del arreglo de palillos. El filosofo intenta tomar un palillo si esta 
		desocupado, ve si el otro palillo esta desocupado, si no esta, se espera
		tantito, si ambos estan desocupados este realiza el proceso de comer.
		Aqui comer hace que cambie de color del filosofo > ColorFilosofo[id]
		y tambien hace que lo escriba implicitamente > estado[id] y se queda en ese
		estado durante 4 a 6 segundos. Despues desbloquea el espacio y el ciclo continua.
	Se necesita de libreria de "colores.cpp" que tiene funciones como:
		color(int); gotoxy(int,int); & ajustarConsola(int,int); 
		Siendo todas funciones de <windows.h> 		
*/

//VARIABLES GLOBALES
const int comiendo = 12; //para cambiar el color cuando comen (12 es rojo)
const int pensando = 3;  //para cambiar el color cuando piensan (3 es azul)

mutex palillos[5]; // Palillos compartidos
mutex pantalla; // Mutex para actualizar pantalla de forma ordenada

// Colores y estados actuales de cada filosofo
int ColorFilosofo[5] = {pensando, pensando, pensando, pensando, pensando};
string estado[5] = {"pensando","pensando","pensando","pensando","pensando"};

// Control de ejecución
atomic<bool> ejecutando(true); //para que no haya condicion de carrera en esta variable


//FUNCION PARA DIBUJAR A LOS FILOSOFOS (FrontEnd xd)
void dibujar() {
    system("cls");
    color(1);
    cout<<"       BIENVENIDO A MI PROGRAMA" << endl;
    color(10);
    cout<<"   Problema de los filosofos comelones"<<endl;

	//DIBUJANDO A LOS FILOSOFOS
    gotoxy(7,4); color(ColorFilosofo[0]); cout << "@";// Filosofo 1 (arriba)
    gotoxy(8,4); color(ColorFilosofo[0]); cout << "@";
    gotoxy(9,4); color(ColorFilosofo[0]); cout << "@";
    gotoxy(7,5); color(ColorFilosofo[0]); cout << "@";
    gotoxy(8,5); color(ColorFilosofo[0]); cout << "#";
    gotoxy(9,5); color(ColorFilosofo[0]); cout << "@";
    gotoxy(7,6); color(ColorFilosofo[0]); cout << "|";
    gotoxy(8,6); color(ColorFilosofo[0]); cout << "%";
    gotoxy(9,6); color(ColorFilosofo[0]); cout << "|";

    gotoxy(2,9); color(ColorFilosofo[1]); cout << "@";// Filosofo 2 (izquierda)
    gotoxy(3,9); color(ColorFilosofo[1]); cout << "@";
    gotoxy(4,9); color(ColorFilosofo[1]); cout << "-";
    gotoxy(2,10); color(ColorFilosofo[1]); cout << "@";
    gotoxy(3,10); color(ColorFilosofo[1]); cout << "#";
    gotoxy(4,10); color(ColorFilosofo[1]); cout << "%";
    gotoxy(2,11); color(ColorFilosofo[1]); cout << "@";
    gotoxy(3,11); color(ColorFilosofo[1]); cout << "@";
    gotoxy(4,11); color(ColorFilosofo[1]); cout << "-";

    gotoxy(4,15); color(ColorFilosofo[2]); cout << "|";//Filosofo 3 (abajoizquierda)
    gotoxy(5,15); color(ColorFilosofo[2]); cout << "%";
    gotoxy(6,15); color(ColorFilosofo[2]); cout << "|";
    gotoxy(4,16); color(ColorFilosofo[2]); cout << "@";
    gotoxy(5,16); color(ColorFilosofo[2]); cout << "#";
    gotoxy(6,16); color(ColorFilosofo[2]); cout << "@";
    gotoxy(4,17); color(ColorFilosofo[2]); cout << "@";
    gotoxy(5,17); color(ColorFilosofo[2]); cout << "@";
    gotoxy(6,17); color(ColorFilosofo[2]); cout << "@";

    gotoxy(10,15); color(ColorFilosofo[3]); cout << "|";//Filosofo 4 (abajoderecha)
    gotoxy(11,15); color(ColorFilosofo[3]); cout << "%";
    gotoxy(12,15); color(ColorFilosofo[3]); cout << "|";
    gotoxy(10,16); color(ColorFilosofo[3]); cout << "@";
    gotoxy(11,16); color(ColorFilosofo[3]); cout << "#";
    gotoxy(12,16); color(ColorFilosofo[3]); cout << "@";
    gotoxy(10,17); color(ColorFilosofo[3]); cout << "@";
    gotoxy(11,17); color(ColorFilosofo[3]); cout << "@";
    gotoxy(12,17); color(ColorFilosofo[3]); cout << "@";

    gotoxy(12,9); color(ColorFilosofo[4]); cout << "-";//Filosofo 5 (derecha)
    gotoxy(13,9); color(ColorFilosofo[4]); cout << "@";
    gotoxy(14,9); color(ColorFilosofo[4]); cout << "@";
    gotoxy(12,10); color(ColorFilosofo[4]); cout << "%";
    gotoxy(13,10); color(ColorFilosofo[4]); cout << "#";
    gotoxy(14,10); color(ColorFilosofo[4]); cout << "@";
    gotoxy(12,11); color(ColorFilosofo[4]); cout << "-";
    gotoxy(13,11); color(ColorFilosofo[4]); cout << "@";
    gotoxy(14,11); color(ColorFilosofo[4]); cout << "@";

    // PALILLOS amarillos
    color(14);
    gotoxy(5, 7); cout << "-";
    gotoxy(4, 13); cout << "-";
    gotoxy(8, 15); cout << "|";
    gotoxy(12, 13); cout << "-";
    gotoxy(11, 7); cout << "-";

    // Plato de arroz
    color(15);
    gotoxy(6, 9); cout << "_____";
    gotoxy(6, 10); cout << "arroz";
    gotoxy(6, 11); cout << "_____";
    
    //Contornos  (margen)
    gotoxy(1,3);color(1);cout<<"===========================================" << endl;color(15);//contorno superior
	gotoxy(1,19);color(1);cout<<"===========================================" << endl;color(15);//contorno inferior
	for(int margen=3; margen <20; margen++){  //contorno derecho
    	gotoxy(20, margen);color(1);cout<<"|";
	}
    // Estados
    gotoxy(24,5);color(8);cout<<"LISTA DE FILOSOFOS"<<endl;
    for (SHORT i = 0; i < 5; i++) {
        gotoxy(24, 8 + i); color(ColorFilosofo[i]);
        cout << "FILOSOFO " << i+1 << " ESTA: " << estado[i] << endl;
    }
    
    gotoxy(2,22);color(8);cout<<"Programa hecho por Angel Eduardo (LeMunioz)"<<endl;
						  cout<<"     Programacion Paralela y concurrente"<<endl;
					      cout<<"            Prof. Carlos Javier"<<endl;
						  cout<<"        Ing Computacion CUALTOS25B";
}//#### FIN DE FUCNCION dibujar ####


//FUNCION DE CADA FILOSOFO (BackEnd xd)
void filosofo(int id) {
    int palilloIzq = id;             // cada filosofo tiene palillo izquierdo = id
    int palilloDer = (id + 1) % 5;   // palillo derecho ciclico

    while(ejecutando) {
        // Pensando
        {
            lock_guard<mutex> lock(pantalla);
            ColorFilosofo[id] = pensando;
            estado[id] = "pensando";
            dibujar();
        }
        this_thread::sleep_for(chrono::seconds(1));
        
        // Intentar tomar palillos
        while (true) {
            if (palillos[palilloIzq].try_lock()) {
                if (palillos[palilloDer].try_lock()) {
                    // Comer
                    {
                        lock_guard<mutex> lock(pantalla);
                        ColorFilosofo[id] = comiendo;
                        estado[id] = "comiendo";
                        dibujar();
                    	
                    }
                 	
                    this_thread::sleep_for(chrono::seconds(1 +(rand() % 6))); //para que se quede comiendo  un numero random entre 4 y 6 segundos
                    gotoxy(24,14);cout<<time;
                    
                    // Soltar palillos
                    palillos[palilloDer].unlock();
                    palillos[palilloIzq].unlock();
                    break; // termina de comer, rompe este while, vuelve a > pensando
                } else {
                    palillos[palilloIzq].unlock();
                }
            }
            this_thread::sleep_for(chrono::milliseconds(200)); //para volver a intentar a agarrar
        }//fin de intento de tomar palillos
    }
}//#### FIN DE FUNCION filosofo ####

// MAIN
int main(){
	ajustarConsola(20, 90);
	srand(time(NULL));  
																													
    gotoxy(2,5);color(5);cout <<"=================================================================";
	gotoxy(6,6);color(5);cout <<" __________.__.__                      _____             ";
	gotoxy(6,7);color(5);cout <<"l_  _____/|__|  |   ____  ___________/ ____l____  ______";
	gotoxy(6,8);color(5);cout <<"|   ___)  |  |  |  /  _ l/  ___/  _ l   __l/  _ l/  ___/";
	gotoxy(6,9);color(5);cout <<"|   l     |  |  |_(  <_> )___ (  <_> )  | (  <_> )___ l ";
	gotoxy(6,10);color(5);cout<<"l__ /     |__|____/l____/____  >____/|__|  l____/____  >";
	gotoxy(6,11);color(5);cout<<"  l/                         l/                      l/ ";
	gotoxy(6,12);color(6);cout<<"                      By Munoz                           ";
	gotoxy(2,13);color(5);cout<<"================================================================"; gotoxy(1,26);
	std::this_thread::sleep_for(std::chrono::seconds(6));

	// Dibujo inicial
	{
	    lock_guard<mutex> lock(pantalla); //un mutex junto a pantalla para controlar que no todos los procesos la cambien a cada rato
	    dibujar();
	}

	// Crear hilos de filosofos
	vector<thread> hilos;
	for(int i=0; i<5; i++){
	    hilos.emplace_back(filosofo, i);
	}

	// Mantener programa corriendo (CTRL+C para terminar)
	for(auto &h: hilos) h.join();
}//#### FIN DEL MAIN ####

