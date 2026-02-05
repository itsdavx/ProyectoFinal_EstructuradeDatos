#include "../../include/estructuras/PilaProcesos.h"
#include <stdexcept>

PilaProcesos::PilaProcesos() : cima(nullptr) {}
PilaProcesos::~PilaProcesos() {
    while (!estaVacia()) desapilar();
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
    if (estaVacia()) throw std::runtime_error("Pila vacía");
    Nodo* temp = cima;
    Proceso proceso = temp->proceso;
    cima = cima->siguiente;
    delete temp;
    return proceso;
}

void PilaProcesos::mostrar() const {
    if (estaVacia()) {
        std::cout << "No hay acciones en la pila.\n";
        return;
    }
    Nodo* actual = cima;
    while (actual) {
        std::cout << "ID: " << actual->proceso.getId()
                  << " | Nombre: " << actual->proceso.getNombre()
                  << "\n";
        actual = actual->siguiente;
    }
}
