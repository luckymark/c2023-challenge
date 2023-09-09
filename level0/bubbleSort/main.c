#include <stdio.h>
#include <time.h>
int main(){
    setbuf(stdout,NULL);
    extern void BubbleSort(int n[],int count);
    int data[5]={98,23,4,2,5};
    BubbleSort(data,5);

    int data1[20]={98,23,4,2,5,34,23,2,2,3,8,34,45,5,57,56,5,234,456,45};
    BubbleSort(data1,20);

    int data2[50]={98,23,4,2,5,34,23,2,2,3,8,34,45,5,57,56,5,234,456,45,89,223,56,5,78,98,23,45,6,7,67,12,23,34,45,56,67,78,89,90,24,35,46,57,68,79,12,21,34,43};
    BubbleSort(data2,50);
    return 0;
}
void BubbleSort(int n[],int count){
    time_t start,done;
    start=clock();
    int c;
    for(int i=0;i<count;i++){
        for(int j=0;j<count;j++){
            if(n[j]>n[j+1]){
                c=n[j];
                n[j]=n[j+1];
                n[j+1]=c;
            }
        }
    }
    for(int i=0;i<count;i++)
        printf("%d ",n[i]);
    done=clock();
    printf("ÓÃÊ±:%f ms\r\n",(double)(done-start));
}