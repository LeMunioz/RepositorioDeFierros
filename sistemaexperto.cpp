#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

/*
ANGEL EDUARDO MUÑOZ PEREZ come 8=D
SISTEMA EXPERTO
ICOM_ CUALTOS[25B]
*/

/*
COMO FUNCIONA?
	Este programa intenta replicar un sistema inteligente actuando como un Akinator de personajes de One Piece.
	Para hacer esto utilizaremos un número de preguntas y una forma de representar las características
	de cada personaje en un espacio vectorial de varias dimensiones. Cada eje o dimensión representa
	una cualidad que se puede medir de forma discreta o no discreta.

	Dimensiones utilizadas:
	0 -> Origen      (0 = Humano, 1 = Gyojin, 2 = Gigante, 3 = Tontata, 4 = Otros)
	1 -> Edad        (0 - 139)
	2 -> Poder       (0 = Fruta del diablo, 1 = Haki, 2 = Ambos, 3 = Ninguno)
	3 -> Afiliación  (0 = Pirata, 1 = Marina, 2 = Revolucionario, 3 = Civil)
	4 -> Personalidad(0 = Alegre, 1 = Serio, 2 = Agresivo, 3 = Tranquilo, 4 = Frío)
	5 -> Bondad      (0 = muy malo, 3 = neutral, 6 = muy bueno)
	6 -> Motivación  (0 = Justicia/deber, 1 = Aventura/libertad, 2 = Venganza/poder,
					  3 = Protección de otros, 4 = Sin motivación clara)
	
	El usuario, a través de respuestas, construye su propio vector de posición.
	Se calcula la distancia euclidiana entre la posición del usuario y cada personaje.
	El personaje más cercano se considera la mejor predicción.
	
	
	Yo creo que todos deberia mos de saber como hacerle para saber hacer las cosas que sean necesarias para la vida que
	esas cosas podrían ser cualquier cosa sabes entonces tienes que saberle a todo para poder saberle bien a todo
	y que todo te salga bien y todo eso y hacer de todo sabiento todo haciendo todo pero pues es un pensamiento una creencia
	una idea que no se ha llevado a la práctica algo asi como habia una vez un lobo que estaba en el bosque y llego una 
	niña y sabe qué de su abuelita y con capa roja y entonces te adelantas a llegar con la abuelita que están hablando de 
	endodoncia y de un termo en el refri, les dio risa no entendí porque y se supone que el lobo tiene que suplantar la
	identidad de la abuelita de la niña para comerse a la niña oye qué feo cuento porqué todos se lo saben si está bien 
	horrible se entiende ue se quiere que sea una enseñansa para los niños para que no confíen en cualquiera ni en su abuela
	pero cual es la necesidad de contar algo tan feo nunca va a llegar un lobo a suplantar a tu abuelita a menos que sea furra
	que está haciendo el muñoz yo creo que no manches llegó la viky pero conmigo no hay pedo proque ando escribiendo y parece
	que ando chambeando jajaj xd :v when momo papu lol xdxd
	mugre muñoz porque no viene
	y ya pasan de las 4 y no llega carlos
	oye no manches se cay+o algo del aws y todo está caído, todo mamón todo está ca+igo porque todo usa aws al parecer, pásate
	de ñonga wtf omg en plan holy shit a ver a qué puta hora llega carlos casi parece que si vamos a presentar hoy asumadre
	lo que se venia y ya a donde iba iba por terceros ups de a los ahi y se las llevabna pues un chingo de no we eso de aws pedian
	peso de las cajas puto no cartulina apache alatas ponen verga chingados trozos de madera ballenas su bascula trucada no
	mira de risa we cacharon we abrio la caja no 150000 opreoductos puto
	oye en cta son bien pinches putas groseros todos a la verga asumadre aaaaaa jajaj todos piensan que estoy haciendo tarea 
	wey ndo bien ida no pienso bien tengp sueño es porque se cayó aws  
	
*/


// ------- VARIABLES GLOBALES Y ESTRUCTURAS -------
struct Personaje {
    string nombre;
    int vector[7];
};

