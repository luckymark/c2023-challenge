#include <stdio.h>
#include <time.h>
#include <stdlib.h>


const int N=100;


int ne[N+5]={},val[N+5]={},head=1,tail=N;

int random(int Min,int Max)
{
    int ans;
    ans=rand()%(Max-Min+1)+Min;
    return ans;
}
int main()
{
    int tem,pre=0;
    srand(time(0));
    for(int i=1;i<=N;++i) if(i!=N) ne[i]=i+1;
    for(int i=head;i;i=ne[i]) val[i]=random(1,10);
    for(int now=head;now;now=tem)
    {
        tem=ne[now];
        ne[now]=pre;
        pre=now;
    }
    tem=head;
    head=tail;
    tail=tem;

    tem=1;
    for(int i=head;i;i=ne[i])
    {
        if(val[i]==5)
        {
            printf("%d\n",i);
            tem=0;
        }
    }
    if(tem) printf("-1");
    return 0;
}