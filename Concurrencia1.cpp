#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <sstream>

using namespace std;
#include "colores.cpp"

//El archivo se estructura de la siguiente manera:
// - Main
// - Clases
// - Funciones

//Prototipos de Función
//Si el orden de tus funciones evita que se puedan usar en otras clases o funciones, usar los prototipos permite
//una identificación temprana de las mismas para que sea posible compilarlas sin errores
void buscar(const string& texto);

///////////////////////////////////////////////////FUNCIÓN PRINCIPAL///////////////////////////////////////////////////////////////////////////


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
             string textoEjemplo =
     			"El veloz murcielago hindu comia feliz cardillo y kiwi. "
     			"La tortuga tocaba el saxofon detras del palenque de paja. "
     			"El veloz murcielago hindu comia feliz cardillo y kiwi. "
     			"La tortuga tocaba el saxofon detras del palenque de paja.";
     		 color(14);
			 cout << textoEjemplo << endl;

			 buscar(textoEjemplo);
            break;
        }
        default:
            break;        
    } // FIN DEL SWITCH
} // FIN DEL MAIN


////////////////////////////////////////////////////////CLASES/////////////////////////////////////////////

//Clase que se encarga de buscar a las palabras en un Hilo
//Cualquier código de busqueda en un string debe añadirse aquí

class Searchers {
public:

    //Es necesario asignar una ID al buscador, al igual que la palabra que va a buscar
    Searchers(int MyID, string search, string Frase) {
        Identificador = MyID;
        Buscar = search;
        MiFrase = Frase;

        //Creamos el Hilo, y lo guardamos en una variable interna
        //Lo que estamos haciendo en este constructor de objeto es obteniendo la dirección de memoria de la propia clase Searchers
        //Entrando a declarar que estamos usando método MyThread cómo función propia
        //Y que lo use cómo argumento para este objeto
        SearchThread = thread(&Searchers::MyThread, this);
        SearchThread.join();
    }


    //El Hilo se ejecuta desde dentro de la clase para aprovechar las funciones de Busqueda de la misma
    void MyThread() {

        vector<string> PalabrasSeparadas = stringSplitter(MiFrase);
        vector<int> indexHolder = findALLindex(PalabrasSeparadas, Buscar);
        int coincidencias = 0;

        for (string palabra : PalabrasSeparadas) {
            

            if (palabra == Buscar) {

                
                    cout << "\"" << Buscar << "\"" << " encontrada en posicion : " << indexHolder[coincidencias] << " por el Buscador " << Identificador << endl;
                    coincidencias++;

            }
        }

        if (coincidencias == 0) { 
        	color(5);
			cout << "Buscador " << Identificador << " Dice: No lo encontre patron" << endl; 
		}
    }

    //función que regresa un vector de números con los indices de la palabra a buscar
    vector<int> findALLindex(vector<string>& MyVector, string match){
        
        vector<int> myIndexes;

        for (int i = 0; i < MyVector.size(); i++) {
            if (MyVector[i] == match) {
                myIndexes.push_back(i + 1);
            }
        }
    
        return myIndexes;

    }

    //Función que regresa un vector de strings que contiene todas las palabras del texto de ejemplo
    vector<string> stringSplitter(string text) {

        vector<string> AllMyWords;

        //objeto Stream String, se usa para hacer que un string se lea cómo input de usuario
        istringstream MyText(text);

        string mainString;

        //guarda en mainString cada palabra que encuentre, sin contar los espacios
        while (getline(MyText, mainString, ' ')) {
            
            AllMyWords.push_back(mainString);
        
        }
        
           

        return AllMyWords;
    }


private:
    int Identificador;
    string Buscar;
    string MiFrase;
    thread SearchThread;
};

//////////////////////////////////////////////////////FUNCIONES/////////////////////////////////////////////////////////////

void buscar(const string& texto) {

    string palabra1;
    string palabra2;
    string palabra3;
    string palabra4;
    string palabra5;
	
	color(3);
    cout << "Que palabras quieres buscar? Puedes buscar hasta 5 Palabras\n"
        "Palabra 1:" << endl;
    cin >> palabra1;
    cout << "Palabra 2: " << endl;
    cin >> palabra2;
    cout << "Palabra 3: " << endl;
    cin >> palabra3;
    cout << "Palabra 4: " << endl;
    cin >> palabra4;
    cout << "Palabra 5: " << endl;
    cin >> palabra5;

    Searchers Buscador1(1, palabra1, texto);
    Searchers Buscador2(2, palabra2, texto);
    Searchers Buscador3(3, palabra3, texto);
    Searchers Buscador4(4, palabra4, texto);
    Searchers Buscador5(4, palabra5, texto);

    //Actualmente la impresión a pantalla de los resultados se choca entre hilo
    //Lo ideal sería obtener una tabla de palabras y coincidencias para imprimirla después de que los hilos hayan terminado de procesarse
}
