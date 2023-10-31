#include "stack.h"

int is_full(Stack *stack){
    return stack -> size == stack -> sp;
}

int is_empty(Stack *stack){
    return stack -> sp == 0;
}

int* pop(Stack *stack){
    int* ret = stack -> stack[--(stack -> sp)];
    return ret;
}

void append(Stack *stack, const int* data){
    stack -> stack[stack -> sp][0] = data[0];
    stack -> stack[stack -> sp][1] = data[1];
    stack -> sp++;
}

Stack *create_stack(int size){
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack -> sp = 0;
    stack -> size = size;
    stack -> stack = (int **) malloc(sizeof(int *) * size);
    for(int i = 0; i < size; i ++){
        stack -> stack[i] = (int *) malloc(sizeof(int) * 2);
    }
    stack -> is_empty = is_empty;
    stack -> is_full = is_full;
    stack -> pop = pop;
    stack -> append = append;
    return stack;
}