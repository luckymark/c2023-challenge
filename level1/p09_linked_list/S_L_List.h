//
// Created by 14212 on 2023/10/11.
//

#ifndef C2023_CHALLENGE_S_L_LIST_H
#define C2023_CHALLENGE_S_L_LIST_H
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct node{
    int data;
    struct node * link;
}New_Node;
New_Node * init_list(void);
void Creat_List(New_Node * first);
void print_list(New_Node *);
New_Node * reverse_list(New_Node *);
int research_num(New_Node *,int x,int cnt);
#endif //C2023_CHALLENGE_S_L_LIST_H
