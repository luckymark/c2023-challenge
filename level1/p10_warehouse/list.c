#include "manage_system.h"

Node *insert(Node *hd, Node *nd){
    nd -> next = hd;
    return nd;
}

void print(Node *nd){
    Node *p = nd;
    int i = 0;
    while(p != NULL){
        Cargo cargo = p -> value;
        printf("[%d]-[%d]-[%s]\n", cargo.id, cargo.count, cargo.name);
        p = p -> next;
    }
    printf("\n");
}

int search(Node *nd, Cargo tar){
    /*
     * 查询某元素的第一个地址
     * */
    Node *p = nd;
    int index = 1;
    while(p != NULL){
        if(p -> value.id == tar.id){
            return index;
        }
        p = p -> next;
        index ++;
    }
    return -1;
}

Node *r_sort(Node *nd){
    if(nd == NULL || nd -> next == NULL){
        return nd;
    }
    Node *p = nd -> next;
    Node *lp = nd;
    nd -> next = NULL;
    Node *temp;
    while(p != NULL){
        temp = p -> next;
        p -> next = lp;
        lp = p;
        p = temp;
    }
    return lp;
}
/*
Node *delete(Node *hd, Cargo tar){
    Node *p = hd;
    int index = 1;
    while(p != NULL){
        if(p -> value.id == tar.id && (strcmp(p -> value.name, tar.name) == 0)){

        }
        p = p -> next;
        index ++;
    }
}
 */
