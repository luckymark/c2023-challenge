//
// Created by Cz_13 on 2023/9/26.
//

#include "manage_system.h"

int saveData(Node *cargos){
    // 采用链表实现一系列货物
    if(cargos == NULL){
        printf("error: none cargo error\n");
        return -2;
    }
    FILE *fp = fopen("D:\\class\\d\\level1\\p10_warehouse\\data.txt", "w");
    if(fp == NULL){
        printf("error: file open error\n");
        return -1;
    }
    /*
     * 文件格式: [id]-[name]-[count]
     * */
    Node *cargo = cargos;
    while(cargo != NULL){
        Cargo cg = cargo -> value;
        fprintf(fp, "[%d]-[%d]-%s\n", cg.id, cg.count, cg.name);
        cargo = cargo -> next;
    }
    fclose(fp);
    return 0;
}



Node *getData(Node *cargos){
    FILE *fp = fopen("D:\\class\\d\\level1\\p10_warehouse\\data.txt", "r");
    if(fp == NULL){
        return NULL;
    }
    int ret;
    while(1){
        Node *node = (Node *)malloc(sizeof(Node));
        ret = fscanf(fp, "[%d]-[%d]-%63s\n", &(node -> value.id), &(node -> value.count), node -> value.name);
        if(ret != 3){
            free(node);
            break;
        }
        cargos = insert(cargos, node);
    };
    fclose(fp);
    return cargos;
}

Node *add_cargo(Node *cargos, Cargo tar){
    int ret = search(cargos, tar);
    if(ret != -1){
        // 查询到, 且位于第ret位
        Node *p = cargos;
        while(ret > 1 && p -> next != NULL){
            ret--;
            p = p -> next;
        }
        if(strcmp(p -> value.name, tar.name) != 0){
            printf("pls check your input. The cargo has a wrong name or id\n");
            printf("the original name: %s\n", p -> value.name);
            printf("the original id: %d\n", p -> value.id);
            printf("the inputted name: %s\n", tar.name);
            printf("the inputted id: %d\n", tar.id);
            return cargos;
        }
        p -> value.count += tar.count;
        return cargos;   // 已有
    }else{
        // 未查询到
        Node *node = (Node *)malloc(sizeof(Node));
        node -> value.count = tar.count;
        node -> value.id = tar.id;
        node -> next = NULL;
        strcpy(node -> value.name, tar.name);
        cargos = insert(cargos, node);
        return cargos;   // 新增
    }
}

Node *delete_cargo(Node *cargos, Cargo tar){
    int ret = search(cargos, tar);
    if(ret != -1){
        Node *p = cargos;
        while(ret-- >= 0 && p -> next != NULL){
            p = p -> next;
        }
        if(strcmp(p -> value.name, tar.name) != 0){
            printf("pls check your input. The cargo has a wrong name or id\n");
            printf("the original name: %s\n", p -> value.name);
            printf("the original id: %d\n", p -> value.id);
            printf("the inputted name: %s\n", tar.name);
            printf("the inputted id: %d\n", tar.id);
            return cargos;
        }
        if(p -> value.count > tar.count){
            p -> value.count -= tar.count;
        }else if(p -> value.count == tar.count){

        }
        return cargos;   // 已有
    }else{
        printf("not found");
        return cargos;
    }
}
