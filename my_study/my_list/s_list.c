
#include "s_list.h"

SLTNode* CreatListNode(SListType x)
{
	SLTNode* newnode = (SLTNode*)malloc(sizeof(SLTNode));
	if (newnode == NULL)
	{
		printf("melloc failed!");
		exit(-1);
	}
	newnode->data = x;
	newnode->next = NULL;

	return newnode;
}

void SListPrint(SLTNode* phead)
{
	SLTNode* cur = phead;
	while (cur != NULL)
	{
		printf("%d->", cur->data);
		cur = cur->next;
	}
	printf("NULL\n");
}

void SListPushBack(SLTNode** pphead, SListType x)
{
	assert(pphead);
	SLTNode* newnode = CreatListNode(x);

	if (*pphead == NULL)
	{
		*pphead = newnode;
	}
	else
	{
		//找到尾节点
		SLTNode* tail = *pphead;
		while (tail->next != NULL)
		{
			tail = tail->next;
		}

		tail->next = newnode;
	}
}

void SListPushFront(SLTNode** pphead, SListType x)
{
	assert(pphead);
	SLTNode* newnode = CreatListNode(x);

	newnode->next = *pphead;
	*pphead = newnode;
}

void SListPopBack(SLTNode** pphead)
{
	assert(pphead);

	if ((*pphead)->next == NULL)
	{
		free(*pphead);
		*pphead = NULL;
	}
	else
	{
//		SLTNode* tail = *pphead, * prev = NULL;
//		while (tail->next != NULL)
//		{
//			prev = tail;
//			tail = tail->next;
//		}
//		free(tail);
//		prev->next = NULL;

		SLTNode* tail = *pphead;
		while (tail->next->next != NULL)
		{
			tail = tail->next;
		}
		free(tail->next);
		tail->next = NULL;
	}
}

void SListPopFront(SLTNode** pphead)
{
	assert(pphead);
	SLTNode* head = (*pphead)->next;
	free(*pphead);
	*pphead = head;
}

SLTNode* SListFind(SLTNode* phead, SListType x)
{
	assert(phead);
	SLTNode* cur = phead;
	while (cur)
	{
		if (x == cur->data)
		{
			return cur;
		}
		else
		{
			cur = cur->next;
		}
	}
	return NULL;
}
//默认在pos位置之后插入一个节点
void SListInsertAfter(SLTNode* pos, SListType x)
{
	assert(pos);
	SLTNode* nownode = CreatListNode(x);
	nownode->next = pos->next;
	pos->next = nownode;
}
//默认在pos位置之前插入一个节点
void SListInsert(SLTNode** pphead, SLTNode* pos, SListType x)
{
	assert(pphead);
	assert(pos);
	SLTNode* nownode = CreatListNode(x);
	//找到pos的前一个位置
	SLTNode* posPrev = *pphead;
	if ((*pphead) == pos)
	{
		nownode->next = *pphead;
		*pphead = nownode;
	}
	else
	{
		while (posPrev->next != pos)
		{
			posPrev = posPrev->next;
		}
		posPrev->next = nownode;
		nownode->next = pos;
	}
}
//
void SListErase(SLTNode** pphead, SLTNode* pos)
{

	assert(pphead);
	assert(pos);
	if ((*pphead) == pos)
	{
		SLTNode* head = (*pphead)->next;
		free(*pphead);
		*pphead = head;
	}
	else
	{
		SLTNode* posPrev = *pphead;
		while (posPrev->next != pos)
		{
			posPrev = posPrev->next;
		}
		posPrev->next = pos->next;
		free(pos);
		pos = NULL;
	}
}

void SListEraseAfter(SLTNode* pos)
{
	assert(pos->next != NULL);
	SLTNode* next = pos->next;
	pos->next = next->next;
	free(next);
	next = NULL;
}

void SListDestroy(SLTNode** pphead)
{
	assert(pphead);
	while (*pphead)
	{
		SLTNode* next = (*pphead)->next;
		free(*pphead);
		*pphead = next;
	}
	*pphead = NULL;
}

SLTNode* RemoveElement(SLTNode* phead, SListType value)
{
	assert(phead);
	//方法1：复用
//	SLTNode * pos = SListFind(phead,value);
//	while (pos){
//		SListErase(&phead, pos);
//		pos = SListFind(phead,value);
//	}
	//方法二：双指针
	SLTNode* cur = phead;
	SLTNode* posPrev = NULL;
	while (cur)
	{
		if (cur->data == value)
		{
			if (cur == phead)
			{
				phead = phead->next;
				free(cur);
				cur = phead;
			}
			else
			{
				posPrev->next = cur->next;
				free(cur);
				cur = posPrev->next;
			}
		}
		else
		{
			posPrev = cur;
			cur = cur->next;
		}
	}
	return phead;
}

SLTNode* ReverseList(SLTNode** head)
{

	if (head == NULL)
		return NULL;
	SLTNode* n1, * n2, * n3;
	n1 = NULL;
	n2 = *head;
	n3 = (*head)->next;
	while (n2)
	{
		n2->next = n1;
		n1 = n2;
		n2 = n3;
		if (n3)
			n3 = n3->next;
	}
	*head = n1;
	return *head;
}

SLTNode* ReverseList_2(SLTNode* head)
{
	SLTNode* cur = head;
	SLTNode* newhead = NULL;

	while (cur)
	{
		SLTNode* next = cur->next;

		cur->next = newhead;
		newhead = cur;

		cur = next;
	}
	head = newhead;
	return head;
}

SLTNode* MiddleNode(SLTNode* head)
{
	SLTNode* cur = head, * quick = head;

	if (cur && cur->next)
	{
		while (quick)
		{
			cur = cur->next;
			quick = quick->next->next;
		}
	}

	return cur;
}

SLTNode* FindKthToTail(SLTNode* head, int k)
{
	SLTNode* fast = head, * slow = head;
	while (k--)
	{
		if(!fast)
		{
			return NULL;
		}
		fast = fast->next;
	}
	while (fast)
	{
		fast = fast->next;
		slow = slow->next;
	}
	return slow;
}

//合并两个链表
SLTNode * MergeTwoLists(SLTNode * l1,SLTNode* l2)
{
	if(!l1)
		return l2;
	if(!l2)
		return l1;
	SLTNode *head = NULL,*tail = NULL;
	if(l1->data <l2->data)
	{
		head = tail = l1;
		l1 = l1->next;
	}
	else
	{
		head = tail = l2;
		l2 = l2->next;
	}
	while (l1 && l2)
	{
		if(l1->data <l2->data)
		{
			tail->next = l1;
			l1 = l1->next;
		}
		else
		{
			tail->next = l2;
			l2 = l2->next;
		}
		tail = tail->next;
	}
	if(l1 == NULL)
	{
		tail->next = l2;
	}
	if(l2 == NULL)
	{
		tail->next = l1;
	}
	return head;
}