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

    // Operaciones principales
    void registrarProceso(const string& nombre, const string& descripcion);
    void ejecutarProceso();
    void eliminarProceso(int id);

    // Consultas
    void mostrarProcesosPendientes() const;
    void mostrarHistorial() const;
    void mostrarFlujoEjecucion() const;
    void buscarProcesoPorId(int id) const;

    // Deshacer
    void deshacerUltimaAccion();
};

#endif
