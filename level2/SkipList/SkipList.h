#ifndef C2023_CHALLENGE_SKIPLIST_H
#define C2023_CHALLENGE_SKIPLIST_H
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define INIT_NUM 5
typedef struct node{
    int data;
    int layer;
    struct node * last;
    struct node * next;
    struct node * down;
}New_Node;
typedef struct N{
    New_Node * Node;
    struct N * next;
}Stack;
void creat_SkipList(New_Node ** head_point,New_Node ** tail_point,int * data);
void insert(New_Node ** head,New_Node ** tail,int d);
int random_layer(void);
void push_stack(Stack ** n,New_Node * location);
New_Node * pop_stack(Stack ** n);
New_Node * research(New_Node * head,int num);
void delete(New_Node ** head,New_Node ** tail,int d);//删除第d个数
void print_list(New_Node *head);
#endif //C2023_CHALLENGE_SKIPLIST_H
