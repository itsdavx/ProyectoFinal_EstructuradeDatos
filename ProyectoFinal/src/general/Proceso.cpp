#include "../../include/general/Proceso.h"

// Constructor
Proceso::Proceso(int id, const string &nombre, const string &descripcion) : id(id), nombre(nombre), descripcion(descripcion), estado(EstadoProceso::PENDIENTE) {}

// Getters
int Proceso::getId() const { return id; }
string Proceso::getNombre() const { return nombre; }
string Proceso::getDescripcion() const { return descripcion; }
EstadoProceso Proceso::getEstado() const { return estado; }

// Setters
void Proceso::setEstado(EstadoProceso nuevoEstado) { estado = nuevoEstado; }