vector<Personaje> basePersonajes;
int usuarioVector[7] = {0, 0, 3, 0, 0, 3, 0}; //Inicializo el vector de puntero con cualidades promedio y neutras

void inicializarBasePersonajes() {
	//{nombre, origen, edad, poder, afiliacion, personalidad, bondad, motivacion}
	
    // Sombreros de paja
    basePersonajes.push_back({"Monkey D. Luffy", {0, 19, 2, 0, 0, 6, 1}});
    basePersonajes.push_back({"Roronoa Zoro", {0, 21, 2, 0, 1, 5, 1}});
    basePersonajes.push_back({"Nami", {0, 20, 3, 0, 0, 5, 1}});
    basePersonajes.push_back({"Usopp", {0, 19, 3, 0, 0, 5, 1}});
    basePersonajes.push_back({"Sanji", {0, 21, 2, 0, 1, 6, 3}});
    basePersonajes.push_back({"Tony Tony Chopper", {4, 17, 0, 0, 0, 6, 3}});

    // Marina
    basePersonajes.push_back({"Sakazuki (Akainu)", {0, 55, 1, 1, 2, 1, 0}});
    basePersonajes.push_back({"Borsalino (Kizaru)", {0, 58, 0, 1, 3, 3, 0}});
    basePersonajes.push_back({"Kuzan (Aokiji)", {0, 49, 0, 1, 3, 4, 3}});

    // Yonkos y comandantes
    basePersonajes.push_back({"Shanks", {0, 39, 2, 0, 0, 6, 3}});
    basePersonajes.push_back({"Kaido", {0, 59, 2, 0, 2, 1, 2}});
    basePersonajes.push_back({"Charlotte Linlin", {0, 68, 0, 0, 2, 0, 2}});
    basePersonajes.push_back({"Edward Newgate", {0, 72, 2, 0, 3, 6, 3}});

    // Revolucionarios
    basePersonajes.push_back({"Monkey D. Dragon", {0, 55, 1, 2, 3, 4, 0}});
    basePersonajes.push_back({"Sabo", {0, 22, 2, 2, 1, 6, 3}});

    // poner mas personajes
}

// ------- FUNCIONES -------
//para validar entradas numericas, valida por tipo de dato y por estar dentro del rango de respuestas
int leerOpcion(int min, int max) {
    int opcion;
    while (true) {
        cin >> opcion;
        if (!cin.fail() && opcion >= min && opcion <= max) break;
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Entrada inválida. Intenta nuevamente: ";
    }
    return opcion;
}

//para validar entradas de caracter, donde validamos dentro del rango de opciones que pueden haber (vector)
char leerCharOpcional(vector<char> opciones) {
    char c;
    while (true) {
        cin >> c;
        c = tolower(c);
        for (auto o : opciones) {
            if (c == o) return c;
        }
        cout << "Entrada inválida. Intenta nuevamente: ";
    }
}

