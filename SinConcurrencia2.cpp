#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <chrono>
#include "colores.cpp"

using namespace std;

// Función para convertir texto a minúsculas
string toLower(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), 
              [](unsigned char c){ return tolower(c); });
    return lowerStr;
}

// Función para buscar una palabra en el texto
void buscarPalabra(const string& texto, const string& palabra, int id) {
    string textoLower = toLower(texto);
    string palabraLower = toLower(palabra);
    
    size_t pos = textoLower.find(palabraLower); // Buscar la palabra en el texto con la librería estándar
    bool encontrada = (pos != string::npos);
    
    if (encontrada) {
        color(3);
        cout << "Búsqueda " << id << ": La palabra '" << palabra 
             << "' fue ENCONTRADA en el texto." << endl;
    } else {
        cout << "Búsqueda " << id << ": La palabra '" << palabra 
             << "' NO fue encontrada en el texto." << endl;
    }
}

// Función para generar texto de ejemplo
string generarTextoEjemplo() {
    return "La programación concurrente es un paradigma de programación "
           "en el que múltiples tareas se ejecutan simultáneamente. "
           "En C++, podemos utilizar hilos para lograr la concurrencia. "
           "Los hilos permiten que diferentes partes de un programa se "
           "ejecuten al mismo tiempo, mejorando el rendimiento en "
           "sistemas con múltiples núcleos. La búsqueda de palabras en "
           "textos largos es un ejemplo perfecto donde la concurrencia "
           "puede ser beneficiosa. Al dividir la búsqueda entre varios "
           "hilos, podemos acelerar el proceso significativamente. "
           "La biblioteca estándar de C++ proporciona la clase thread "
           "para trabajar con hilos. Es importante manejar adecuadamente "
           "la sincronización entre hilos usando mutex y otras "
           "herramientas de concurrencia para evitar condiciones de "
           "carrera y garantizar la consistencia de los datos. "
           "La programación multihilo requiere cuidado pero ofrece "
           "grandes ventajas en términos de eficiencia y rendimiento. "
           "Este texto servirá como ejemplo para demostrar cómo "
           "funciona la búsqueda concurrente de palabras usando hilos "
           "en C++. La tecnología avanza rápidamente y la necesidad de "
           "procesamiento paralelo se vuelve cada vez más importante. "
           "Los desarrolladores deben entender estos conceptos para "
           "crear aplicaciones modernas y eficientes. La concurrencia "
           "no es solo sobre velocidad, sino también sobre eficiencia "
           "en el uso de recursos del sistema. Con los procesadores "
           "multinúcleo siendo la norma, aprovechar la concurrencia "
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
    cout << "¿Cómo quieres el texto?" << endl;
    color(11);
    cout << "[1] Escribir mi propio texto" << endl;
    cout << "[2] Usar texto de ejemplo generado automáticamente" << endl;
    color(10);
    cout << "Seleccione una opción (1 o 2): ";
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
        cout << "El texto está vacío. Saliendo del programa." << endl;
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
    cout << "\nIniciando búsqueda secuencial..." << endl;
    color(2);
    cout << "==============================================" << endl;
    
    auto inicio = chrono::high_resolution_clock::now(); // Toma captura en el reloj del procesador para ver cuándo empezó
    
    // Búsqueda secuencial (sin hilos)
    for (int i = 0; i < 4; i++) {
        buscarPalabra(texto, palabras[i], i + 1);
    }
    
    auto fin = chrono::high_resolution_clock::now(); // Toma captura en el reloj del procesador para ver cuándo terminó
    auto duracion = chrono::duration_cast<chrono::milliseconds>(fin - inicio); // Duración en milisegundos

    color(2);
    cout << "==============================================" << endl;
    color(3);
    cout << "Búsqueda completada en " << duracion.count() << " milisegundos." << endl;
    color(5);
    cout << "Gracias por usar el buscador secuencial!" << endl;
    
    return 0;
}
