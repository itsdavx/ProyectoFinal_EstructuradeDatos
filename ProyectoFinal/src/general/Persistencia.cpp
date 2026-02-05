#include "../../include/general/Persistencia.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

// Implementacion de metodos
string Persistencia::estadoToString(EstadoProceso estado) const {
    switch (estado) {
        case EstadoProceso::PENDIENTE: return "PENDIENTE";
        case EstadoProceso::EN_EJECUCION: return "EN_EJECUCION";
        case EstadoProceso::EJECUTADO: return "EJECUTADO";
        case EstadoProceso::ELIMINADO: return "ELIMINADO";
        default: return "DESCONOCIDO";
    }
}

void Persistencia::cargarProcesos(ListaProcesos& lista, ColaProcesos& cola, HashMapProcesos& mapa, int& siguienteId) {
    
    lista = ListaProcesos();
    cola = ColaProcesos();
    mapa = HashMapProcesos();

    ifstream archivo(rutaProcesos);
    string linea;
    int maxId = 0;

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string idStr, nombre, descripcion, estadoStr;
        getline(ss, idStr, ',');
        getline(ss, nombre, ',');
        getline(ss, descripcion, ',');
        getline(ss, estadoStr, ',');

        int id = stoi(idStr);
        EstadoProceso estado = EstadoProceso::PENDIENTE;
        if (estadoStr == "PENDIENTE") estado = EstadoProceso::PENDIENTE;
        else if (estadoStr == "EN_EJECUCION") estado = EstadoProceso::EN_EJECUCION;
        else if (estadoStr == "EJECUTADO") estado = EstadoProceso::EJECUTADO;
        else if (estadoStr == "ELIMINADO") estado = EstadoProceso::ELIMINADO;

        Proceso p(id, nombre, descripcion);
        p.setEstado(estado);

        lista.agregar(p);
        if (estado == EstadoProceso::PENDIENTE) {
            cola.encolar(p);
        }
        mapa.insertar(id, p);

        if (id > maxId) maxId = id;
    }
    siguienteId = maxId + 1;
}

void Persistencia::guardarProceso(const Proceso& p) {
    // Leer todos los procesos y sobrescribir el que coincide
    vector<Proceso> procesos;
    ifstream entrada(rutaProcesos);
    string linea;
    while (getline(entrada, linea)) {
        if (linea.empty()) continue;
        stringstream ss(linea);
        string idStr, nombre, descripcion, estadoStr;
        getline(ss, idStr, ',');
        getline(ss, nombre, ',');
        getline(ss, descripcion, ',');
        getline(ss, estadoStr, ',');

        int id = stoi(idStr);
        Proceso proc(id, nombre, descripcion);
        EstadoProceso estado = EstadoProceso::PENDIENTE;
        if (estadoStr == "PENDIENTE") estado = EstadoProceso::PENDIENTE;
        else if (estadoStr == "EN_EJECUCION") estado = EstadoProceso::EN_EJECUCION;
        else if (estadoStr == "EJECUTADO") estado = EstadoProceso::EJECUTADO;
        else if (estadoStr == "ELIMINADO") estado = EstadoProceso::ELIMINADO;

        proc.setEstado(estado);
        procesos.push_back(proc);
    }
    entrada.close();

    // Reemplazar o agregar el proceso
    bool reemplazado = false;
    for (auto& proc : procesos) {
        if (proc.getId() == p.getId()) {
            proc.setEstado(p.getEstado());
            reemplazado = true;
            break;
        }
    }
    if (!reemplazado) procesos.push_back(p);

    // Escribir todo nuevamente
    ofstream salida(rutaProcesos);
    for (const auto& proc : procesos) {
        salida << proc.getId() << "," 
                << proc.getNombre() << "," 
                << proc.getDescripcion() << "," 
                << estadoToString(proc.getEstado()) << "\n";
    }
}

void Persistencia::actualizarProceso(const Proceso& p) {
    guardarProceso(p); // sobrescribe
}

void Persistencia::registrarEnHistorial(const string& accion, const Proceso& p) {
    ofstream archivo(rutaHistorial, ios::app);
    if (!archivo) return;

    archivo << left
            << setw(15) << accion << " | "
            << setw(5)  << "ID:"
            << setw(4)  << p.getId() << " | "
            << setw(10) << "Nombre:"
            << setw(35) << p.getNombre() << " | "
            << setw(14) << "Descripcion:"
            << setw(45) << p.getDescripcion() << " | "
            << setw(8)  << "Estado:"
            << setw(12) << estadoToString(p.getEstado()) << " | "
            << '\n';
}

void Persistencia::mostrarHistorial() const {
    ifstream archivo(rutaHistorial);
    string linea;

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el historial.\n";
        return;
    }

    while (getline(archivo, linea)) {
        cout << linea << endl;
    }
}