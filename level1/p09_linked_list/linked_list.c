#include "link.h"

Node *insert(Node *hd, Node *nd){
    nd -> next = hd;
    return nd;
}

void print(Node *nd){
    Node *p = nd;
    int i = 0;
    while(p != NULL){
        if(i++){
            printf(" -> ");
        }
        printf("%d", p -> value);
        p = p -> next;
    }
    printf("\n");
}

int search(Node *nd, int target){
    /*
     * 查询某元素的第一个地址
     * */
    Node *p = nd;
    int index = 1;
    while(p != NULL){
        if(p -> value == target){
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
