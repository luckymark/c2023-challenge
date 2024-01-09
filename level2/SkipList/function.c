#include "SkipList.h"
//进栈,头插法
void push_stack(Stack ** n,New_Node * location){
    Stack * p=(Stack *)malloc(sizeof(Stack));
    p->Node=location;
    if((*n)==NULL){
        (*n)=p;
        p->next=NULL;
    }
    else{
        p->next=(*n)->next;
        (*n)=p;
    }
}
//出栈，从头出栈
New_Node * pop_stack(Stack ** n){
    Stack * p=(*n);
    (*n)=p->next;
    New_Node * temp=p->Node;
    free(p);
    return temp;
}
int random_layer(){
    int test;
    int sum=0;
    while((test=rand()%2)==1){
        sum+=1;
    }
    return sum;
}
void insert(New_Node ** head,New_Node ** tail,int d){//头指针和尾指针是要存放数据的，头指针存放最小值，尾指针存放最大值
    New_Node * p=(New_Node *)malloc(sizeof(New_Node));
    p->data=d;
    int l=random_layer();
    p->layer=l;
    Stack * top=NULL;
    int num=p->data;
    New_Node * k=(*head);//寻找插入位置，用k试探
    int temp_l=k->layer;
    while(temp_l>0){
        if(num<(k->next)->data){
            push_stack(&top,k);
            k=k->down;
            temp_l--;
        }
        else{
            k=k->next;
        }
    }
    //接下来在原始链表中找到目标位置
    while(num>=(k->next)->data){
        k=k->next;
    }
    //找到原始列表位置后，直接插入
    p->next=k->next;
    (k->next)->last=p;
    k->next=p;
    p->last=k;//双向链表控制前一个节点
    p->down=NULL;
    //接下来出栈
    New_Node * p_copy=p;//用于迭代
    while(top!=NULL){
        New_Node * q= pop_stack(&top);
        New_Node * sy=(New_Node *)malloc(sizeof(New_Node));
        sy->next=q->next;
        (q->next)->last=sy;
        q->next=sy;
        sy->last=q;//双向链表控制前一个节点
        sy->down=p_copy;
        sy->layer=l;
        sy->data=num;
        p_copy=sy;
    }
    //接下来判断是否超额,超额则建立新的节点

    while((*head)->layer<l){
        New_Node * new_head=(New_Node *)malloc(sizeof(New_Node));
        New_Node * new_tail=(New_Node *)malloc(sizeof(New_Node));
        new_head->down=(*head);
        new_head->data=(*head)->data;
        new_head->layer=(*head)->layer+1;
        new_head->last=NULL;
        (*head)=new_head;
        new_tail->down=(*tail);
        new_tail->data=(*tail)->data;
        new_tail->layer=(*tail)->layer+1;
        new_tail->next=NULL;
        (*tail)=new_tail;
        New_Node * q=(New_Node *)malloc(sizeof(New_Node));
        (*head)->next=q;
        q->last=(*head);
        q->next=(*tail);
        (*tail)->last=q;//双向链表控制前一个节点
        q->data=num;
        q->layer=l;
        q->down=p_copy;
        p_copy=q;
    }
}
void creat_SkipList(New_Node ** head_point,New_Node ** tail_point,int * data){
    for(int i=0;i<INIT_NUM;i++){
        insert(head_point,tail_point,data[i]);
    }
}
New_Node * research(New_Node * head,int num){
    int temp_l=head->layer;
    New_Node * k=head;
    while(temp_l>0){
        if(num<(k->next)->data){
            k=k->down;
            temp_l--;
        }
        else{
            if(num==(k->next)->data){
                return k->next;
            }
            else{
                k=k->next;
            }
        }
    }
    //如果在索引中没有找到则在原始列表中找
    while(num>=(k->next)->data){
        if(num==(k->next)->data){
            return k->next;
        }
        else{
            k=k->next;
        }
    }
    return NULL;
}
void delete(New_Node ** head,New_Node ** tail,int d){//删除数字为d的一个节点
    New_Node * location= research(*head,d);
    if(location==NULL)
        return;
    while(location!=NULL){
        if(location->last==(*head)&&location->next==(*tail)){
            New_Node * head_temp=(*head);
            (*head)=head_temp->down;
            free(head_temp);
            New_Node * tail_temp=(*tail);
            (*tail)=tail_temp->down;
            free(tail_temp);
            New_Node * loc_temp=location;
            location=loc_temp->down;
            free(loc_temp);
        }
        else{
            New_Node * loc_temp=location;
            (loc_temp->last)->next=loc_temp->next;
            (loc_temp->next)->last=loc_temp->last;
            location=loc_temp->down;
            free(loc_temp);
        }
    }
}
void print_list(New_Node *head){
    New_Node * head_temp=head;
    while(head_temp->down!=NULL)
        head_temp=head_temp->down;
    New_Node * k=head_temp->next;
    while(k->next!=NULL){
        printf("%d ",k->data);
        k=k->next;
    }
    printf("\n");
}