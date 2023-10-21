#include <stdio.h>
#include <windows.h>

void insert(int a[],int n,int m)
{
    int temp = a[n];
    for(int i = n - 1;i > m;i --)
    {
        a[i + 1] = a[i];
    }
    a[m + 1] = temp;
}

void Insert_sort(int a[], int n) {

    for(int i = 1;i < n;++i)
    {
        int count = 0;
        while(count < i){
            if(a[i] < a[count]){
                insert(a,i,count - 1);
                break;
            }
            else if(a[i] >= a[count] && a[i] <= a[1 + count])
            {
                insert(a,i,count);
                break;
            }
            else
            {
                count ++;
            }
        }

    }
}

int main()
{
    int mas[] = {4,3,1,8,5,99,17,20,2,7},num = sizeof (mas)/ sizeof(mas[0]);
    Insert_sort(mas, num);
    for(int i = 0;i < sizeof (mas) / sizeof(mas[0]);i ++)
    {
        printf("%d ",mas[i]);
    }
    system("pause");
    printf("\n");
    return 0;
}
