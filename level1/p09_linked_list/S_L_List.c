//
// Created by 14212 on 2023/10/11.
//
#include "S_L_List.h"
New_Node * init_list(){
    New_Node * first;
    first=(New_Node *)malloc(sizeof(New_Node));
    first->link=NULL;
    return first;
}
void Creat_List(New_Node * first){
    srand(time(0));
    New_Node * q=first;
    int flag=0;
    for(int i=0;i<10;i++){
        int rand_num=rand()%10;
        if(flag==0){
            q->data=rand_num;
            flag=1;
        }
        else{
            New_Node * p= (New_Node *)malloc(sizeof(New_Node));
            p->data=rand_num;
            p->link=q->link;
            q->link=p;
            q=q->link;
        }
    }
}
void print_list(New_Node *first){
    New_Node * p=first;
    printf("The List is :");
    while(p!=NULL){
        printf("%d ",p->data);
        p=p->link;
    }
    printf("\n");
}
New_Node * reverse_list(New_Node * first){
    int pp=0;
    New_Node * first_copy=init_list();
    New_Node * p=first;
    New_Node * p_copy=first_copy;
    while(p!=NULL){
        if(pp==0){
            first_copy->data=p->data;
            pp=1;
        }
        else{
            New_Node * n=malloc(sizeof(New_Node));
            n->data=p->data;
            n->link=p_copy;
            p_copy=n;
        }
        New_Node * k=p;
        p=p->link;
        free(k);
    }
    return p_copy;
}
int research_num(New_Node * first,int x,int cnt){
    int cont=0;
    int place=0;
    int now_place=0;
    New_Node * p=first;
    while(p!=NULL){
        if(p->data==x){
            place=now_place;
            cont++;
        }
        if(cnt==cont)
            break;
        else {
            now_place++;
            p = p->link;
        }
    }
    if(cnt==cont)
        return place;
    else
        return -1;
}