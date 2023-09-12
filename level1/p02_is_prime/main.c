#include <stdio.h>
#include <math.h>
int main()
{

    int n,end;
    scanf("%d",&n);
    end=sqrt(n)+1;
    if(n==1) printf("No");
    else if(n==2) printf("Yes");
    else
    {
        for(int i=2;i<=end;++i)
        {
            if(n%i==0) {
                printf("No");
                break;
            }
        }
        printf("Yes");
    }
    return 0;
}