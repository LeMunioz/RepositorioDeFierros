#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Jugador {
    string nombre;
    int dinero;
    vector<string> cartas;
};

// -------------------------- FUNCIONES ------------------------------

void inicializarStack(vector<string>& stack, const vector<string>& base) {
    stack = base;
    random_shuffle(stack.begin(), stack.end());
}

int tirarDado() {
    return (rand() % 6) + 1;
}

void verCartas(const Jugador& j) {
    if (j.cartas.empty()) {
        cout << j.nombre << " no tiene cartas.\n";
        return;
    }
    cout << "Cartas de " << j.nombre << ":\n";
    for (int i = 0; i < j.cartas.size(); i++) {
        cout << i+1 << ") " << j.cartas[i] << endl;
    }
}

void tomarTarjeta(Jugador& j, vector<string>& stack) {
    if (stack.empty()) {
        cout << "El stack esta vacio.\n";
        return;
    }
    string carta = stack.back();
    stack.pop_back();
    j.cartas.push_back(carta);
    cout << j.nombre << " tomó la carta: " << carta << endl;
}

void dejarTarjeta(Jugador& j, vector<string>& stack) {
    if (j.cartas.empty()) {
        cout << j.nombre << " no tiene cartas para dejar.\n";
        return;
    }
    verCartas(j);
    cout << "Indica el número de la carta a dejar: ";
    int idx;
    cin >> idx;
    idx--;

    if (idx < 0 || idx >= j.cartas.size()) {
        cout << "Índice inválido.\n";
        return;
    }

    string carta = j.cartas[idx];
    stack.insert(stack.begin(), carta);
    j.cartas.erase(j.cartas.begin() + idx);

    cout << j.nombre << " dejó la carta: " << carta << endl;
}

// -------------------------- MAIN ------------------------------

int main() {
    srand(time(NULL));

    // ----- STACKS BASE -----
    vector<string> baseDefensa;
    vector<string> baseAtaque;

    // Agregar 8 de cada carta de defensa
    vector<string> defensa = {
        "Cifrado de datos", "Consultas seguras", "Respaldo de datos", "Antivirus",
        "Mitigacion DDoS", "Validacion de entradas", "Curso de ciberseguridad",
        "Contrasenas seguras", "Firewall", "VLANs"
    };
    for (auto& s : defensa)
        for (int i = 0; i < 8; i++) baseDefensa.push_back(s);

    // Agregar cartas de ataque
    vector<pair<string,int>> ataque = {
        {"Ransomware",8}, {"Troyano",8}, {"DDoS",8}, {"MITM",8}, {"SQL Injection",8},
        {"XSS",8}, {"Phishing",8}, {"DNS Spoofing",8},
        {"Ataque Dia 0",1}, {"Ataque de contrasena",10}
    };

    for (auto& par : ataque)
        for (int i = 0; i < par.second; i++) baseAtaque.push_back(par.first);

    // Mezclar stacks
    vector<string> stackDefensa;
    vector<string> stackAtaque;

    inicializarStack(stackDefensa, baseDefensa);
    inicializarStack(stackAtaque, baseAtaque);

    // ----- JUGADORES -----
    int n;
    cout << "Cuantos jugadores? (2-4): ";
    cin >> n;

    while (n < 2 || n > 4) {
        cout << "Numero invalido. Ingresa 2 a 4: ";
        cin >> n;
    }

    vector<Jugador> jugadores(n);

    for (int i = 0; i < n; i++) {
        cout << "Nombre del jugador " << i+1 << ": ";
        cin >> jugadores[i].nombre;
        jugadores[i].dinero = 0;
    }

    // ----- CICLO DE TURNOS -----
    int turno = 0;

    while (true) {
        cout << "\n-----------------------------------------\n";
        cout << "Turno de: " << jugadores[turno].nombre << endl;
        cout << "Dinero actual: " << jugadores[turno].dinero << endl;

        cout << "\nAcciones:\n";
        cout << "1) Tirar dado\n";
        cout << "2) Ver cartas\n";
        cout << "3) Modificar dinero a cualquier jugador\n";
        cout << "4) Dejar una tarjeta\n";
        cout << "5) Tomar una tarjeta del stack\n";
        cout << "6) Cambiar al siguiente jugador\n";
        cout << "7) Salir del programa\n";
        cout << "Selecciona: ";

        int op;
        cin >> op;

        switch (op) {
            case 1: {
                int dado = tirarDado();
                cout << "Salio: " << dado << "!\n";
                break;
            }
            case 2: {
                verCartas(jugadores[turno]);
                break;
            }
            case 3: {
                cout << "A qué jugador modificar dinero? (1-" << n << "): ";
                int p;
                cin >> p;
                p--;

                if (p < 0 || p >= n) {
                    cout << "Jugador inválido.\n";
                    break;
                }

                cout << "Cuanto gana o pierde? (+ o -): ";
                int cantidad;
                cin >> cantidad;
                jugadores[p].dinero += cantidad;

                cout << "Ahora " << jugadores[p].nombre << " tiene " << jugadores[p].dinero << " de dinero.\n";
                break;
            }
            case 4: {
                cout << "Dejar tarjeta en qué stack?\n1) Defensa\n2) Ataque\n";
                int s; cin >> s;

                if (s == 1) dejarTarjeta(jugadores[turno], stackDefensa);
                else if (s == 2) dejarTarjeta(jugadores[turno], stackAtaque);
                else cout << "Opcion invalida.\n";

                break;
            }
            case 5: {
                cout << "Tomar tarjeta de qué stack?\n1) Defensa\n2) Ataque\n";
                int s; cin >> s;

                if (s == 1) tomarTarjeta(jugadores[turno], stackDefensa);
                else if (s == 2) tomarTarjeta(jugadores[turno], stackAtaque);
                else cout << "Opcion invalida.\n";

                break;
            }
            case 6: {
                turno = (turno + 1) % n;
                break;
            }
            case 7: {
                cout << "Saliendo del programa...\n";
                return 0;
            }

            default:
                cout << "Opcion invalida.\n";
        }
    }

    return 0;
}

