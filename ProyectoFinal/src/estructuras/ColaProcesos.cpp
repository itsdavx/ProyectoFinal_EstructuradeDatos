#include "../../include/estructuras/ColaProcesos.h"
#include <iomanip>

// Constructor o inicializador
ColaProcesos::ColaProcesos() : frente(nullptr), final(nullptr) {}

// Destructor
ColaProcesos::~ColaProcesos()
{
    while (frente != nullptr)
    {
        Nodo *temp = frente;
        frente = frente->siguiente;
        delete temp;
    }
}

// Implementacion de funciones
bool ColaProcesos::estaVacia() const
{
    return frente == nullptr;
}

void ColaProcesos::encolar(const Proceso &proceso)
{
    Nodo *nuevo = new Nodo{proceso, nullptr};
    if (estaVacia())
    {
        frente = final = nuevo;
    }
    else
    {
        final->siguiente = nuevo;
        final = nuevo;
    }
}

// Pone el proceso al frente de la cola (para revertidos)
void ColaProcesos::encolarAlFrente(const Proceso &proceso)
{
    Nodo *nuevo = new Nodo{proceso, frente};
    frente = nuevo;
    if (final == nullptr)
        final = nuevo;
}

Proceso ColaProcesos::desencolarValido()
{
    if (estaVacia())
        throw runtime_error("No hay procesos pendientes");

    Nodo *actual = frente;
    Nodo *anterior = nullptr;

    while (actual != nullptr)
    {
        if (actual->proceso.getEstado() == EstadoProceso::PENDIENTE)
        {
            if (anterior == nullptr)
                frente = actual->siguiente;
            else
                anterior->siguiente = actual->siguiente;

            if (actual == final)
                final = anterior;

            Proceso p = actual->proceso;
            delete actual;
            return p;
        }
        anterior = actual;
        actual = actual->siguiente;
    }

    throw runtime_error("No hay procesos pendientes");
}

void ColaProcesos::mostrar() const
{
    if (estaVacia())
    {
        cout << "No hay procesos pendientes.\n";
        return;
    }

    Nodo *actual = frente;
    while (actual != nullptr)
    {
        if (actual->proceso.getEstado() != EstadoProceso::ELIMINADO)
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
                 << setw(35) << actual->proceso.getNombre() << " | " // ↑ antes 25
                 << setw(14) << "Descripcion:"
                 << setw(45) << actual->proceso.getDescripcion() << " | " // ↑ antes 30
                 << setw(8) << "Estado:"
                 << setw(12) << estadoStr
                 << endl;
        }
        actual = actual->siguiente;
    }
}
void ColaProcesos::actualizarEstado(int id, EstadoProceso nuevoEstado)
{
    Nodo *actual = frente;
    while (actual != nullptr)
    {
        if (actual->proceso.getId() == id)
        {
            actual->proceso.setEstado(nuevoEstado);
            return;
        }
        actual = actual->siguiente;
    }
}
