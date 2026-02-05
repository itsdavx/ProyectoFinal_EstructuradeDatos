#ifndef COLA_PROCESOS_H
#define COLA_PROCESOS_H

#include "../general/Proceso.h"
#include <iostream>
#include <stdexcept>

using namespace std;

class ColaProcesos {
private:
    struct Nodo {
        Proceso proceso;
        Nodo* siguiente;
    };

    Nodo* frente;
    Nodo* final;

public:
    ColaProcesos();

    bool estaVacia() const;
    void encolar(const Proceso& proceso);
    void encolarAlFrente(const Proceso& proceso); // Para revertir
    Proceso desencolarValido();                   // Ignora procesos eliminados
    void mostrar() const;
void actualizarEstado(int id, EstadoProceso nuevoEstado); // sincroniza cola

    ~ColaProcesos();
};

#endif
