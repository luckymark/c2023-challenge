#include "SeqList.h"

void SeqListPrint(SL* ps)
{
	for (int i = 0; i < ps->size; ++i)
	{
		printf("%.0f ", ps->a[i]);
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
		int newcapacity = ps->capacity == 0 ? 4 : ps->capacity * 2;
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
//    //温柔处理
//    if(ps->size > 0)
//    {
//        ps->a[ps->size] = 0;
//        ps->size --;
//    }
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
	//温柔处理
//    if(ps->size > 0)
//    {
//        int start = 0;
//        while (start < ps->size - 1)
//        {
//            ps->a[start] = ps->a[start + 1];
//            ++start;
//        }
//
//        ps->a[ps->size - 1] = 0;
//        ps->size--;
//    }
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

void SeqListFind(SL* ps, SLDataType x)
{
	//返回下标
	int b[ps->size];
	int n = 1;
	for (int i = 0; i < ps->size; ++i)
	{
		if (x == ps->a[i])
		{
			printf("第%d个下标是:%d\n", n, i);
			++n;
		}
	}

//	int i = 0;
//	while (i < ps->size)
//	{
//		if(x == ps->a[i])
//		{
//			return &ps->a;
//		}
//		++i;
//	}
//	return 0;
}

void SeqListInsert(SL* ps, int pos, SLDataType x)
{
	SeqListCheckCapacity(ps);
	assert(pos >= 0 && pos <= ps->size);
	ps->size++;
	int begin = pos, end = ps->size - 1;
	while (end >= begin)
	{
		ps->a[end + 1] = ps->a[end];
		--end;
	}
	ps->a[pos] = x;
}

//删除pos位置数据
void SeqListErase(SL* ps, int pos)
{
	assert(pos >= 0 && pos <= ps->size - 1);
	int begin = pos, end = ps->size - 1;
	while (begin < end)
	{
		ps->a[begin] = ps->a[begin + 1];
		++begin;
	}
	ps->a[end] = 0;
	ps->size--;
}