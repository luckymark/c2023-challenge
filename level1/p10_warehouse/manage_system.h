//
// Created by Cz_13 on 2023/9/26.
//

#ifndef C2023_CHALLENGE_MANAGE_SYSTEM_H
#define C2023_CHALLENGE_MANAGE_SYSTEM_H

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

typedef struct {
    char name[64];
    int id;
    int count;
} Cargo;

struct Node {
    Cargo value;
    struct Node *next;
};

typedef struct Node Node;

Node *insert(Node *hd, Node *nd);
Node *delete(Node *nd, Cargo tar);
void print(Node *nd);
int search(Node *nd, Cargo tar);
Node *r_sort(Node *nd);

int saveData(Node *cargos);
Node *getData(Node *cargos);
Node *add_cargo(Node *cargos, Cargo tar);
int main_menu();
Node *delete_cargo(Node *cargos, Cargo tar);
#endif //C2023_CHALLENGE_MANAGE_SYSTEM_H
