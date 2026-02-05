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
        Nodo *siguiente;
    };

    Nodo *frente;
    Nodo *final;

public:

    // Constructor y Destructor
    ColaProcesos();
    ~ColaProcesos();

    // Métodos
    void limpiar();
    bool estaVacia() const;
    void encolar(const Proceso &proceso);
    void encolarAlFrente(const Proceso &proceso); 
    Proceso desencolarValido();
    void mostrar() const;
    void actualizarEstado(int id, EstadoProceso nuevoEstado);
};

#endif