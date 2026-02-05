#include "../../include/general/Persistencia.h"
#include <iostream>
#include <fstream>

using namespace std;

void Persistencia::guardarProceso(const Proceso& p) {
    ofstream archivo(rutaProcesos, ios::app);
    if (archivo.is_open()) {
        archivo << p.getId() << "," << p.getNombre() << "," 
                << p.getDescripcion() << "," << p.getPrioridad() << "," 
                << static_cast<int>(p.getEstado()) << "\n";
        archivo.close();
    }
}

void Persistencia::actualizarProceso(const Proceso& p) {
    // Leer todos y sobrescribir con el actualizado
    ifstream archivoLectura(rutaProcesos);
    ofstream archivoTemp("data/temp.csv");
    string linea;

    while (getline(archivoLectura, linea)) {
        stringstream ss(linea);
        string idStr;
        getline(ss, idStr, ',');
        int id = stoi(idStr);
        if (id == p.getId()) {
            archivoTemp << p.getId() << "," << p.getNombre() << ","
                        << p.getDescripcion() << "," << p.getPrioridad() << ","
                        << static_cast<int>(p.getEstado()) << "\n";
        } else {
            archivoTemp << linea << "\n";
        }
    }
    archivoLectura.close();
    archivoTemp.close();

    remove(rutaProcesos.c_str());
    rename("data/temp.csv", rutaProcesos.c_str());
}

void Persistencia::cargarProcesos(ListaProcesos& lista,
                                   ColaProcesos& cola,
                                   HashMapProcesos& mapa,
                                   int& siguienteId) {
    ifstream archivo(rutaProcesos);
    string linea;
    int maxId = 0;

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
        int estadoInt = stoi(estadoStr);

        Proceso p(id, nombre, descripcion, prioridad);
        p.setEstado(static_cast<EstadoProceso>(estadoInt));

        lista.agregar(p);
        mapa.insertar(id, p);
        if (p.getEstado() == EstadoProceso::PENDIENTE)
            cola.encolar(p);

        if (id > maxId) maxId = id;
    }

    siguienteId = maxId + 1;
}
