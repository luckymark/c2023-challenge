#include <stdio.h>

int main() {
    int i,j,m,cnt=0;
    int a[]={1,4,32,16,3,8,19,22,135,7,234,56,36,75,67,64,85,23,67,3,4,65,37,563,43,90};
    int len=sizeof(a)/sizeof(a[0]);
    for(i=0;i<len-1;i++){
        for(j=i+1;j>0;j--){
            if(a[j]<a[j-1]){
                m=a[j];
                a[j]=a[j-1];
                a[j-1]=m;
                cnt+=3;
            }else{
                cnt++;
                continue;
            }
        }
    }
    for(i=0;i<len;i++)
        printf("%d ",a[i]);
    printf("次数=%d",cnt);
    return 0;
}