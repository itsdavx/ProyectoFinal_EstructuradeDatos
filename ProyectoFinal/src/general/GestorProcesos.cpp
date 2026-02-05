#include "../include/general/GestorProcesos.h"
#include <iostream>

using namespace std;

// Constructor de la clase GestorProcesos
GestorProcesos::GestorProcesos() : siguienteId(1)
{
    persistencia.cargarProcesos(listaProcesos, colaPendientes, mapaProcesos, siguienteId);
}

// Funciones principales del gestor de procesos
void GestorProcesos::registrarProceso(const string &nombre, const string &descripcion)
{
    Proceso nuevo(siguienteId++, nombre, descripcion);

    colaPendientes.encolar(nuevo);
    listaProcesos.agregar(nuevo);
    mapaProcesos.insertar(nuevo.getId(), nuevo);

    persistencia.guardarProceso(nuevo);
    persistencia.registrarEnHistorial("REGISTRAR", nuevo);
}

void GestorProcesos::ejecutarProceso()
{
    if (colaPendientes.estaVacia())
    {
        cout << "No hay procesos pendientes.\n";
        return;
    }

    // Saca el primer proceso pendiente válido
    Proceso proceso = colaPendientes.desencolarValido();

    // Estado: EN_EJECUCION
    proceso.setEstado(EstadoProceso::EN_EJECUCION);
    listaProcesos.actualizar(proceso);
    mapaProcesos.actualizar(proceso.getId(), proceso);

    persistencia.actualizarProceso(proceso);
    persistencia.registrarEnHistorial("EN_EJECUCION", proceso);

    // Estado: EJECUTADO
    proceso.setEstado(EstadoProceso::EJECUTADO);
    listaProcesos.actualizar(proceso);
    mapaProcesos.actualizar(proceso.getId(), proceso);

    pilaDeshacer.apilar(proceso);

    persistencia.actualizarProceso(proceso);
    persistencia.registrarEnHistorial("EJECUTAR", proceso);
    cout << "\n----------------- EJECUCION DE PROCESO -----------------" << endl;
    cout << "Ejecutando proceso..." << endl;
    cout << "Proceso ejecutado: " << proceso.getNombre() << endl;
    cout << "Ejecucion completada." << endl;
    cout << "--------------------------------------------------------" << endl;
}

void GestorProcesos::eliminarProceso(int id)
{
    if (!mapaProcesos.existe(id))
    {
        cout << "Proceso no encontrado.\n";
        return;
    }

    Proceso proceso = mapaProcesos.obtener(id);
    proceso.setEstado(EstadoProceso::ELIMINADO);

    listaProcesos.actualizar(proceso);
    mapaProcesos.actualizar(id, proceso);                          // ya no eliminar del mapa
    colaPendientes.actualizarEstado(id, EstadoProceso::ELIMINADO); // sincroniza cola
    pilaDeshacer.apilar(proceso);

    persistencia.actualizarProceso(proceso);
    persistencia.registrarEnHistorial("ELIMINAR", proceso);
    cout << "\n------------------ ELIMINACION DE PROCESO ------------------" << endl;
    cout << "Eliminando proceso..." << endl;
    cout << "Proceso eliminado: " << proceso.getNombre() << endl;
    cout << "Eliminacion completada." << endl;
    cout << "------------------------------------------------------------" << endl;
}

void GestorProcesos::mostrarProcesosPendientes() const
{
    colaPendientes.mostrar();

}

void GestorProcesos::mostrarHistorial() const
{
    listaProcesos.mostrarPorEstado(EstadoProceso::EJECUTADO);
}

void GestorProcesos::mostrarFlujoEjecucion() const
{
    persistencia.mostrarHistorial();
}

void GestorProcesos::buscarProcesoPorId(int id) const
{
    if (!mapaProcesos.existe(id))
    {
        cout << "Proceso no encontrado.\n";
        return;
    }

    cout << "\n----------------------------------------------------------------" << endl;
    Proceso p = mapaProcesos.obtener(id);
    cout << "ID: " << p.getId()
         << " | Nombre: " << p.getNombre()
         << " | Descripcion: " << p.getDescripcion()
         << " | Estado: " << static_cast<int>(p.getEstado())
         << endl;
    cout << "----------------------------------------------------------------" << endl;
}

void GestorProcesos::deshacerUltimaAccion()
{
    if (pilaDeshacer.estaVacia())
    {
        cout << "No hay acciones para deshacer.\n";
        return;
    }

    Proceso proceso = pilaDeshacer.desapilar();
    proceso.setEstado(EstadoProceso::PENDIENTE);

    colaPendientes.encolarAlFrente(proceso);
    listaProcesos.actualizar(proceso);
    mapaProcesos.actualizar(proceso.getId(), proceso);

    persistencia.actualizarProceso(proceso);
    persistencia.registrarEnHistorial("DESHACER", proceso);
    cout << "Deshaciendo ultima accion..." << endl;
    cout << "Ultima accion deshecha correctamente."<< endl;
}