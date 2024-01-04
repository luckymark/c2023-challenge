//
// Created by 81201 on 2023/9/14.
//输入5个0-9的数，输入的数从小到大排序
// （排序方法不限，但鼓励尝试下“桶排序”，不知道什么是“桶排序”的话，可以google之）
#include <stdio.h>
int main(){
    system("chcp 65001");
    printf("请输入5个0-9的数：");
    int a[4],j=0,i,m[4]={0},n[4]={0};
    for ( i = 0; i < 5; i++) {
        scanf("%d",&a[i]);
    }

    for (j = 0; j < 5; j++) {
        if(a[j]>=0&&a[j]<5)
            m[a[j]-1]=1;
        else if(a[j]>=5&&a[j]<=9)
            n[a[j]-1]=1;
        else
            printf("输入错误!");
    }

    for (i = 0; i < 5; i++) {
        if(m[i]==1)
            printf("%d ",i+1);
    }
    for (i = 0; i < 5; i++) {
        if(n[i]==1)
            printf("%d ",i+1);
    }
    return 0;
}
