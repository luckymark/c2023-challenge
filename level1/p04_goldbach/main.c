#include <stdio.h>

int main() {
    int i,x,cnt,num=0;
    int a[100];
    for(i=2;i<=100;i++){
        cnt=0;
        for(x=2;x<=i;x++){
            cnt++;
            if(i%x==0){
                break;
            }
        }
        if(cnt==i-1) {
            printf("%d\n", i);
            num++;
            a[num-1]=i;
        }
        else
            continue;
    }
    printf("num=%d\n",num);
    int t,k,j,m,n,CNT=0;
    for(t=6;t<=100;t++){
        // printf("%d->%d\n",t,CNT);
        for(i=0;i<num;i++){
            if(a[i]<t){
                k=t-a[i];
                for(j=0;j<num;j++){
                    m=k-a[j];
                    for(n=0;n<num;n++){
                        if(a[n]==m){
                            CNT++;
                            goto end;
                        }else{
                            continue;
                        }

                    }

                }
            }
            else{
                break;
            }
        }
        end:continue;
    }
    printf("CNT=%d\n",CNT);
    if(CNT==95){
        printf("right");
    }

    return 0;
}
