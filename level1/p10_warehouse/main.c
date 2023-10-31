#include "manage_system.h"

Node *cargos;

int main() {
    system("chcp 65001");
    setbuf(stdout, 0); //debug
    cargos = getData(cargos);
    while(main_menu());
    return 0;
}