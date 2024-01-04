#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int QueueDataType;

typedef struct Queue{

    QueueDataType *data;            //顺序存储 数组模拟的队列
    int size;                //队列的大小(队列中元素的个数)
    int capacity;
}Queue,*SeqQueue;

Queue * create_queue(int num);
int is_empty(Queue* queue);
void append(Queue* queue, int x);
void print_queue(Queue* queue);
