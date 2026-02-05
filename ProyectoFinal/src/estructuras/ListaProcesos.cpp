#include "../../include/estructuras/ListaProcesos.h"
#include <iomanip>

ListaProcesos::ListaProcesos() : cabeza(nullptr) {}
ListaProcesos::~ListaProcesos()
{
    while (cabeza != nullptr)
    {
        Nodo *temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

void ListaProcesos::agregar(const Proceso &proceso)
{
    Nodo *nuevo = new Nodo(proceso);
    if (!cabeza)
    {
        cabeza = nuevo;
        return;
    }
    Nodo *actual = cabeza;
    while (actual->siguiente != nullptr)
        actual = actual->siguiente;
    actual->siguiente = nuevo;
}

void ListaProcesos::actualizar(const Proceso &proceso)
{
    Nodo *actual = cabeza;
    while (actual)
    {
        if (actual->proceso.getId() == proceso.getId())
        {
            actual->proceso.setEstado(proceso.getEstado());
            return;
        }
        actual = actual->siguiente;
    }
}

void ListaProcesos::mostrar() const
{
    if (!cabeza)
    {
        cout << "No hay procesos registrados.\n";
        return;
    }

    Nodo *actual = cabeza;

    while (actual)
    {

        string estadoStr;
        switch (actual->proceso.getEstado())
        {
        case EstadoProceso::PENDIENTE:
            estadoStr = "PENDIENTE";
            break;
        case EstadoProceso::EN_EJECUCION:
            estadoStr = "EN_EJECUCION";
            break;
        case EstadoProceso::EJECUTADO:
            estadoStr = "EJECUTADO";
            break;
        case EstadoProceso::ELIMINADO:
            estadoStr = "ELIMINADO";
            break;
        }

        cout << left
             << setw(5) << "ID:"
             << setw(4) << actual->proceso.getId() << " | "
             << setw(10) << "Nombre:"
             << setw(35) << actual->proceso.getNombre() << " | "
             << setw(14) << "Descripcion:"
             << setw(45) << actual->proceso.getDescripcion() << " | "
             << setw(8) << "Estado:"
             << setw(12) << estadoStr
             << endl;

        actual = actual->siguiente;
    }
}

void ListaProcesos::mostrarPorEstado(EstadoProceso estado) const
{
    Nodo *actual = cabeza;
    bool encontrado = false;

    while (actual)
    {
        if (actual->proceso.getEstado() == estado)
        {

            cout << left
                 << setw(5) << "ID:"
                 << setw(4) << actual->proceso.getId() << " | "
                 << setw(10) << "Nombre:"
                 << setw(35) << actual->proceso.getNombre() << " | "
                 << setw(14) << "Descripcion:"
                 << setw(45) << actual->proceso.getDescripcion()
                 << endl;

            encontrado = true;
        }
        actual = actual->siguiente;
    }

    if (!encontrado)
    {
        cout << "No hay procesos con ese estado.\n";
    }
}
