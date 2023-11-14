#include "Queue.h"

Queue * create_queue(int num){

    //申请队列空间，即数组空间
    SeqQueue  queue = (Queue *) malloc(sizeof(Queue) * num);

    //判断队列空间申请失败
    if(!queue){
        printf("malloc fail!");
        return NULL;
    }

    //初始化队列容量
    queue->capacity = num;

    //初始化队列元素个数
    queue->size = 0;

    //初始化队列值为空
    queue->data = (QueueDataType*)malloc(num * sizeof(QueueDataType));
    if (!queue->data) {
        printf("Memory allocation for data array failed.\n");
        free(queue);  // Clean up and free the queue struct
        return NULL;
    }
    for (int i = 1; i < num; ++i) {
        queue->data[i] = 0;
    }

    //返回队列指针
    return queue;
}

int is_empty(Queue* queue)
{
    if(0 == queue->size)
        return 1;
    else
        return 0;
}

void append(Queue* queue, int x)
{
    //判断队列不存在
    if(!queue){
        return;
    }

    //判断队列元素是否为满，拿队列当前的长度去跟数组的最大值作比较
    if(queue->size == queue->capacity){
        printf("队列元素已满！\n");
        return;
    }

    //插入元素(进队)
    queue->data[queue->size] = x;

    //元素入队，队列长度增加
    queue->size ++;
}

void print_queue(Queue* queue)
{
    for (int i = 0; i < queue->size; ++i) {
        printf("%d ",queue->data[i]);
    }
    printf("\n");
}