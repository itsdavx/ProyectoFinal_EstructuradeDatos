#ifndef GESTOR_PROCESOS_H
#define GESTOR_PROCESOS_H

#include <string>
#include "Proceso.h"
#include "Persistencia.h"

#include "../estructuras/ColaProcesos.h"
#include "../estructuras/PilaProcesos.h"
#include "../estructuras/ListaProcesos.h"
#include "../estructuras/HashMapProcesos.h"

using namespace std;

class GestorProcesos {
private:
    ColaProcesos colaPendientes;
    ListaProcesos listaProcesos;
    HashMapProcesos mapaProcesos;
    PilaProcesos pilaDeshacer;

    Persistencia persistencia;
    int siguienteId;

public:
    GestorProcesos();

    void registrarProceso(const string& nombre, const string& descripcion, int prioridad);
    void ejecutarProceso();
    void eliminarProceso(int id);

    void mostrarProcesosPendientes() const;
    void mostrarHistorial() const;
    void buscarProcesoPorId(int id) const;

    void deshacerUltimaAccion();
};

#endif
