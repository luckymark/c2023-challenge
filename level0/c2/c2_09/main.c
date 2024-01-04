
//输入5个0-9的数，输出0-9中没有出现过的数
// Created by 81201 on 2023/9/14.
#include <stdio.h>
int main(){
    system("chcp 65001");
    printf("请输入5个0-9的数：");
    int a[4],j=0,i;
    for ( i = 0; i < 5; i++) {
        scanf("%d",&a[i]);
    }

    for (j = 0; j < 10; j++) {
        if(a[0]!=j&&a[1]!=j&&a[2]!=j&&a[3]!=j&&a[4]!=j)
            printf("%d ",j);
    }


    return 0;
}
