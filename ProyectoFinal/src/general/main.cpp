#include "../include/general/Menu.h"
#include "../include/general/GestorProcesos.h"

int main() {
    GestorProcesos gestor;
    Menu menu(gestor);
    menu.iniciar();
    return 0;
}
