//
// Created by Cz_13 on 2023/9/26.
//
#include "manage_system.h"

extern Node *cargos;

int main_menu(){
    char str[] = "1: 入库\n"
                 "2: 出库\n"
                 "3: 退出\n"
                 "4: 保存\n"
                 "5: 显示存货列表\n"
                 "6: 清空屏幕\n";
    printf("%s", str);
    int cmd = 0;
    if (scanf("%d", &cmd) != 1) {
        printf("pls input an integer\n");
        while (getchar() != '\n'); // 清空输入缓冲区
        return 1;
    }
    if(cmd == 1){
        Cargo cargo = {};
        printf("pls input id: ");
        scanf("%d", &cargo.id);
        printf("pls input count: ");
        scanf("%d", &cargo.count);
        printf("pls input name: ");
        scanf("%s", cargo.name);
        cargos = add_cargo(cargos, cargo);
    }else if(cmd == 5){
        printf("[id]-[count]-[name]\n");
        print(cargos);
    }else if(cmd == 4){
        saveData(cargos);
    }else if(cmd == 3){
        saveData(cargos);
        return 0;
    }else if(cmd == 2){
        Cargo cargo = {};
        printf("pls input id: ");
        scanf("%d", &cargo.id);
        printf("pls input count: ");
        scanf("%d", &cargo.count);
        printf("pls input name: ");
        scanf("%s", cargo.name);
        cargos = delete_cargo(cargos, cargo);
    }else if(cmd == 6){
        system("cls");
    }
    return 1;
}