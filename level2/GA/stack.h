//
// Created by Cz_13 on 2023/10/23.
//

#ifndef C2023_CHALLENGE_STACK_H
#define C2023_CHALLENGE_STACK_H

#include "stdlib.h"
#include "stdio.h"
#include <assert.h>



typedef struct Stack{
    int sp; // 下一个将要填入数据的位置
    int **stack;
    int size;
    int (*is_empty)(struct Stack *stack);
    int (*is_full)(struct Stack *stack);
    int* (*pop)(struct Stack *stack);
    void (*append)(struct Stack *stack, const int* data);
} Stack;

/*extern int is_empty(Stack *stack);
extern int is_full(Stack *stack);
extern int* pop(Stack *stack);
extern void append(Stack *stack, int* data);
extern Stack *create_stack(int size);*/
extern Stack *create_stack(int size);
#endif //C2023_CHALLENGE_STACK_H
