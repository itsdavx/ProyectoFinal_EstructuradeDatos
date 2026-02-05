#include "../include/general/GestorProcesos.h"
#include <iostream>

using namespace std;

GestorProcesos::GestorProcesos() : siguienteId(1) {
    persistencia.cargarProcesos(listaProcesos, colaPendientes, mapaProcesos, siguienteId);
}

void GestorProcesos::registrarProceso(const string& nombre,
                                      const string& descripcion,
                                      int prioridad) {
    Proceso nuevo(siguienteId++, nombre, descripcion, prioridad);

    colaPendientes.encolar(nuevo);
    listaProcesos.agregar(nuevo);
    mapaProcesos.insertar(nuevo.getId(), nuevo);

    persistencia.guardarProceso(nuevo);

    cout << "Proceso registrado correctamente.\n";
}

void GestorProcesos::ejecutarProceso() {
    if (colaPendientes.estaVacia()) {
        cout << "No hay procesos pendientes.\n";
        return;
    }

    Proceso proceso = colaPendientes.desencolar();
    proceso.setEstado(EstadoProceso::EJECUTADO);

    listaProcesos.actualizar(proceso);
    mapaProcesos.actualizar(proceso.getId(), proceso);
    pilaDeshacer.apilar(proceso);

    persistencia.actualizarProceso(proceso);

    cout << "Proceso ejecutado: " << proceso.getNombre() << endl;
}

void GestorProcesos::eliminarProceso(int id) {
    if (!mapaProcesos.existe(id)) {
        cout << "Proceso no encontrado.\n";
        return;
    }

    Proceso proceso = mapaProcesos.obtener(id);
    proceso.setEstado(EstadoProceso::ELIMINADO);

    listaProcesos.actualizar(proceso);
    mapaProcesos.eliminar(id);
    colaPendientes.eliminarPorId(id); // sincroniza cola
    pilaDeshacer.apilar(proceso);

    persistencia.actualizarProceso(proceso);

    cout << "Proceso eliminado correctamente.\n";
}

void GestorProcesos::mostrarProcesosPendientes() const {
    colaPendientes.mostrar();
}

void GestorProcesos::mostrarHistorial() const {
    listaProcesos.mostrarPorEstado(EstadoProceso::EJECUTADO);
}

void GestorProcesos::buscarProcesoPorId(int id) const {
    if (!mapaProcesos.existe(id)) {
        cout << "Proceso no encontrado.\n";
        return;
    }

    Proceso p = mapaProcesos.obtener(id);
    cout << "ID: " << p.getId()
         << " | Nombre: " << p.getNombre()
         << " | Prioridad: " << p.getPrioridad()
         << " | Estado: ";
    switch(p.getEstado()){
        case EstadoProceso::PENDIENTE: cout << "PENDIENTE"; break;
        case EstadoProceso::EJECUTADO: cout << "EJECUTADO"; break;
        case EstadoProceso::ELIMINADO: cout << "ELIMINADO"; break;
        case EstadoProceso::EN_EJECUCION: cout << "EN_EJECUCION"; break;
    }
    cout << endl;
}

void GestorProcesos::deshacerUltimaAccion() {
    if (pilaDeshacer.estaVacia()) {
        cout << "No hay acciones para deshacer.\n";
        return;
    }

    Proceso proceso = pilaDeshacer.desapilar();
    if (proceso.getEstado() == EstadoProceso::EJECUTADO) {
        proceso.setEstado(EstadoProceso::PENDIENTE);
        colaPendientes.encolar(proceso);
        listaProcesos.actualizar(proceso);
        mapaProcesos.insertar(proceso.getId(), proceso);
        persistencia.actualizarProceso(proceso);
        cout << "Ultima ejecucion revertida.\n";
    } else if (proceso.getEstado() == EstadoProceso::ELIMINADO) {
        proceso.setEstado(EstadoProceso::PENDIENTE);
        listaProcesos.actualizar(proceso);
        mapaProcesos.insertar(proceso.getId(), proceso);
        colaPendientes.encolar(proceso);
        persistencia.actualizarProceso(proceso);
        cout << "Ultima eliminacion revertida.\n";
    }
}
