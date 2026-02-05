#include "../include/general/Menu.h"

#include <iostream>
#include <limits>

using namespace std;

// Constructor del menu
Menu::Menu(GestorProcesos &gestor) : gestor(gestor) {}

// Implementacion de metodos del menu
void Menu::mostrarOpciones() const {
    cout << endl;
    cout << "\n------------------------ GESTOR DE PROCESOS ---------------------\n";
    cout << "1. Registrar proceso\n";
    cout << "2. Ejecutar siguiente proceso\n";
    cout << "3. Mostrar procesos pendientes\n";
    cout << "4. Buscar proceso por ID\n";
    cout << "5. Eliminar proceso\n";
    cout << "6. Mostrar historial de ejecucion\n";
    cout << "7. Mostrar flujo de ejecucion paso a paso\n";
    cout << "8. Deshacer ultima accion\n";
    cout << "0. Salir\n";
    cout << "Seleccione una opcion: ";
}

void Menu::iniciar() {
    int opcion = -1;

    do {
        mostrarOpciones();

        //Validacion de entrada
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\nEntrada invalida. Ingrese un numero valido.\n";
            linea();

            opcion = -1;
            continue;
        }

        switch (opcion) {
        case 1: linea(); registrarProceso(); break;
        case 2: linea(); ejecutarProceso(); break;
        case 3: linea(); mostrarPendientes(); break;
        case 4: linea(); buscarProceso(); break;
        case 5: linea(); eliminarProceso(); break;
        case 6: linea(); mostrarHistorial(); break;
        case 7: linea(); mostrarFlujo(); break;
        case 8: linea(); deshacerAccion(); break;
        case 0: cout << "\nSaliendo del sistema...\n"; linea(); break;
        default: cout << "\nEntrada invalida. Ingrese un numero valido.\n"; linea();
        }

    } while (opcion != 0);
}

void Menu::registrarProceso() {
    string nombre, descripcion;
    cout << "\n------------------- Registro de nuevo proceso -------------------" << endl;

    cout << "Nombre del proceso: ";
    cin.ignore();
    getline(cin, nombre);

    cout << "Descripcion: ";
    getline(cin, descripcion);

    gestor.registrarProceso(nombre, descripcion);

    cout << "Registrando proceso..." << endl;
    cout << "Proceso registrado exitosamente." << endl;

    linea();
}

// Implementar metodos por el gestor de procesos
void Menu::ejecutarProceso() {
    gestor.ejecutarProceso();
}

void Menu::mostrarPendientes() {
    cout << "\n------------------------------------------------------------ PROCESOS PENDIENTES -------------------------------------------------------------" << endl;
    gestor.mostrarProcesosPendientes();
    cout << "----------------------------------------------------------------------------------------------------------------------------------------------" << endl;
}

void Menu::buscarProceso() {
    cout << "\n----------------------------------- BUSQUEDA DE PROCESO POR ID -----------------------------------" << endl;
    int id;
    cout << "Ingrese ID: ";
    cin >> id;

    gestor.buscarProcesoPorId(id);
}

void Menu::eliminarProceso() {
    cout << "\n----------------- ELIMINACION DE PROCESO POR ID -----------------" << endl;
    int id;
    cout << "Ingrese ID: ";
    cin >> id;
    cout << endl;
    gestor.eliminarProceso(id);
    linea();
}

void Menu::mostrarHistorial() {
    cout << "\n------------------------------------------------ HISTORIAL DE EJECUCION ------------------------------------------------" << endl;
    gestor.mostrarHistorial();
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
}

void Menu::mostrarFlujo() {
    cout << "\n------------------------------------------------------------- FLUJO DE EJECUCION PASO A PASO --------------------------------------------------------------------" << endl;
    gestor.mostrarFlujoEjecucion();
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
}

void Menu::deshacerAccion() {
    cout << "\n-------------------- DESHACER ULTIMA ACCION ---------------------" << endl;
    gestor.deshacerUltimaAccion();
    linea();
}

// Metodo Auxiliar para aspecto visual
void Menu::linea() const {
    cout << "-----------------------------------------------------------------" << endl;
}