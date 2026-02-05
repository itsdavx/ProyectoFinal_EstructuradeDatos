#include "../../include/estructuras/ListaProcesos.h"

ListaProcesos::ListaProcesos() : cabeza(nullptr) {}
ListaProcesos::~ListaProcesos() {
    Nodo* actual = cabeza;
    while (actual) {
        Nodo* temp = actual;
        actual = actual->siguiente;
        delete temp;
    }
}

void ListaProcesos::agregar(const Proceso& proceso) {
    Nodo* nuevo = new Nodo(proceso);
    if (!cabeza) {
        cabeza = nuevo;
        return;
    }
    Nodo* actual = cabeza;
    while (actual->siguiente) actual = actual->siguiente;
    actual->siguiente = nuevo;
}

void ListaProcesos::actualizar(const Proceso& proceso) {
    Nodo* actual = cabeza;
    while (actual) {
        if (actual->proceso.getId() == proceso.getId()) {
            actual->proceso.setEstado(proceso.getEstado());
            return;
        }
        actual = actual->siguiente;
    }
}

void ListaProcesos::mostrar() const {
    if (!cabeza) { std::cout << "No hay procesos registrados.\n"; return; }
    Nodo* actual = cabeza;
    while (actual) {
        std::cout << "ID: " << actual->proceso.getId()
                  << " | Nombre: " << actual->proceso.getNombre()
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

void ListaProcesos::mostrarPorEstado(EstadoProceso estado) const {
    Nodo* actual = cabeza;
    bool encontrado = false;
    while (actual) {
        if (actual->proceso.getEstado() == estado) {
            std::cout << "ID: " << actual->proceso.getId()
                      << " | Nombre: " << actual->proceso.getNombre()
                      << "\n";
            encontrado = true;
        }
        actual = actual->siguiente;
    }
    if (!encontrado) std::cout << "No hay procesos con ese estado.\n";
}
