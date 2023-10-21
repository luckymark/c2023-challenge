#include <stdio.h>
#include <windows.h>
void Exchange(int *a,int *b);
void Pop(int a[],int num);

int main()
{
    int mas[] = {3,4,1,5,8,2,99,0},num = sizeof (mas)/ sizeof(mas[0]);
    Pop(mas,num);
    for(int i = 0;i < sizeof (mas) / sizeof(mas[0]);i ++)
    {
        printf("%d ",mas[i]);
    }
    system("pause");
    printf("\n");
    return 0;
}

void Exchange(int *a,int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void Pop(int a[],int num)
{
    int flag = 0,count = 0;
    while (flag < num - 1){
        flag = 0;
        for(int i = 0;i < num - 1 - flag;++i)
        {
            if(a[i] > a[i + 1])
            {
                Exchange(a + i,a + i + 1);
                count = 0;
            }
            else
            {
                ++count;
            }
        }
        flag += count;
    }
}