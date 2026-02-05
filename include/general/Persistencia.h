#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include "../estructuras/ColaProcesos.h"
#include "../estructuras/PilaProcesos.h"
#include "../estructuras/ListaProcesos.h"
#include "Proceso.h"
#include <string>

class Persistencia {
private:
    const std::string rutaProcesos = "data/procesos.csv";
    const std::string rutaHistorial = "data/historial.csv";

public:
    void guardarProceso(const Proceso& proceso);
    void actualizarProceso(const Proceso& proceso);

    void cargarProcesos(ListaProcesos& lista,
                        ColaProcesos& cola,
                        HashMapProcesos& mapa,
                        int& siguienteId);

    void guardarHistorial(const PilaProcesos& pila);
    void cargarHistorial(PilaProcesos& pila);
};

#endif
