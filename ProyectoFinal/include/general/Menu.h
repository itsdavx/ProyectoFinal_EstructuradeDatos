#ifndef MENU_H
#define MENU_H

#include "GestorProcesos.h"

class Menu {
private:

    GestorProcesos& gestor;

    //Opciones del menú
    void mostrarOpciones() const;
    void registrarProceso();
    void ejecutarProceso();
    void mostrarPendientes();
    void buscarProceso();
    void eliminarProceso();
    void mostrarHistorial();
    void mostrarFlujo();
    void deshacerAccion();

    //Metodo auxiliar
    void linea() const;

public:

    // Constructor
    Menu(GestorProcesos& gestor);

    // Método para iniciar el menu
    void iniciar();
};

#endif