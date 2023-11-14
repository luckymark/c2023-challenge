#include "SeqList.h"

void SeqListPrint(SL* ps)
{
    for(int i = 0; i < ps->size; ++i)
    {
        printf("%.0f ",ps->a[i]);
    }
    printf("\n");
}

void SeqListInit(SL* ps)
{
    ps->a = NULL;
    ps->size = ps->capacity = 0;
}

void SeqListDestroy(SL* ps)
{
    free(ps->a);
    ps->a = NULL;
    ps->size = ps->capacity = 0;
}

void SeqListCheckCapacity(SL* ps)
{
//如果没有空间或者空间不足就扩容
    if(ps->size == ps ->capacity)
    {
        int newcapacity = ps->capacity == 0 ? 4 : ps->capacity * 2;
        SLDataType * tmp = (SLDataType*)realloc(ps->a,newcapacity*sizeof(SLDataType));
        if(tmp == NULL)
        {
            printf("realloc fail\n");
            exit(-1);
        }
        ps->a = tmp;
        ps->capacity = newcapacity;
    }
}

void SeqListPushBack(SL* ps,SLDataType x)
{
    SeqListCheckCapacity(ps);
    ps->a[ps->size] = x;
    ps->size ++;
}

void SeqListPopBack(SL* ps)
{
//    //温柔处理
//    if(ps->size > 0)
//    {
//        ps->a[ps->size] = 0;
//        ps->size --;
//    }
    //暴力处理
    assert(ps->size > 0);
    ps->a[ps->size] = 0;
    ps->size --;
}

void SeqListPushFront(SL* ps,SLDataType x)
{
    SeqListCheckCapacity(ps);
    //挪动数据
    int end = ps->size -1;
    while (end >= 0)
    {
        ps->a[end + 1] = ps->a[end];
        --end;
    }
    ps->a[0] = x;
    ps->size++;
}

void SeqListPopFront(SL* ps){
    //温柔处理
    if(ps->size > 0)
    {
        int start = 0;
        while (start < ps->size - 1)
        {
            ps->a[start] = ps->a[start + 1];
            ++start;
        }

        ps->a[ps->size - 1] = 0;
        ps->size--;
    }

}

int SeqListFind(SL* ps, SLDataType x)
{
    ;
}