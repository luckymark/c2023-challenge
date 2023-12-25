#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "stackAndSeqList.h"


void SeqListPrint(SL* ps)
{
	for (int i = 0; i < ps->size; ++i)
	{
		printf("%d ", ps->a[i]);
	}
	printf("\n");
}

// 清空栈操作
void StackChessClear(ST* pStack)
{
	pStack->size = 0;
}

void StackChessInit(ST *ps){
	assert(ps);
	ps->a = (Chess*)malloc(sizeof(Chess)*4);
	if (ps->a == NULL)
	{
		printf("malloc failed!");
		exit(-1);
	}
	ps->size = 0;//-1
	ps->capacity = 0;
}

void StackChessPush(ST *ps, Chess x){
	assert(ps);

	if (ps->size == ps->capacity)
	{
		int newCapacity = ps->capacity * 2 + 1;
		Chess* tmp = (Chess*)realloc(ps->a, sizeof(Chess)*newCapacity);
		if (tmp == NULL)
		{
			printf("realloc failed!");
			exit(-1);
		}
		ps->a = tmp;
		ps->capacity = newCapacity;
	}
	ps->a[ps->size] = x;
	ps->size++;
}

Chess StackChessPop(ST *ps)
{
	assert(ps);
	assert(ps->size > 0);
	ps->size--;
	return ps->a[ps->size];
}

Chess StackChessTop(ST *ps)
{
	assert(ps);
	assert(ps->size > 0);
	return ps->a[ps->size - 1];
}

bool StackChessEmpty(ST *ps){
	assert(ps);
	return ps->size == 0;
}

void StackChessDestroy(ST *ps){
	assert(ps);
	free(ps->a);
	ps->a = NULL;
	ps->size = 0;
	ps->capacity = 0;
}

void StackChessPrint(ST *ps){
	assert(ps);
	while (!StackChessEmpty(ps))
	{
		//输出Chess的x,col,color
		Chess tmp = StackChessTop(ps);
		printf("(%d,%d,%d) ", tmp.x, tmp.y, tmp.color);
		StackChessPop(ps);
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
	if (ps->size == ps->capacity)
	{
		int newcapacity = ps->capacity == 0 ? 12 : ps->capacity * 2;
		SLDataType* tmp = (SLDataType*)realloc(ps->a, newcapacity * sizeof(SLDataType));
		if (tmp == NULL)
		{
			printf("realloc fail\n");
			exit(-1);
		}
		ps->a = tmp;
		ps->capacity = newcapacity;
	}
}

void SeqListPushBack(SL* ps, SLDataType x)
{
	SeqListCheckCapacity(ps);
	ps->a[ps->size] = x;
	ps->size++;
}

void SeqListPopBack(SL* ps)
{
	//暴力处理
	assert(ps->size > 0);
	ps->a[ps->size] = 0;
	ps->size--;
}

void SeqListPushFront(SL* ps, SLDataType x)
{
	SeqListCheckCapacity(ps);
	//挪动数据
	int end = ps->size - 1;
	while (end >= 0)
	{
		ps->a[end + 1] = ps->a[end];
		--end;
	}
	ps->a[0] = x;
	ps->size++;
}

void SeqListPopFront(SL* ps)
{
	//暴力
	assert(ps->size > 0);
	int start = 0;
	while (start < ps->size - 1)
	{
		ps->a[start] = ps->a[start + 1];
		++start;
	}

	ps->a[ps->size - 1] = 0;
	ps->size--;
}

void SeqListClear(SL* ps)
{
	ps->size = 0;
}