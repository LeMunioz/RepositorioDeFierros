% recorrido preorden

preorden(nil, []).

preorden(arbol(V, I, D), Lista) :-
    preorden(I, LI),
    preorden(D, LD),
    append([V|LI], LD, Lista).
