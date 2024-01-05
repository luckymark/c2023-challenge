#include <stdio.h>

//定义move函数，将一个盘子从x座移到y座上
void move(char x, char y)
{
    printf("%c-->%c\n",x,y);   //输出移盘方案。x,y代表A，B，C座之一，根据每次的不同情况分别取A，B，C代入
}

void hanoi(int n, char one, char two, char three) //将n个盘从one座借助two座，移到three座
{
    if(n==1)
        move(one, three);
    else
    {
        hanoi(n-1, one, three, two); //将 A 座上 n-1 个盘子移到 B 座上（借助 C）
        move(one, three);//将 A 座上剩下的 1 个盘子移到 C 座上
        hanoi(n-1, two, one, three);//将 B 座上 n-1 个盘子移到 C 座上（借助 A）
    }
}

main()
{
    int m;
    printf("input the number of disks:");
    scanf("%d",&m);   //盘子的数量
    printf("The step to moving %d disks:\n",m);
    hanoi(m,'A','B','C');
}