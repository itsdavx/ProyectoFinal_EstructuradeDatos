#include "../../include/estructuras/ListaProcesos.h"

ListaProcesos::ListaProcesos() : cabeza(nullptr) {}
ListaProcesos::~ListaProcesos() {
    while (cabeza != nullptr) {
        Nodo* temp = cabeza;
        cabeza = cabeza->siguiente;
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
    while (actual->siguiente != nullptr) actual = actual->siguiente;
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
    if (!cabeza) {
        cout << "No hay procesos registrados.\n";
        return;
    }
    Nodo* actual = cabeza;
    while (actual) {
        cout << "ID: " << actual->proceso.getId()
             << " | Nombre: " << actual->proceso.getNombre()
             << " | Descripcion: " << actual->proceso.getDescripcion()
             << " | Estado: " << static_cast<int>(actual->proceso.getEstado())
             << endl;
        actual = actual->siguiente;
    }
}

void ListaProcesos::mostrarPorEstado(EstadoProceso estado) const {
    Nodo* actual = cabeza;
    bool encontrado = false;
    while (actual) {
        if (actual->proceso.getEstado() == estado) {
            cout << "ID: " << actual->proceso.getId()
                 << " | Nombre: " << actual->proceso.getNombre()
                 << " | Descripcion: " << actual->proceso.getDescripcion()
                 << endl;
            encontrado = true;
        }
        actual = actual->siguiente;
    }
    if (!encontrado) cout << "No hay procesos con ese estado.\n";
}
