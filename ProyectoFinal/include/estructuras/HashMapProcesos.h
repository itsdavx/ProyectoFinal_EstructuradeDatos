#ifndef HASHMAP_PROCESOS_H
#define HASHMAP_PROCESOS_H

#include "../general/Proceso.h"
#include <iostream>

using namespace std;

class HashMapProcesos {
private:

    static const int TAM = 101;

    struct Nodo {
        int clave;
        Proceso proceso;
        Nodo* siguiente;
        Nodo(int c, const Proceso& p, Nodo* sig) : clave(c), proceso(p), siguiente(sig) {}
    };

    Nodo* tabla[TAM];

    int funcionHash(int clave) const;

public:

    // Constructor y Destructor
    HashMapProcesos();
    ~HashMapProcesos();

    // Métodos
    void insertar(int clave, const Proceso& proceso);
    bool existe(int clave) const;
    Proceso obtener(int clave) const;
    void actualizar(int clave, const Proceso& proceso);
    void eliminar(int clave);
};

#endif
