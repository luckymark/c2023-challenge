#include<stdio.h>
int main()
{
    int m,n;
    int i;
    int cnt=0;
    int sum=0;
    scanf("%d %d",&m,&n);
    if(m==1){
        m=2;}
    for(i=m;i<=n;i++){
        int isprime=1;
        int k;
        for(k=2;k<i-1;k++){
            if(i%k==0){
                isprime=0;
                break;
            }
        }
        if(isprime){
            cnt++;
            sum+=i;
        }
    }
    printf("%d %d\n",cnt,sum);
    return 0;
}