//
// Created by twlm on 9/7/2023.
//
#include <stdio.h>
#include <stdarg.h>
///C0
int main(){
    printf("Hello world！I'm 陈筑江！");
    extern int MaxNum_v3(int,...);
    printf("Max = %d",MaxNum_v3(5,2,1,9,8,88));
    return 0;
}

///C1 1.
int isPositiveNum(int n){
    return n>0;
}
///C1 2.
int isEvenNum(int n){
    return n%2==0;
}
///C1 3.
///Bing Says:能被4整除、但不能被100整除，或能被400整除的年份为闰年
int isLeapYear(int year){
    return (year%4==0&&year%100!=0)||year%400==0;
}
///C1 4.
int MaxNum(int n1,int n2){
    return n1>n2?n1:n2;
}
///C1 5.
int MaxNum_v2(int n1,int n2,int n3){
    int m=n1>n2?n1:n2;
    return MaxNum(m,n3);
}
///C1 6.
int MaxNum_v3(int NumCount,...){
    va_list args;
    va_start(args,NumCount);
    int max= va_arg(args,int);
    for(int i=1;i<NumCount;i++){
        max= MaxNum(max,va_arg(args,int));
    }
    return max;
}

