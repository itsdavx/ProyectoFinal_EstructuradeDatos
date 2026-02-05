#ifndef LISTA_PROCESOS_H
#define LISTA_PROCESOS_H

#include "../general/Proceso.h"
#include "ColaProcesos.h"
#include <iostream>

using namespace std;

class ListaProcesos
{
private:

    struct Nodo {
        Proceso proceso;
        Nodo* siguiente;
        Nodo(const Proceso& p) : proceso(p), siguiente(nullptr) {}
    };

    Nodo* cabeza;

public:
    // Constructor y Destructor
    ListaProcesos();
    ~ListaProcesos();

    // Métodos
    void agregar(const Proceso& proceso);
    void actualizar(const Proceso& proceso);
    void mostrar() const;
    void mostrarPorEstado(EstadoProceso estado) const;
    void reconstruirColaPendientes(ColaProcesos& cola) const;
};

#endif