#include "SeqList.h"

void TestSeqList1()
{
	SL sl;
	SeqListInit(&sl);
	SeqListPushBack(&sl, 1);
	SeqListPushBack(&sl, 2);
	SeqListPushBack(&sl, 3);
	SeqListPushBack(&sl, 4);
	SeqListPushBack(&sl, 5);
	SeqListPrint(&sl);
	SeqListPopBack(&sl);
	SeqListPopBack(&sl);
	SeqListPopBack(&sl);

	SeqListPrint(&sl);
	SeqListDestroy(&sl);
}

void TestSeqList2()
{
	SL sl;
	SeqListInit(&sl);
	SeqListPushBack(&sl, 1);
	SeqListPushBack(&sl, 2);
	SeqListPushBack(&sl, 3);
	SeqListPushBack(&sl, 4);
	SeqListPrint(&sl);

	SeqListPushFront(&sl, 10);
	SeqListPushFront(&sl, 20);
	SeqListPushFront(&sl, 30);
	SeqListPushFront(&sl, 40);
	SeqListPushFront(&sl, 50);
	SeqListPrint(&sl);
	SeqListDestroy(&sl);

}

void TestSeqList3()
{
	SL sl;
	SeqListInit(&sl);
	SeqListPushBack(&sl, 1);
	SeqListPushBack(&sl, 2);
	SeqListPushBack(&sl, 3);
	SeqListPushBack(&sl, 4);
	SeqListPrint(&sl);
	SeqListPopFront(&sl);
	SeqListPopFront(&sl);
	SeqListPopFront(&sl);
	SeqListPopFront(&sl);
	SeqListPopFront(&sl);
	SeqListPrint(&sl);
	SeqListDestroy(&sl);
}

void TestSeqList4()
{
	SL sl;
	SeqListInit(&sl);
	SeqListPushBack(&sl, 1);
	SeqListPushBack(&sl, 2);
	SeqListPushBack(&sl, 3);
	SeqListPushBack(&sl, 4);
	for (int i = 0; i < 8; ++i)
	{
		SeqListPushBack(&sl, i);
	}
	SeqListPrint(&sl);
	SeqListFind(&sl, 2);
	//未完成设想
//    int pos = SeqListFind(&sl,2),i=1;
//	while (pos)
//	{
//		printf("第%d个下标是：%d\n",++i,pos);
//		pos = SeqListFind(&sl,2);
//	}
	SeqListInsert(&sl, 5, 0);
	SeqListPrint(&sl);
	SeqListErase(&sl, 5);
	SeqListPrint(&sl);
	SeqListDestroy(&sl);
}

void Menu()
{
	printf("******************************************\n");
	printf("请选择你的操作：>\n");
	printf("1.头插  2.头删\n3.尾插  4.尾删\n5.打印 -1.退出\n");
	printf("******************************************\n");
}

void MenuTest()
{
	SL sl;
	int x;
	SeqListInit(&sl);
	int input = 0;
	while (input != -1)
	{
		Menu();
		scanf_s("%d", &input);
		switch (input)
		{
		case 1:
			printf("请输出您要头插入的数据，以-1结束：\n");
			scanf_s("%d", &x);
			while (x != -1)
			{
				SeqListPushFront(&sl, x);
				scanf_s("%d", &x);
			}
			break;
		case 2:
			SeqListPopFront(&sl);
			break;
		case 3:
			printf("请输出您要尾插入的数据，以-1结束：\n");
			scanf_s("%d", &x);
			while (x != -1)
			{
				SeqListPushBack(&sl, x);
				scanf_s("%d", &x);
			}
			break;
		case 4:
			SeqListPopBack(&sl);
			break;
		case 5:
			SeqListPrint(&sl);
			break;
		case -1:
			break;
		default:
			printf("无此选项请重新输入！\ng输入-1则退出");
			break;
		}
	}
	SeqListDestroy(&sl);
}
int main()
{
	system("chcp 65001");
	TestSeqList4();
	//MenuTest();
	return 0;
}