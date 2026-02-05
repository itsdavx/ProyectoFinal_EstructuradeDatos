#include "../include/general/GestorProcesos.h"
#include <iostream>

using namespace std;

// Constructor
GestorProcesos::GestorProcesos() : siguienteId(1) {
    persistencia.cargarProcesos(listaProcesos, colaPendientes, mapaProcesos, siguienteId);
}

// Implementacion de metodos
void GestorProcesos::registrarProceso(const string &nombre, const string &descripcion) {
    Proceso nuevo(siguienteId++, nombre, descripcion);

    colaPendientes.encolar(nuevo);
    listaProcesos.agregar(nuevo);
    mapaProcesos.insertar(nuevo.getId(), nuevo);

    persistencia.guardarProceso(nuevo);
    persistencia.registrarEnHistorial("REGISTRAR", nuevo);
}

void GestorProcesos::ejecutarProceso() {
    if (colaPendientes.estaVacia()) {
        cout << "No hay procesos pendientes.\n";
        return;
    }

    Proceso proceso = colaPendientes.desencolarValido();

    // Estado: EN_EJECUCION
    proceso.setEstado(EstadoProceso::EN_EJECUCION);
    listaProcesos.actualizar(proceso);
    mapaProcesos.actualizar(proceso.getId(), proceso);
    persistencia.actualizarProceso(proceso);
    persistencia.registrarEnHistorial("EJECUCION", proceso);

    // Estado: EJECUTADO
    proceso.setEstado(EstadoProceso::EJECUTADO);
    listaProcesos.actualizar(proceso);
    mapaProcesos.actualizar(proceso.getId(), proceso);
    pilaDeshacer.apilar(proceso);
    persistencia.actualizarProceso(proceso);
    persistencia.registrarEnHistorial("EJECUTADO", proceso);

    //Mostrar en consolas
    cout << "\n---------------------- EJECUCION DE PROCESO ---------------------" << endl;
    cout << "Ejecutando proceso..." << endl;
    cout << "Proceso ejecutado: " << proceso.getNombre() << endl;
    cout << "Ejecucion completada." << endl;
    cout << "-----------------------------------------------------------------" << endl;
}

void GestorProcesos::eliminarProceso(int id) {
    if (!mapaProcesos.existe(id)) {
        cout << "Proceso no encontrado.\n";
        return;
    }

    Proceso proceso = mapaProcesos.obtener(id);

    // Validar Eliminado
    if (proceso.getEstado() == EstadoProceso::ELIMINADO) {
        cout << "El proceso ya esta eliminado.\n";
        return;
    }

    // Validar Ejecutado
    if (proceso.getEstado() == EstadoProceso::EJECUTADO) {
        cout << "No se puede eliminar un proceso que ya fue ejecutado.\n";
        return;
    }

    proceso.setEstado(EstadoProceso::ELIMINADO);

    listaProcesos.actualizar(proceso);
    mapaProcesos.actualizar(id, proceso);
    colaPendientes.actualizarEstado(id, EstadoProceso::ELIMINADO);
    pilaDeshacer.apilar(proceso);

    persistencia.actualizarProceso(proceso);
    persistencia.registrarEnHistorial("ELIMINADO", proceso);

    cout << "Eliminando proceso...\n";
    cout << "Proceso eliminado: " << proceso.getNombre() << endl;
    cout << "Eliminacion completada.\n";
}

void GestorProcesos::mostrarProcesosPendientes() const {
    colaPendientes.mostrar();
}

void GestorProcesos::mostrarHistorial() const {
    listaProcesos.mostrarPorEstado(EstadoProceso::EJECUTADO);
}

void GestorProcesos::mostrarFlujoEjecucion() const {
    persistencia.mostrarHistorial();
}

void GestorProcesos::buscarProcesoPorId(int id) const {
    if (!mapaProcesos.existe(id)) {
        cout << endl;
        cout << "Proceso no encontrado.\n";
        cout << "--------------------------------------------------------------------------------------------------" << endl;
        return;
    }

    Proceso p = mapaProcesos.obtener(id);

    // Validar Eliminado
    if (p.getEstado() == EstadoProceso::ELIMINADO) {
        cout << endl;
        cout << "Proceso no encontrado.\n";
        cout << "--------------------------------------------------------------------------------------------------" << endl;
        return;
    }

    cout << "\n--------------------------------------------------------------------------------------------------" << endl;
    cout << "ID: " << p.getId() << " | Nombre: " << p.getNombre() << " | Descripcion: " << p.getDescripcion() << " | Estado: " << estadoToString(p.getEstado()) << endl;
    cout << "--------------------------------------------------------------------------------------------------" << endl;
}

void GestorProcesos::deshacerUltimaAccion() {
    if (pilaDeshacer.estaVacia())
    {
        cout << "No hay acciones para deshacer.\n";
        return;
    }

    Proceso proceso = pilaDeshacer.desapilar();

    if (proceso.getEstado() == EstadoProceso::EJECUTADO || proceso.getEstado() == EstadoProceso::ELIMINADO) {
        proceso.setEstado(EstadoProceso::PENDIENTE);
    }

    listaProcesos.actualizar(proceso);
    mapaProcesos.actualizar(proceso.getId(), proceso);

    colaPendientes = ColaProcesos();
    listaProcesos.reconstruirColaPendientes(colaPendientes);

    persistencia.actualizarProceso(proceso);
    persistencia.registrarEnHistorial("DESHECHO", proceso);

    cout << "Deshaciendo ultima accion..." << endl;
    cout << "Ultima accion deshecha correctamente." << endl;
}

//Metodo Auxiliar
string GestorProcesos::estadoToString(EstadoProceso estado) const {
    switch (estado) {
        case EstadoProceso::PENDIENTE: return "PENDIENTE";
        case EstadoProceso::EN_EJECUCION: return "EN_EJECUCION";
        case EstadoProceso::EJECUTADO: return "EJECUTADO";
        case EstadoProceso::ELIMINADO: return "ELIMINADO";
        default: return "DESCONOCIDO";
    }
}