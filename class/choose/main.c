#include <stdio.h>
#include <windows.h>

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void Choose(int a[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        int k = i;
        for (int j = i + 1; j < n; ++j) {
            if (a[j] < a[k]) {
                k = j;
            }
        }
        swap(a + i, a + k);
    }
}

int main()
{
    int mas[] = {3,4,1,5,8,2,99,0},num = sizeof (mas)/ sizeof(mas[0]);
    Choose(mas,num);
    for(int i = 0;i < sizeof (mas) / sizeof(mas[0]);i ++)
    {
        printf("%d ",mas[i]);
    }
    system("pause");
    printf("\n");
    return 0;
}
