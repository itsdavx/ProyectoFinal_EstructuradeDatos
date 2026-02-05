#include "../include/general/Menu.h"
#include <iostream>
#include <limits>

using namespace std;

Menu::Menu(GestorProcesos &gestor) : gestor(gestor) {}

void Menu::mostrarOpciones() const
{
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

void Menu::iniciar()
{
    int opcion = -1;

    do
    {
        mostrarOpciones();

        //Validacion de entrada
        if (!(cin >> opcion))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\nEntrada invalida. Ingrese un numero valido.\n";
            cout << "-----------------------------------------------------------------" << endl;

            opcion = -1;
            continue;
        }
        switch (opcion)
        {
        case 1:
        cout << "-----------------------------------------------------------------" << endl;
            registrarProceso();
            break;
        case 2:
        cout << "-----------------------------------------------------------------" << endl;
            ejecutarProceso();
            break;
        case 3:
        cout << "-----------------------------------------------------------------" << endl;
            mostrarPendientes();
            break;
        case 4:
        cout << "-----------------------------------------------------------------" << endl;
            buscarProceso();
            break;
        case 5:
        cout << "-----------------------------------------------------------------" << endl;
            eliminarProceso();
            break;
        case 6:
        cout << "-----------------------------------------------------------------" << endl;
            mostrarHistorial();
            break;
        case 7:
        cout << "-----------------------------------------------------------------" << endl;
            mostrarFlujo();
            break;
        case 8:
        cout << "-----------------------------------------------------------------" << endl;
            deshacerAccion();
            break;
        case 0:
            cout << "Saliendo del sistema...\n";
            cout << "-----------------------------------------------------------------" << endl;
            break;
        default:
            cout << "\nEntrada invalida. Ingrese un numero valido.\n";
            cout << "-----------------------------------------------------------------" << endl;
        }

    } while (opcion != 0);
}



void Menu::registrarProceso()
{
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
    cout << "-----------------------------------------------------------------" << endl;
}

// Funciones implementadas por el gestor de procesos

void Menu::ejecutarProceso()
{
    gestor.ejecutarProceso();
}

void Menu::mostrarPendientes()
{
    cout << "\n------------------------------------------------------------ PROCESOS PENDIENTES -------------------------------------------------------------" << endl;
    gestor.mostrarProcesosPendientes();
    cout << "----------------------------------------------------------------------------------------------------------------------------------------------" << endl;
}

void Menu::buscarProceso()
{
    cout << "\n----------------------------------- BUSQUEDA DE PROCESO POR ID -----------------------------------" << endl;
    int id;
    cout << "Ingrese ID: ";
    cin >> id;

    gestor.buscarProcesoPorId(id);
}

void Menu::eliminarProceso()
{
    cout << "\n----------------- ELIMINACION DE PROCESO POR ID -----------------" << endl;
    int id;
    cout << "Ingrese ID: ";
    cin >> id;
    cout << endl;
    gestor.eliminarProceso(id);  
    cout << "-----------------------------------------------------------------" << endl;
}

void Menu::mostrarHistorial()
{
    cout << "\n------------------------------------------------ HISTORIAL DE EJECUCION ------------------------------------------------" << endl;
    gestor.mostrarHistorial();
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
}

void Menu::mostrarFlujo()
{
    cout << "\n------------------------------------------------------------- FLUJO DE EJECUCION PASO A PASO --------------------------------------------------------------------" << endl;
    gestor.mostrarFlujoEjecucion();
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
}

void Menu::deshacerAccion()
{
    cout << "\n-------------------- DESHACER ULTIMA ACCION ---------------------" << endl;
    gestor.deshacerUltimaAccion();
    cout << "-----------------------------------------------------------------" << endl;
}