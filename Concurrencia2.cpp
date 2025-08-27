#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <algorithm>
#include <cctype>
#include <chrono>
#include "colores.cpp"

using namespace std;

mutex cout_mutex; // Mutex para sincronizar la salida para que no se mezclen

// Funcion para convertir texto a minusculas
string toLower(const string& str) {
    string lowerStr = str;
    transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), 
              [](unsigned char c){ return tolower(c); });
    return lowerStr;
}

// Funcion para buscar una palabra en el texto
void buscarPalabra(const string& texto, const string& palabra, int idHilo) {
    string textoLower = toLower(texto);
    string palabraLower = toLower(palabra);
    
    size_t pos = textoLower.find(palabraLower); // Buscar la palabra en el texto con la libreria estandar
    bool encontrada = (pos != string::npos);
    
    // Bloquear el mutex para evitar que se mezcle la salida
    lock_guard<mutex> lock(cout_mutex);
    
    if (encontrada) {
        color(3);
        cout << "Hilo " << idHilo << ": La palabra '" << palabra 
             << "' fue ENCONTRADA en el texto." << endl;
    } else {
        cout << "Hilo " << idHilo << ": La palabra '" << palabra 
             << "' NO fue encontrada en el texto." << endl;
    }
}

// Funcion para generar texto de ejemplo
string generarTextoEjemplo() {
    return "La programacion concurrente es un paradigma de programacion "
           "en el que multiples tareas se ejecutan simultaneamente. "
           "En C++, podemos utilizar hilos para lograr la concurrencia. "
           "Los hilos permiten que diferentes partes de un programa se "
           "ejecuten al mismo tiempo, mejorando el rendimiento en "
           "sistemas con multiples nucleos. La busqueda de palabras en "
           "textos largos es un ejemplo perfecto donde la concurrencia "
           "puede ser beneficiosa. Al dividir la busqueda entre varios "
           "hilos, podemos acelerar el proceso significativamente. "
           "La biblioteca estandar de C++ proporciona la clase thread "
           "para trabajar con hilos. Es importante manejar adecuadamente "
           "la sincronizacion entre hilos usando mutex y otras "
           "herramientas de concurrencia para evitar condiciones de "
           "carrera y garantizar la consistencia de los datos. "
           "La programacion multihilo requiere cuidado pero ofrece "
           "grandes ventajas en terminos de eficiencia y rendimiento. "
           "Este texto servira como ejemplo para demostrar como "
           "funciona la busqueda concurrente de palabras usando hilos "
           "en C++. La tecnologia avanza rapidamente y la necesidad de "
           "procesamiento paralelo se vuelve cada vez mas importante. "
           "Los desarrolladores deben entender estos conceptos para "
           "crear aplicaciones modernas y eficientes. La concurrencia "
           "no es solo sobre velocidad, sino tambien sobre eficiencia "
           "en el uso de recursos del sistema. Con los procesadores "
           "multinucleo siendo la norma, aprovechar la concurrencia "
           "se ha vuelto esencial en el desarrollo de software.";
}

int main() {
    // Mensaje de bienvenida
    color(6);
    cout << "=====================================================" << endl;
    color(12);
    cout << "   BIENVENIDO AL BUSCADOR CONCURRENTE DE PALABRAS" << endl;
    color(6);
    cout << "=====================================================" << endl;
    cout << endl;
    
    string texto;
    int opcion;
    
    // para que escoja el usuario
    color(3);
    cout << "Como quieres el texto?" << endl;
    color(11);
    cout << "[1] Escribir mi propio texto" << endl;
    cout << "[2] Usar texto de ejemplo generado automaticamente" << endl;
    color(10);
    cout << "Seleccione una opcion (1 o 2): ";
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
        cout << "El texto esta vacio. Saliendo del programa." << endl;
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
    cout << "\nIniciando busqueda concurrente..." << endl;
    color(2);
    cout << "==============================================" << endl;
    
    // Crear hilos para cada palabra
    vector<thread> hilos;
    
    auto inicio = chrono::high_resolution_clock::now(); //toma captura en el reloj del procesador para ver cuadno empezo
    // Lanzar hilos para buscar cada palabra con su ID
    for (int i = 0; i < 4; i++) {
        hilos.emplace_back(buscarPalabra, texto, palabras[i], i + 1); //emplace_back construye el objeto en el lugar
    }
    
    // Esperar a que todos los hilos terminen
    for (auto& hilo : hilos) {
        hilo.join();
    }
    
    auto fin = chrono::high_resolution_clock::now(); //toma captura en el reloj del procesador para ver cuando termino
    auto duracion = chrono::duration_cast<chrono::milliseconds>(fin - inicio); //duracion en milisegundos

    color(2);
    cout << "==============================================" << endl;
    color(3);
    cout << "Busqueda completada en " << duracion.count() << " milisegundos." << endl;
    color(5);
    cout << "Gracias por usar el buscador concurrente!" << endl;
    
    return 0;
}
