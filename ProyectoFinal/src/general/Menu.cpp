#include "../include/general/Menu.h"
#include <iostream>

using namespace std;

Menu::Menu(GestorProcesos& gestor) : gestor(gestor) {}

void Menu::mostrarOpciones() const {
    cout << "\n===== GESTION DE PROCESOS =====\n";
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
    int opcion;
    do {
        mostrarOpciones();
        cin >> opcion;

        switch(opcion) {
            case 1: registrarProceso(); break;
            case 2: ejecutarProceso(); break;
            case 3: mostrarPendientes(); break;
            case 4: buscarProceso(); break;
            case 5: eliminarProceso(); break;
            case 6: mostrarHistorial(); break;
            case 7: mostrarFlujo(); break;
            case 8: deshacerAccion(); break;
            case 0: cout << "Saliendo del sistema...\n"; break;
            default: cout << "Opcion invalida.\n";
        }
    } while(opcion != 0);
}

void Menu::registrarProceso() {
    string nombre, descripcion;
    cout << "Nombre del proceso: ";
    cin.ignore();
    getline(cin, nombre);
    cout << "Descripcion: ";
    getline(cin, descripcion);
    gestor.registrarProceso(nombre, descripcion);
}

void Menu::ejecutarProceso() { gestor.ejecutarProceso(); }
void Menu::mostrarPendientes() { gestor.mostrarProcesosPendientes(); }
void Menu::buscarProceso() { 
    int id; cout << "Ingrese ID: "; cin >> id; 
    gestor.buscarProcesoPorId(id); 
}
void Menu::eliminarProceso() { 
    int id; cout << "Ingrese ID: "; cin >> id; 
    gestor.eliminarProceso(id); 
}
void Menu::mostrarHistorial() { gestor.mostrarHistorial(); }
void Menu::mostrarFlujo() { gestor.mostrarFlujoEjecucion(); }
void Menu::deshacerAccion() { gestor.deshacerUltimaAccion(); }
