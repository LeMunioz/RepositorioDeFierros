#include <iostream>
#include <string>
#include <thread>
#include <vector>
using namespace std;
#include "colores.cpp"

void buscar(const string &texto){
    color(3);
    cout << "Que palabras quieres buscar?" << endl;
    color(5);
    cout << "No lo encontre patrón" << endl;
}

void MyThread(){



}



int main(){
    char opcion;

    color(1);
    cout << "    HOLA PINSHE PROFE (con cariño)" << endl;
    cout << "  NUESTRO PRIMER PROGRAMA CONCURRENTE" << endl;
    cout << "========================================" << endl;
    color(3);
    cout << "Quieres escribir tu texto?" << endl;
    color(10);
    cout << " [1]  Dejame escribirlo" << endl;
    cout << " [2]  No, dejame agarro uno de ejemplo" << endl;
    color(15);
    
    cin >> opcion;
    cin.ignore(); //limpiar buffer antes de getline
    
    switch(opcion){
        case '1': {
            string textoUsuario;
            color(8);
            cout << "A ver, pon tu texto porfis" << endl;
            getline(cin, textoUsuario);
            buscar(textoUsuario);        
            break;
        }
        case '2': {
            color(14);
            string textoEjemplo = 
                "El veloz murciélago hindú comía feliz cardillo y kiwi. "
                "La cigüeña tocaba el saxofón detrás del palenque de paja. "
                "El veloz murciélago hindú comía feliz cardillo y kiwi. "
                "La cigüeña tocaba el saxofón detrás del palenque de paja.";
            buscar(textoEjemplo);    
            break;
        }
        default:
            break;        
    } // FIN DEL SWITCH
} // FIN DEL MAIN

//Clase que se encarga de buscar a las palabras en un Hilo
//Cualquier código de busqueda en un string debe añadirse aquí
class Searchers {
public:

    //Es necesario asignar una ID al buscador, al igual que la palabra que va a buscar
    Searchers(int MyID, char search) {
        Identificador = MyID;
        Buscar = search;

        //Creamos el Hilo, Lo separamos del Main y guardamos el Hilo en una variable interna
        //No olvidemos el usar delete SearchThread cuando terminemos
        SearchThread = new thread(MyThread);
        SearchThread->detach();
    }

    //Obtiene la ID del Buscador
    int getID() {
        return Identificador;
    }

    //Obtiene la palabra que el Buscador está buscando
    char getWord() {
        return Buscar;
    }

private:
    int Identificador;
    char Buscar;

    //El objeto puntero no apunta a nada actualmente, existe para crear una variable de objeto "Vácia"
    //Para luego ser asignada cúando se use el constructor Del Objeto
    //No olvidemos cerrar esto cuando terminemos
    thread *SearchThread = NULL;
};
