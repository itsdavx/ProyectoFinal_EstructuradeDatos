#ifndef PROCESO_H
#define PROCESO_H

#include <string>

using namespace std;

enum class EstadoProceso {
    PENDIENTE,   //0
    EN_EJECUCION,//1
    EJECUTADO,   //2
    ELIMINADO    //3
};

class Proceso {
private:
    int id;
    string nombre;
    string descripcion;
    EstadoProceso estado;

public:
    Proceso(int id, const string& nombre, const string& descripcion);

    int getId() const;
    string getNombre() const;
    string getDescripcion() const;
    EstadoProceso getEstado() const;

    void setEstado(EstadoProceso nuevoEstado);
};

#endif
