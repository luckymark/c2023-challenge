#include "../headers/stack.h"

int is_full(Stack *stack){
    return stack -> size == stack -> sp;
}

int is_empty(Stack *stack){
    return stack -> sp == 0;
}
int *get_last_element(Stack *stack){
    if(stack->is_empty(stack)){
        printf("[ERROR] empty stack");
        return NULL;
    }
    int* ret = stack -> stack[(stack -> sp) - 1];
    return ret;
}


int* pop(Stack *stack){
    int* ret = stack -> stack[--(stack -> sp)];
    return ret;
}

void append(Stack *stack, int player, int x, int y){
    stack -> stack[stack -> sp][0] = player;   // 执行该步的角色
    stack -> stack[stack -> sp][1] = x;   // 落点x坐标
    stack -> stack[stack -> sp][2] = y;   // 落点y坐标
    stack -> sp++;
}

Stack *create_stack(int size){
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack -> sp = 0;
    stack -> size = size;
    stack -> stack = (int **) malloc(sizeof(int *) * size);
    for(int i = 0; i < size; i ++){
        stack -> stack[i] = (int *) malloc(sizeof(int) * 3);
    }
    stack -> is_empty = is_empty;
    stack -> is_full = is_full;
    stack -> pop = pop;
    stack -> append = append;
    stack -> get_last_element = get_last_element;
    return stack;
}