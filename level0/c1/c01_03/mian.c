//判断闰年
//push失败？
#include <stdio.h>

void leap(int a){
    if(a%4==0&&a&100!=0)
        printf("您输入的是闰年");
    else
        printf("您输入的不是闰年");
}
int main(){
    system("chcp 65001");
    int a;
    printf("请输入一个整数：");
    scanf("%d",&a);
    leap(a);
}