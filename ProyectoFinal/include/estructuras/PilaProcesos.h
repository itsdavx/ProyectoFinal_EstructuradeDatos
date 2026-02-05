#ifndef PILA_PROCESOS_H
#define PILA_PROCESOS_H

#include "../general/Proceso.h"
#include <iostream>

using namespace std;

class PilaProcesos {
private:

    struct Nodo {
        Proceso proceso;
        Nodo* siguiente;
        Nodo(const Proceso& p) : proceso(p), siguiente(nullptr) {}
    };
    Nodo* cima;

public:

    // Constructor y Destructor
    PilaProcesos();
    ~PilaProcesos();

    // Métodos
    bool estaVacia() const;
    void apilar(const Proceso& proceso);
    Proceso desapilar();
    void mostrar() const;
};

#endif