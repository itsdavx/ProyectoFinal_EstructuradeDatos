#ifndef LISTA_PROCESOS_H
#define LISTA_PROCESOS_H

#include "../include/general/Proceso.h"
#include <iostream>

class ListaProcesos {
private:
    struct Nodo {
        Proceso proceso;
        Nodo* siguiente;
        Nodo(const Proceso& p) : proceso(p), siguiente(nullptr) {}
    };

    Nodo* cabeza;

public:
    ListaProcesos();
    ~ListaProcesos();

    void agregar(const Proceso& proceso);
    void actualizar(const Proceso& proceso);
    void mostrar() const;
    void mostrarPorEstado(EstadoProceso estado) const;
};

#endif
