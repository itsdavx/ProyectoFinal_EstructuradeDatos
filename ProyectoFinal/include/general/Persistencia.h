#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include <string>

#include "Proceso.h"

#include "../estructuras/ColaProcesos.h"
#include "../estructuras/PilaProcesos.h"
#include "../estructuras/ListaProcesos.h"
#include "../estructuras/HashMapProcesos.h"



class Persistencia {
private:

    const std::string rutaProcesos = "data/procesos.csv";
    const std::string rutaHistorial = "data/historial.csv";

    std::string estadoToString(EstadoProceso estado) const;

public:

    // Constructor
    Persistencia() = default;

    // Métodos
    void cargarProcesos(ListaProcesos& lista, ColaProcesos& cola, HashMapProcesos& mapa, int& siguienteId);
    void guardarProceso(const Proceso& p);
    void actualizarProceso(const Proceso& p);
    void registrarEnHistorial(const std::string& accion, const Proceso& p);
    void mostrarHistorial() const;
};

#endif