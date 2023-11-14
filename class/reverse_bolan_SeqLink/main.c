#include "SeqList.h"


int main()
{
    char c;
    SL sl;
    SeqListInit(&sl);
    for(scanf("%c",&c);c!='\n';scanf("%c",&c))
    {
        if(c >= '0' && c <= '9')
        {
            SeqListPushFront(&sl,c - '0');
        }
        else
        {
            int a,b,d;
            a = sl.a[0];
            b = sl.a[1];
            SeqListPopFront(&sl);
            SeqListPopFront(&sl);
            switch(c)
            {
                case'+':
                    d = a + b;
                    SeqListPushFront(&sl,d);
                    break;
                case'-':
                    d = b - a;
                    SeqListPushFront(&sl,d);
                    break;
                case'*':
                    d = a * b;
                    SeqListPushFront(&sl,d);
                    break;
                case'/':
                    d = b / a;
                    SeqListPushFront(&sl,d);
                    break;
            }
        }
    }
    int result = sl.a[0];
    printf("%d ",result);
    return 0;
}