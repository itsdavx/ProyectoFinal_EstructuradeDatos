#include "../../include/estructuras/HashMapProcesos.h"
#include <stdexcept>

HashMapProcesos::HashMapProcesos() {
    for (int i = 0; i < TAM; i++)
        tabla[i] = nullptr;
}

HashMapProcesos::~HashMapProcesos() {
    for (int i = 0; i < TAM; i++) {
        Nodo* actual = tabla[i];
        while (actual) {
            Nodo* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }
}

void HashMapProcesos::insertar(int clave, const Proceso& proceso) {
    int idx = funcionHash(clave);
    tabla[idx] = new Nodo(clave, proceso, tabla[idx]);
}

bool HashMapProcesos::existe(int clave) const {
    int idx = funcionHash(clave);
    Nodo* actual = tabla[idx];
    while (actual) {
        if (actual->clave == clave) return true;
        actual = actual->siguiente;
    }
    return false;
}

Proceso HashMapProcesos::obtener(int clave) const {
    int idx = funcionHash(clave);
    Nodo* actual = tabla[idx];
    while (actual) {
        if (actual->clave == clave) return actual->proceso;
        actual = actual->siguiente;
    }
    throw runtime_error("Proceso no encontrado");
}

void HashMapProcesos::actualizar(int clave, const Proceso& proceso) {
    int idx = funcionHash(clave);
    Nodo* actual = tabla[idx];
    while (actual) {
        if (actual->clave == clave) {
            actual->proceso.setEstado(proceso.getEstado());
            return;
        }
        actual = actual->siguiente;
    }
}

void HashMapProcesos::eliminar(int clave) {
    int idx = funcionHash(clave);
    Nodo* actual = tabla[idx];
    Nodo* prev = nullptr;
    while (actual) {
        if (actual->clave == clave) {
            if (prev) prev->siguiente = actual->siguiente;
            else tabla[idx] = actual->siguiente;
            delete actual;
            return;
        }
        prev = actual;
        actual = actual->siguiente;
    }
}
