#include <iostream>
#include <string>
using namespace std;
#include "colores.cpp"


void buscar(const string &texto){
    color(3);
    cout << "Que palabras quieres buscar?" << endl;
    color(5);
    cout << "No lo encontre patr�n" << endl;
}

int main(){
    char opcion;

    color(1);
    cout << "    HOLA PINSHE PROFE (con cari�o)" << endl;
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
                "El veloz murci�lago hind� com�a feliz cardillo y kiwi. "
                "La cig�e�a tocaba el saxof�n detr�s del palenque de paja. "
                "El veloz murci�lago hind� com�a feliz cardillo y kiwi. "
                "La cig�e�a tocaba el saxof�n detr�s del palenque de paja.";
            buscar(textoEjemplo);    
            break;
        }
        default:
            break;        
    } // FIN DEL SWITCH
} // FIN DEL MAIN


