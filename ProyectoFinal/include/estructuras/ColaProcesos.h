#ifndef COLA_PROCESOS_H
#define COLA_PROCESOS_H

#include "../general/Proceso.h"
#include <iostream>
using namespace std;

class ColaProcesos {
private:
    struct Nodo {
        Proceso proceso;
        Nodo* siguiente;
        Nodo(const Proceso& p) : proceso(p), siguiente(nullptr) {}
    };

    Nodo* frente;
    Nodo* final;

public:
    ColaProcesos();
    ~ColaProcesos();

    bool estaVacia() const;
    void encolar(const Proceso& proceso);
    Proceso desencolar();
    void mostrar() const;
};

#endif
