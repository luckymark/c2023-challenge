#include <stdio.h>
//作业p09
#include<stdlib.h>
int main() {
    //创建64个数组构成的链表，顺序由小到大
    struct Node{
        int x;
        struct Node* next;
        //struct Node* past;
    };
    typedef struct Node node;
    node *pre;
    pre=NULL;
    //node *r;
    //r=NULL;
    node begin;
    pre=&begin;

    int i=1;
    int num;

    int a[]={2,45,2,54,23,56,35,23,56,34,5,
             3,6,3,6,7,4,6,4,23,3,3,5,34,4,7,4,5,3};
    num=sizeof(a)/sizeof(a[0]);

    //做个单链表
    for(i=0;i<num;i++){
        struct Node * back=pre;
        pre=(node*)malloc(sizeof(node));
        back->next=pre;
        //pre->past=back;
        pre->x=a[i];
        pre->next=NULL;
    }
    //打印
    pre=&begin;
    for(pre=&begin;pre!=NULL;pre=pre->next){
        printf("%d\n",pre->x);
    }


    pre=&begin;
    node* r=pre->next;
    node* p=r->next;
    r->next=pre;
    pre->next=NULL;
    do{//链表反序
        pre=r;
        r=p;
        p=p->next;
        r->next=pre;
    }while(p->next!=NULL);
    p->next=r;
    pre=p;

    //打印
    printf("----------\n");
    while(pre->next!=NULL){
        printf("%d\n",pre->x);
        pre=pre->next;
    }

    //搜索指定数字5
    int cnt=0;
    for(pre=p;pre!=NULL;pre=pre->next,cnt++){
        if(pre->x==5){
            printf("find at location %d\n",cnt);

        }else{
            continue;}

    }
    if(cnt==num){
        printf("NOT FIND");
    }

    //清除内存
    pre=p;
    while(pre!=NULL)
    {
        free(pre);
        pre=pre->next;
    }


    return 0;
}
