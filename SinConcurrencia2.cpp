#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <chrono>
#include "colores.cpp"

using namespace std;

// Funci�n para convertir texto a min�sculas
string toLower(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), 
              [](unsigned char c){ return tolower(c); });
    return lowerStr;
}

// Funci�n para buscar una palabra en el texto
void buscarPalabra(const string& texto, const string& palabra, int id) {
    string textoLower = toLower(texto);
    string palabraLower = toLower(palabra);
    
    size_t pos = textoLower.find(palabraLower); // Buscar la palabra en el texto con la librer�a est�ndar
    bool encontrada = (pos != string::npos);
    
    if (encontrada) {
        color(3);
        cout << "B�squeda " << id << ": La palabra '" << palabra 
             << "' fue ENCONTRADA en el texto." << endl;
    } else {
        cout << "B�squeda " << id << ": La palabra '" << palabra 
             << "' NO fue encontrada en el texto." << endl;
    }
}

// Funci�n para generar texto de ejemplo
string generarTextoEjemplo() {
    return "La programaci�n concurrente es un paradigma de programaci�n "
           "en el que m�ltiples tareas se ejecutan simult�neamente. "
           "En C++, podemos utilizar hilos para lograr la concurrencia. "
           "Los hilos permiten que diferentes partes de un programa se "
           "ejecuten al mismo tiempo, mejorando el rendimiento en "
           "sistemas con m�ltiples n�cleos. La b�squeda de palabras en "
           "textos largos es un ejemplo perfecto donde la concurrencia "
           "puede ser beneficiosa. Al dividir la b�squeda entre varios "
           "hilos, podemos acelerar el proceso significativamente. "
           "La biblioteca est�ndar de C++ proporciona la clase thread "
           "para trabajar con hilos. Es importante manejar adecuadamente "
           "la sincronizaci�n entre hilos usando mutex y otras "
           "herramientas de concurrencia para evitar condiciones de "
           "carrera y garantizar la consistencia de los datos. "
           "La programaci�n multihilo requiere cuidado pero ofrece "
           "grandes ventajas en t�rminos de eficiencia y rendimiento. "
           "Este texto servir� como ejemplo para demostrar c�mo "
           "funciona la b�squeda concurrente de palabras usando hilos "
           "en C++. La tecnolog�a avanza r�pidamente y la necesidad de "
           "procesamiento paralelo se vuelve cada vez m�s importante. "
           "Los desarrolladores deben entender estos conceptos para "
           "crear aplicaciones modernas y eficientes. La concurrencia "
           "no es solo sobre velocidad, sino tambi�n sobre eficiencia "
           "en el uso de recursos del sistema. Con los procesadores "
           "multin�cleo siendo la norma, aprovechar la concurrencia "
           "se ha vuelto esencial en el desarrollo de software.";
}

int main() {
    // Mensaje de bienvenida
    color(6);
    cout << "=====================================================" << endl;
    color(12);
    cout << "   BIENVENIDO AL BUSCADOR SECUENCIAL DE PALABRAS" << endl;
    color(6);
    cout << "=====================================================" << endl;
    cout << endl;
    
    string texto;
    int opcion;
    
    // para que escoja el usuario
    color(3);
    cout << "�C�mo quieres el texto?" << endl;
    color(11);
    cout << "[1] Escribir mi propio texto" << endl;
    cout << "[2] Usar texto de ejemplo generado autom�ticamente" << endl;
    color(10);
    cout << "Seleccione una opci�n (1 o 2): ";
    cin >> opcion;
    cin.ignore(); // Limpiar el buffer
    
    if (opcion == 1) {
        color(3);
        cout << "\nPor favor, escriba el texto (presione Enter dos veces para finalizar):" << endl;
        string linea;
        while (true) {
            getline(cin, linea);
            if (linea.empty()) break;
            texto += linea + " ";
        }
    } else {
        texto = generarTextoEjemplo();
        color(3);
        cout << "\nTexto de ejemplo generado:" << endl;
        color(2);
        cout << "=============================================================" << endl;
        color(10);
        cout << texto << endl;
        color(2);
        cout << "=============================================================" << endl;
    }
    
    if (texto.empty()) {
        color(12);
        cout << "El texto est� vac�o. Saliendo del programa." << endl;
        return 0;
    }
    
    // Obtener las palabras a buscar
    vector<string> palabras(4);
    color(3);
    cout << "\nPor favor, ingrese 4 palabras para buscar:" << endl;
    
    for (int i = 0; i < 4; i++) {
        color(11);
        cout << "Palabra " << i+1 << ": ";
        cin >> palabras[i];
    }

    color(3);
    cout << "\nIniciando b�squeda secuencial..." << endl;
    color(2);
    cout << "==============================================" << endl;
    
    auto inicio = chrono::high_resolution_clock::now(); // Toma captura en el reloj del procesador para ver cu�ndo empez�
    
    // B�squeda secuencial (sin hilos)
    for (int i = 0; i < 4; i++) {
        buscarPalabra(texto, palabras[i], i + 1);
    }
    
    auto fin = chrono::high_resolution_clock::now(); // Toma captura en el reloj del procesador para ver cu�ndo termin�
    auto duracion = chrono::duration_cast<chrono::milliseconds>(fin - inicio); // Duraci�n en milisegundos

    color(2);
    cout << "==============================================" << endl;
    color(3);
    cout << "B�squeda completada en " << duracion.count() << " milisegundos." << endl;
    color(5);
    cout << "Gracias por usar el buscador secuencial!" << endl;
    
    return 0;
}
