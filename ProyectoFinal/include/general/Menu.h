#ifndef MENU_H
#define MENU_H

#include "GestorProcesos.h"

class Menu {
private:
    GestorProcesos& gestor;

    void mostrarOpciones() const;
    void registrarProceso();
    void ejecutarProceso();
    void mostrarPendientes();
    void buscarProceso();
    void eliminarProceso();
    void mostrarHistorial();
    void mostrarFlujo();
    void deshacerAccion();

public:
    Menu(GestorProcesos& gestor);
    void iniciar();
};

#endif
