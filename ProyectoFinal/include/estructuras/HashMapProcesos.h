#ifndef HASHMAP_PROCESOS_H
#define HASHMAP_PROCESOS_H

#include "../general/Proceso.h"
#include <iostream>
using namespace std;

class HashMapProcesos {
private:
    struct Nodo {
        int clave;
        Proceso proceso;
        Nodo* siguiente;
        Nodo(int c, const Proceso& p, Nodo* sig) : clave(c), proceso(p), siguiente(sig) {}
    };
    static const int TAM = 100;
    Nodo* tabla[TAM];

    int funcionHash(int clave) const { return clave % TAM; }

public:
    HashMapProcesos();
    ~HashMapProcesos();
    void insertar(int clave, const Proceso& proceso);
    bool existe(int clave) const;
    Proceso obtener(int clave) const;
    void actualizar(int clave, const Proceso& proceso);
    void eliminar(int clave);
};

#endif
