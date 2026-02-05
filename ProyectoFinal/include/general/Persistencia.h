#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include "../estructuras/ColaProcesos.h"
#include "../estructuras/PilaProcesos.h"
#include "../estructuras/ListaProcesos.h"
#include "../estructuras/HashMapProcesos.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Persistencia {
private:
    const string rutaProcesos = "data/procesos.csv";
    const string rutaHistorial = "data/historial.csv";

public:
    void guardarProceso(const Proceso& p);
    void actualizarProceso(const Proceso& p);
    void cargarProcesos(ListaProcesos& lista,
                        ColaProcesos& cola,
                        HashMapProcesos& mapa,
                        int& siguienteId);
};

#endif
