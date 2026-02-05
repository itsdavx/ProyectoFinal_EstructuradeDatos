#include "../../include/estructuras/ColaProcesos.h"

ColaProcesos::ColaProcesos() : frente(nullptr), final(nullptr) { }

ColaProcesos::~ColaProcesos() {
    while (frente != nullptr) {
        Nodo* temp = frente;
        frente = frente->siguiente;
        delete temp;
    }
}

bool ColaProcesos::estaVacia() const {
    return frente == nullptr;
}

void ColaProcesos::encolar(const Proceso& proceso) {
    Nodo* nuevo = new Nodo{ proceso, nullptr };
    if (estaVacia()) {
        frente = final = nuevo;
    } else {
        final->siguiente = nuevo;
        final = nuevo;
    }
}

// Pone el proceso al frente de la cola (para revertidos)
void ColaProcesos::encolarAlFrente(const Proceso& proceso) {
    Nodo* nuevo = new Nodo{ proceso, frente };
    frente = nuevo;
    if (final == nullptr) final = nuevo;
}

// Desencola el primer proceso que no esté eliminado
Proceso ColaProcesos::desencolarValido() {
    if (estaVacia()) throw runtime_error("No hay procesos pendientes");

    Nodo* actual = frente;
    Nodo* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->proceso.getEstado() == EstadoProceso::PENDIENTE) {
            if (anterior == nullptr) frente = actual->siguiente;
            else anterior->siguiente = actual->siguiente;

            if (actual == final) final = anterior;

            Proceso p = actual->proceso;
            delete actual;
            return p;
        }
        anterior = actual;
        actual = actual->siguiente;
    }

    throw runtime_error("No hay procesos pendientes");
}

void ColaProcesos::mostrar() const {
    if (estaVacia()) {
        cout << "No hay procesos pendientes.\n";
        return;
    }

    Nodo* actual = frente;
    while (actual != nullptr) {
        if (actual->proceso.getEstado() != EstadoProceso::ELIMINADO) {
            cout << "ID: " << actual->proceso.getId()
                 << " | Nombre: " << actual->proceso.getNombre()
                 << " | Descripcion: " << actual->proceso.getDescripcion()
                 << " | Estado: ";
            switch (actual->proceso.getEstado()) {
                case EstadoProceso::PENDIENTE: cout << "PENDIENTE"; break;
                case EstadoProceso::EN_EJECUCION: cout << "EN_EJECUCION"; break;
                case EstadoProceso::EJECUTADO: cout << "EJECUTADO"; break;
                case EstadoProceso::ELIMINADO: cout << "ELIMINADO"; break;
            }
            cout << endl;
        }
        actual = actual->siguiente;
    }
}
void ColaProcesos::actualizarEstado(int id, EstadoProceso nuevoEstado) {
    Nodo* actual = frente;
    while (actual != nullptr) {
        if (actual->proceso.getId() == id) {
            actual->proceso.setEstado(nuevoEstado);
            return;
        }
        actual = actual->siguiente;
    }
}
