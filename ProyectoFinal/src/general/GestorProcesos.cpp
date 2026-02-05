#include "../include/general/GestorProcesos.h"
#include <iostream>

using namespace std;

GestorProcesos::GestorProcesos() : siguienteId(1) {
    persistencia.cargarProcesos(listaProcesos, colaPendientes, mapaProcesos, siguienteId);
}

void GestorProcesos::registrarProceso(const string& nombre, const string& descripcion) {
    Proceso nuevo(siguienteId++, nombre, descripcion);

    colaPendientes.encolar(nuevo);
    listaProcesos.agregar(nuevo);
    mapaProcesos.insertar(nuevo.getId(), nuevo);

    persistencia.guardarProceso(nuevo);
    persistencia.registrarEnHistorial("REGISTRAR", nuevo);

    cout << "Proceso registrado correctamente.\n";
}

void GestorProcesos::ejecutarProceso() {
    if (colaPendientes.estaVacia()) {
        cout << "No hay procesos pendientes.\n";
        return;
    }

    // Saca el primer proceso pendiente válido
    Proceso proceso = colaPendientes.desencolarValido();

    // 1️⃣ Estado: EN_EJECUCION
    proceso.setEstado(EstadoProceso::EN_EJECUCION);
    listaProcesos.actualizar(proceso);
    mapaProcesos.actualizar(proceso.getId(), proceso);

    persistencia.actualizarProceso(proceso);
    persistencia.registrarEnHistorial("EN_EJECUCION", proceso);

    // 2️⃣ Estado: EJECUTADO
    proceso.setEstado(EstadoProceso::EJECUTADO);
    listaProcesos.actualizar(proceso);
    mapaProcesos.actualizar(proceso.getId(), proceso);

    pilaDeshacer.apilar(proceso);

    persistencia.actualizarProceso(proceso);
    persistencia.registrarEnHistorial("EJECUTAR", proceso);

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
mapaProcesos.actualizar(id, proceso);  // ya no eliminar del mapa
colaPendientes.actualizarEstado(id, EstadoProceso::ELIMINADO); // sincroniza cola
pilaDeshacer.apilar(proceso);

persistencia.actualizarProceso(proceso);
persistencia.registrarEnHistorial("ELIMINAR", proceso);


    cout << "Proceso eliminado correctamente.\n";
}

void GestorProcesos::mostrarProcesosPendientes() const {
    colaPendientes.mostrar();
}

void GestorProcesos::mostrarHistorial() const {
    listaProcesos.mostrarPorEstado(EstadoProceso::EJECUTADO);
}

void GestorProcesos::mostrarFlujoEjecucion() const {
    cout << "\n===== FLUJO DE EJECUCION =====\n";
    persistencia.mostrarHistorial(); // Ahora persistencia.mostrarHistorial() es const
}


void GestorProcesos::buscarProcesoPorId(int id) const {
    if (!mapaProcesos.existe(id)) {
        cout << "Proceso no encontrado.\n";
        return;
    }

    Proceso p = mapaProcesos.obtener(id);
    cout << "ID: " << p.getId()
         << " | Nombre: " << p.getNombre()
         << " | Descripcion: " << p.getDescripcion()
         << " | Estado: " << static_cast<int>(p.getEstado())
         << endl;
}

void GestorProcesos::deshacerUltimaAccion() {
    if (pilaDeshacer.estaVacia()) {
        cout << "No hay acciones para deshacer.\n";
        return;
    }

    Proceso proceso = pilaDeshacer.desapilar();
    proceso.setEstado(EstadoProceso::PENDIENTE);

    colaPendientes.encolarAlFrente(proceso); // vuelve al frente
    listaProcesos.actualizar(proceso);
    mapaProcesos.actualizar(proceso.getId(), proceso);

    persistencia.actualizarProceso(proceso);
    persistencia.registrarEnHistorial("DESHACER", proceso);

    cout << "Ultima accion deshecha correctamente.\n";
}