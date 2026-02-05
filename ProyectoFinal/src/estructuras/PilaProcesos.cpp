#include "../../include/estructuras/PilaProcesos.h"

#include <stdexcept>
#include <iomanip>

// Constructor y Destructor
PilaProcesos::PilaProcesos() : cima(nullptr) {}
PilaProcesos::~PilaProcesos() {
    while (!estaVacia()) desapilar();
}

// Implementacion de metodos
bool PilaProcesos::estaVacia() const { 
    return cima == nullptr; 
}

void PilaProcesos::apilar(const Proceso& proceso) {
    Nodo* nuevo = new Nodo(proceso);
    nuevo->siguiente = cima;
    cima = nuevo;
}

Proceso PilaProcesos::desapilar() {
    if (estaVacia()) throw runtime_error("La pila esta vacia");
    Nodo* temp = cima;
    Proceso p = temp->proceso;
    cima = cima->siguiente;
    delete temp;
    return p;
}

void PilaProcesos::mostrar() const {
    if (estaVacia()) {
        cout << "No hay acciones registradas.\n";
        return;
    }

    Nodo* actual = cima;

    while (actual) {

        string estadoStr;
        switch (actual->proceso.getEstado()) {
            case EstadoProceso::PENDIENTE:      estadoStr = "PENDIENTE"; break;
            case EstadoProceso::EN_EJECUCION:   estadoStr = "EN_EJECUCION"; break;
            case EstadoProceso::EJECUTADO:      estadoStr = "EJECUTADO"; break;
            case EstadoProceso::ELIMINADO:      estadoStr = "ELIMINADO"; break;
        }

        cout << left
             << setw(5)  << "ID:"
             << setw(4)  << actual->proceso.getId() << " | "
             << setw(10) << "Nombre:"
             << setw(35) << actual->proceso.getNombre() << " | "
             << setw(14) << "Descripcion:"
             << setw(45) << actual->proceso.getDescripcion() << " | "
             << setw(8)  << "Estado:"
             << setw(12) << estadoStr
             << endl;

        actual = actual->siguiente;
    }
}