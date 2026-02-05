#include "../include/general/Proceso.h"

// Constructor
Proceso::Proceso(int id, const string& nombre, const string& descripcion, int prioridad)
    : id(id), nombre(nombre), descripcion(descripcion), prioridad(prioridad),
      estado(EstadoProceso::PENDIENTE) {
}

// Getters
int Proceso::getId() const {
    return id;
}

string Proceso::getNombre() const {
    return nombre;
}

string Proceso::getDescripcion() const {
    return descripcion;
}

int Proceso::getPrioridad() const {
    return prioridad;
}

EstadoProceso Proceso::getEstado() const {
    return estado;
}

// Setter
void Proceso::setEstado(EstadoProceso nuevoEstado) {
    estado = nuevoEstado;
}