// ====================================================
// PREGUNTAS PRINCIPALES
// ====================================================
void hacerPreguntasBase() {
    cout << "=== SISTEMA EXPERTO ONE PIECE ===\n\n";

    // Origen
    cout << "1. ¿Qué origen tiene el personaje?\n";
    cout << "[0] Humano\n[1] Gyojin\n[2] Gigante\n[3] Tontata\n[4] Otros\n> ";
    usuarioVector[0] = leerOpcion(0,4);

    // Edad (rango amplio)
    cout << "2. ¿Es mayor de 40 años? (s/n): ";
    char edadResp = leerCharOpcional({'s','n'});
    if (edadResp == 's') {
        cout << "¿Es mayor de 70 años? (s/n): ";
        edadResp = leerCharOpcional({'s','n'});
        usuarioVector[1] = (edadResp == 's') ? 80 : 50; //si es, 80, si no, 50
    } else {
        cout << "¿Es mayor de 20 años? (s/n): ";
        edadResp = leerCharOpcional({'s','n'});
        usuarioVector[1] = (edadResp == 's') ? 25 : 18; //si es, 25, si no, 18
    }

    // Poder
    cout << "3. ¿Qué tipo de poder tiene?\n";
    cout << "[0] Fruta del diablo\n[1] Haki\n[2] Ambos\n[3] Ninguno\n> ";
    usuarioVector[2] = leerOpcion(0,3);

    // Tripulación
    cout << "4. ¿Qué afiliación tiene?\n";
    cout << "[0] Pirata\n[1] Marina\n[2] Revolucionario\n[3] Civil\n> ";
    usuarioVector[3] = leerOpcion(0,3);

    // Personalidad
    cout << "5. ¿Cómo describirías su personalidad?\n";
    cout << "[0] Alegre\n[1] Serio\n[2] Agresivo\n[3] Tranquilo\n[4] Frío\n> ";
    usuarioVector[4] = leerOpcion(0,4);

    // Bondad (pregunta base)
    cout << "6. ¿Es bueno, malo o neutral? (b/m/n): ";
    char b = leerCharOpcional({'b','m','n'});
    if (b == 'b') usuarioVector[5] = 4;		    //si es bueno, va en la pocision 4 de 6
    else if (b == 'm') usuarioVector[5] = 1;    //si es malo, va en la pocision 1 de 6
    else usuarioVector[5] = 3; 				    //si es neutro, va en la pocision 3 de 6

    // Bondad (ajuste)
    cout << "7. ¿Ha hecho cosas crueles? (s/n): ";
    char crueldad = leerCharOpcional({'s','n'});
    if (crueldad == 's') usuarioVector[5] -= 1;
    else usuarioVector[5] += 1;

    if (usuarioVector[5] < 0) usuarioVector[5] = 0;
    if (usuarioVector[5] > 6) usuarioVector[5] = 6;

    // Motivación base
    cout << "8. ¿Cuál es su principal motivación?\n";
    cout << "[0] Justicia/deber\n[1] Aventura/libertad\n[2] Venganza/poder\n[3] Protección\n[4] Sin motivación clara\n> ";
    usuarioVector[6] = leerOpcion(0,4);
}

// ===============================
// PREGUNTAS EXTRA ALEATORIAS
// ===============================
void hacerPreguntasExtra() {
    int numExtras = rand() % 3 + 1; // 1 o 2 preguntas
    for (int i = 0; i < numExtras; i++) {
        int tipo = rand() % 3;      // para escoger que pregunta hacer
        switch (tipo) {
            case 0: {
                cout << "Extra: ¿Ha ayudado activamente a otras personas? (s/n): ";
                char r = leerCharOpcional({'s','n'});
                if (r == 's') usuarioVector[5] += 1;
                else usuarioVector[5] -= 1;
                if (usuarioVector[5] < 0) usuarioVector[5] = 0;
                if (usuarioVector[5] > 6) usuarioVector[5] = 6;
                break;
            }
            case 1: {
                cout << "Extra: ¿Es una persona calmada incluso en batallas? (s/n): ";
                char r = leerCharOpcional({'s','n'});
                if (r == 's' && usuarioVector[4] != 4) usuarioVector[4] = 3; 
                break;
            }
            case 2: {
                cout << "Extra: ¿Lucha principalmente por ideales personales? (s/n): ";
                char r = leerCharOpcional({'s','n'});
                if (r == 's') usuarioVector[6] = 1;
                break;
            }
        }
    }
}// === FIN DE PREGUNTAS ===


double calcularDistancia(const int v1[7], const int v2[7]) {
    double suma = 0;
    for (int i = 0; i < 7; i++) {
        double d = v1[i] - v2[i];
        suma += d * d;
    }
    return sqrt(suma);
}// === FIN de calcularDistancia ===

void recomendarPersonaje() {
    string mejorNombre;
    double mejorDistancia = 1e9;
    for (auto &p : basePersonajes) {
        double d = calcularDistancia(usuarioVector, p.vector);
        if (d < mejorDistancia) {
            mejorDistancia = d;
            mejorNombre = p.nombre;
        }
    }
    cout << "\n?? El personaje más cercano es: " << mejorNombre 
         << " (distancia: " << mejorDistancia << ")\n";
}

int main() {
    srand(time(0));
    inicializarBasePersonajes();
    hacerPreguntasBase();
    hacerPreguntasExtra();
    recomendarPersonaje();
    return 0;
}




