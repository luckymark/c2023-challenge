//判断一个数是否是13的倍数
#include <stdio.h>

void mul(int a){
    if(a==0)
        printf("您输入的不是13的倍数\n");
    else if(a%13==0)
        printf("您输入的是13的倍数\n");
    else
        printf("您输入的不是13的倍数\n");
}
int main(){
    system("chcp 65001");
    int a;
    printf("请输入一个整数：");
    scanf("%d",&a);
    mul(a);
    return 0;
}