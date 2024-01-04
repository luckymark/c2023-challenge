
#include <stdio.h>
//判断数的正负、判断是否为偶数

void pom(int a){
    if(a==0)
        printf("您输入的为0\n");
    else if(a>0)
        printf("您输入的为正数\n");
    else printf("你你输入的为负数\n");
}

void odevity(int a){
    if(a/2==0)
        printf("您输入的是非奇非偶数\n");
    else if(a%2==0)
        printf("您输入的是偶数\n");
    else
        printf("您输入的是奇数\n");

}
int main(){
    system("chcp 65001");
    int a;
    printf("请输入一个整数：");
    scanf("%d",&a);
    pom(a);
    odevity(a);
    return 0;
}

