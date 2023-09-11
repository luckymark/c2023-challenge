#include <stdio.h>
void move(int cap,int tar,int buffer,int num)
{
    if(num==1)
    {
        printf("%c->%c\n",cap-1+'A',tar-1+'A');
        return;
    }
    move(cap,buffer,tar,num-1);
    printf("%c->%c\n",cap-1+'A',tar-1+'A');
    move(buffer,tar,cap,num-1);
    return;
}
int main()
{
    move(1,2,3,64);
    return 0;
}