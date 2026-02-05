#include "../../include/estructuras/ColaProcesos.h"
#include <stdexcept>

ColaProcesos::ColaProcesos() : frente(nullptr), final(nullptr) {}

ColaProcesos::~ColaProcesos() {
    while (!estaVacia()) {
        desencolar();
    }
}

bool ColaProcesos::estaVacia() const {
    return frente == nullptr;
}

void ColaProcesos::encolar(const Proceso& proceso) {
    Nodo* nuevo = new Nodo(proceso);
    if (estaVacia()) {
        frente = final = nuevo;
    } else {
        final->siguiente = nuevo;
        final = nuevo;
    }
}

Proceso ColaProcesos::desencolar() {
    if (estaVacia())
        throw runtime_error("La cola está vacía");

    Nodo* temp = frente;
    Proceso p = temp->proceso;
    frente = frente->siguiente;
    if (frente == nullptr)
        final = nullptr;
    delete temp;
    return p;
}

void ColaProcesos::mostrar() const {
    if (estaVacia()) {
        cout << "No hay procesos pendientes.\n";
        return;
    }
    Nodo* actual = frente;
    while (actual) {
        cout << "ID: " << actual->proceso.getId()
             << " | Nombre: " << actual->proceso.getNombre()
             << " | Prioridad: " << actual->proceso.getPrioridad() << "\n";
        actual = actual->siguiente;
    }
}
