#include <stdio.h>


int main()
{
    int a[] = {2,3,5,0,0,0,0,0},b[]={1,2,2,4,6,};
    int p = sizeof (a)/sizeof (a[0]),n = sizeof (b)/sizeof (b[0]),m = 3;
    int end1 = m - 1,end2 = n - 1,end = m + n - 1;
    while (end1 >= 0 && end2 >= 0)
    {
        a[end--] = a[end1] > b[end2] ? a[end1--] : b[end2--];
//        if(a[end1] > b[end2])
//        {
//            a[end] = a[end1];
//            --end;
//            --end1;
//        } else
//        {
//           a[end] = b[end2];
//           --end;
//           --end2;
//        }
    }
    while (end2 >= 0){
        a[end--] = b[end2--];
    }
    for (int i = 0; i < m + n; ++i) {
        printf("%d ",a[i]);
    }
}