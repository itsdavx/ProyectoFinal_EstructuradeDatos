#include "../../include/estructuras/PilaProcesos.h"
#include <stdexcept>

PilaProcesos::PilaProcesos() : cima(nullptr) {}

PilaProcesos::~PilaProcesos() {
    while (!estaVacia())
        desapilar();
}

bool PilaProcesos::estaVacia() const {
    return cima == nullptr;
}

void PilaProcesos::apilar(const Proceso& proceso) {
    Nodo* nuevo = new Nodo(proceso);
    nuevo->siguiente = cima;
    cima = nuevo;
}

Proceso PilaProcesos::desapilar() {
    if (estaVacia())
        throw runtime_error("La pila está vacía");
    Nodo* temp = cima;
    Proceso p = temp->proceso;
    cima = cima->siguiente;
    delete temp;
    return p;
}

void PilaProcesos::mostrar() const {
    if (estaVacia()) {
        cout << "No hay acciones en la pila.\n";
        return;
    }
    Nodo* actual = cima;
    while (actual) {
        cout << "ID: " << actual->proceso.getId()
             << " | Nombre: " << actual->proceso.getNombre() << "\n";
        actual = actual->siguiente;
    }
}
