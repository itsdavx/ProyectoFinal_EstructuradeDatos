#include "../../include/general/Persistencia.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void Persistencia::guardarProceso(const Proceso& proceso) {
    ofstream archivo(rutaProcesos, ios::app);
    if (!archivo.is_open()) return;

    archivo << proceso.getId() << ","
            << proceso.getNombre() << ","
            << proceso.getDescripcion() << ","
            << proceso.getPrioridad() << ","
            << static_cast<int>(proceso.getEstado())
            << "\n";
    archivo.close();
}

void Persistencia::actualizarProceso(const Proceso& proceso) {
    // Leer todo y reescribir, reemplazando la línea del proceso
    ifstream entrada(rutaProcesos);
    ofstream salida("data/temp.csv");
    string linea;

    while (getline(entrada, linea)) {
        stringstream ss(linea);
        string idStr;
        getline(ss, idStr, ',');

        if (stoi(idStr) == proceso.getId()) {
            salida << proceso.getId() << ","
                   << proceso.getNombre() << ","
                   << proceso.getDescripcion() << ","
                   << proceso.getPrioridad() << ","
                   << static_cast<int>(proceso.getEstado()) << "\n";
        } else {
            salida << linea << "\n";
        }
    }
    entrada.close();
    salida.close();
    remove(rutaProcesos.c_str());
    rename("data/temp.csv", rutaProcesos.c_str());
}

void Persistencia::cargarProcesos(ListaProcesos& lista,
                                   ColaProcesos& cola,
                                   HashMapProcesos& mapa,
                                   int& siguienteId) {
    ifstream archivo(rutaProcesos);
    if (!archivo.is_open()) return;

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string idStr, nombre, descripcion, prioridadStr, estadoStr;

        getline(ss, idStr, ',');
        getline(ss, nombre, ',');
        getline(ss, descripcion, ',');
        getline(ss, prioridadStr, ',');
        getline(ss, estadoStr, ',');

        int id = stoi(idStr);
        int prioridad = stoi(prioridadStr);
        EstadoProceso estado = static_cast<EstadoProceso>(stoi(estadoStr));

        Proceso p(id, nombre, descripcion, prioridad);
        p.setEstado(estado);

        lista.agregar(p);
        mapa.insertar(id, p);
        if (estado == EstadoProceso::PENDIENTE)
            cola.encolar(p);

        if (id >= siguienteId) siguienteId = id + 1;
    }

    archivo.close();
}
