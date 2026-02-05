#include "../../include/estructuras/HashMapProcesos.h"

HashMapProcesos::HashMapProcesos() {
    for (int i = 0; i < TAM; i++) tabla[i] = nullptr;
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

int HashMapProcesos::funcionHash(int clave) const {
    return clave % TAM;
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
    throw std::runtime_error("Proceso no encontrado");
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
    Nodo* anterior = nullptr;
    while (actual) {
        if (actual->clave == clave) {
            if (!anterior) tabla[idx] = actual->siguiente;
            else anterior->siguiente = actual->siguiente;
            delete actual;
            return;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
}
