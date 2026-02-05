#ifndef PROCESO_H
#define PROCESO_H

#include <string>

using namespace std;

// Estados posibles de un proceso
enum class EstadoProceso {
    PENDIENTE,
    EN_EJECUCION,
    EJECUTADO,
    ELIMINADO
};

class Proceso {
private:
    int id;
    string nombre;
    string descripcion;
    int prioridad;
    EstadoProceso estado;

public:
    // Constructor
    Proceso(int id, const string& nombre, const string& descripcion, int prioridad);

    // Getters
    int getId() const;
    string getNombre() const;
    string getDescripcion() const;
    int getPrioridad() const;
    EstadoProceso getEstado() const;

    // Setters
    void setEstado(EstadoProceso nuevoEstado);
};

#endif