class Nodo {
    int valor;
    Nodo izquierda;
    Nodo derecha;

    Nodo(int valor) {
        this.valor = valor;
    }
}

public class Preorden {

    static void preorden(Nodo n) {
        if (n == null)
            return;

        System.out.print(n.valor + " ");
        preorden(n.izquierda);
        preorden(n.derecha);
    }

    public static void main(String[] args) {

        Nodo raiz = new Nodo(1);
        raiz.izquierda = new Nodo(2);
        raiz.derecha = new Nodo(3);
        raiz.izquierda.izquierda = new Nodo(4);
        raiz.izquierda.derecha = new Nodo(5);

        preorden(raiz);
    }
}