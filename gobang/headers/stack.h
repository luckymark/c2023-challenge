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
    void (*append)(struct Stack *stack, int player, int x, int y);
    int* (*get_last_element)(struct Stack *stack);   // 返回栈中第一个元素
} Stack;

extern Stack *create_stack(int size);
#endif //C2023_CHALLENGE_STACK_H
