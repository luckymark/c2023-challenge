#include <stdio.h>
#include <stdlib.h>
//使用链表指向 1【】 2【】 3【】
//1 h->x  2 h-> 1.x  3 p insert  4 delete h
typedef struct Node
{
    int data;//定义数据域
    struct Node *next;//定义后继指针域
}Node;

int main()
{
    Node * h = (Node*) malloc(sizeof (Node *));

}