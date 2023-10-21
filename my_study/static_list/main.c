#include "SeqList.h"

void  TestSeqList1()
{
    SL sl;
    SeqListInit(&sl);
    SeqListPushBack(&sl,1);
    SeqListPushBack(&sl,2);
    SeqListPushBack(&sl,3);
    SeqListPushBack(&sl,4);
    SeqListPushBack(&sl,5);
}
int main()
{
    TestSeqList1();
    return 0;
}