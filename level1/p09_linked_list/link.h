//
// Created by Cz_13 on 2023/9/25.
//

#ifndef C2023_CHALLENGE_LINK_H
#define C2023_CHALLENGE_LINK_H
#include "string.h"
#include "stdlib.h"
#include "stdio.h"

struct Node{
    int value;
    struct Node *next;
};

typedef struct Node Node;

void menu();
Node *insert(Node *hd, Node *nd);
void print(Node *nd);
int search(Node *nd, int target);
Node *r_sort(Node *nd);
#endif //C2023_CHALLENGE_LINK_H
