#include "SkipList.h"
int data_0[INIT_NUM]={5,34,0,-1,-7};
int main(){
    srand(time(0));
    New_Node head,tail;
    head.next=&tail;
    head.layer=0;
    head.data=INT_MIN;
    head.last=NULL;
    head.down=NULL;
    tail.next=NULL;
    tail.down=NULL;
    tail.data=INT_MAX;
    tail.last=&head;
    tail.layer=0;
    New_Node * head_p=&head;
    New_Node * tail_p=&tail;
    creat_SkipList(&head_p,&tail_p,data_0);
    print_list(head_p);
    insert(&head_p,&tail_p,-9);
    print_list(head_p);
    delete(&head_p,&tail_p,-7);
    print_list(head_p);
    return 0;
}