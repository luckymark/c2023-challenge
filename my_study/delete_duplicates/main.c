#include <stdio.h>

int main()
{
    int a[] = {0,0,1,1,1,2,2,3,3};
    int n = sizeof(a)/sizeof (a[0]);
    int begin = 0,end = 0,dst = 0;
    while (begin < n){
        if(a[begin] == a[end])++end;
        else
        {
            a[dst] = a[begin];
            ++dst;
            begin = end;
            ++end;
        }
        if(n == end)
        {
            a[dst] = a[begin];
            ++dst;
            break;
        }
    }
    for (int i = 0; i < dst; ++i) {
        printf("%d ",a[i]);
    }
}