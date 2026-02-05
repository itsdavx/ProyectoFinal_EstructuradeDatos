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
    if (estaVacia()) throw std::runtime_error("Cola vacía");
    Nodo* temp = frente;
    Proceso proceso = temp->proceso;
    frente = frente->siguiente;
    if (!frente) final = nullptr;
    delete temp;
    return proceso;
}

void ColaProcesos::mostrar() const {
    if (estaVacia()) {
        std::cout << "No hay procesos pendientes.\n";
        return;
    }
    Nodo* actual = frente;
    std::cout << "\n--- Procesos Pendientes ---\n";
    while (actual) {
        std::cout << "ID: " << actual->proceso.getId()
                  << " | Nombre: " << actual->proceso.getNombre()
                  << " | Prioridad: " << actual->proceso.getPrioridad()
                  << " | Estado: ";
        switch (actual->proceso.getEstado()) {
            case EstadoProceso::PENDIENTE: std::cout << "PENDIENTE"; break;
            case EstadoProceso::EJECUTADO: std::cout << "EJECUTADO"; break;
            case EstadoProceso::ELIMINADO: std::cout << "ELIMINADO"; break;
            case EstadoProceso::EN_EJECUCION: std::cout << "EN_EJECUCION"; break;
        }
        std::cout << "\n";
        actual = actual->siguiente;
    }
}

bool ColaProcesos::eliminarPorId(int id) {
    Nodo* actual = frente;
    Nodo* anterior = nullptr;

    while (actual) {
        if (actual->proceso.getId() == id) {
            if (anterior) anterior->siguiente = actual->siguiente;
            else frente = actual->siguiente;
            if (actual == final) final = anterior;
            delete actual;
            return true;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    return false;
}
