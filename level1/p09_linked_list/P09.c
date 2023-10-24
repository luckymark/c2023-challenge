#include <malloc.h>
#include <stdio.h>

typedef struct Node{
    int data;
    struct Node* p;
}Node;

Node* create(int data);
Node* insert(Node** before_node, int data);
void delete(Node** before_node);
void ergodic(Node* node);
Node* reverse(Node** fir_node, Node** end_node);
int find_value(Node* node, int value, int index);
Node* find_end(Node* node);
Node* find_front_node(Node** fir_node, Node** later_node);
Node* find_specific_node(Node** fir_node, int index, int i);

int main(){
    Node* node= create(0);

    //创建单向链表，含有50个节点
    for(int i=1; i < 50 ; ++ i) {
        insert(&node, (rand() % 100 + 1));
    }
    //遍历列表，显示各节点value
    ergodic(node);

    printf("\n");

    //反序所有节点
    Node* end_node= find_end(node);
    Node* new_fir_node=reverse(&node, &end_node);
    ergodic(new_fir_node);

    //查找第一个值为5的节点
    printf("\n");
    printf("\n");
    int serial=find_value(new_fir_node, 5, 1);
    if (serial == -1){
        printf("%s", "There isn't 5 in the list.\n");
    } else {
        printf("The first node whose value is 5 is %d\n", serial);

        //查找下一个值为5的节点
        serial = find_value(find_specific_node(&new_fir_node, serial, 1), 5, serial);
        if (serial == -1) {
            printf("%s", "There isn't another 5 in the list.\n");
        } else {
            printf("The second node whose value is 5 is %d", serial);
        }
    }

    return 0;
}


Node* create(int data){
    Node* fir_node=(Node* )malloc(sizeof(Node));

    fir_node->data= data;
    fir_node->p=NULL;

    return fir_node;
}

Node* insert(Node** before_node, int data){
    Node* new_node=(Node* )malloc(sizeof(Node));
    new_node->data=data;

    if ((*before_node)->p == NULL){
        (*before_node)->p = new_node;
        new_node->p=NULL;
    }
    else{
        new_node->p=(*before_node)->p;
        (*before_node)->p=new_node;
    }

    return new_node;
}

void delete(Node** before_node){
    if ((*before_node)->p->p == NULL){
        (*before_node)->p=NULL;
    }
    else{
        (*before_node)->p=(*before_node)->p->p;
    }
}

void ergodic(Node* node){
    if (node->p != NULL){
        printf("%d ", node->data);
        ergodic(node->p);
    }
    else{
        printf("%d", node->data);
    }
}

Node* reverse(Node** fir_node, Node** end_node){
    Node* front_node=find_front_node(fir_node, end_node);
    (*end_node)->p=front_node;
    if (*fir_node != front_node) {
        reverse(fir_node, &front_node);
    } else {
        (*fir_node)->p = NULL;
    }
    return *end_node;
}

int find_value(Node* node, int value, int index){
    if (node->p != NULL){
        if (node->data == value){
            return index;
        }
        else{
            ++ index;
            find_value(node->p, value, index);
        }
    }
    else
        return -1;
}

Node* find_end(Node* node){
    if (node->p == NULL){
        return node;
    } else{
        find_end(node->p);
    }
}

Node* find_front_node(Node** fir_node, Node** later_node){
    if ((*fir_node)->p == *later_node){
        return *fir_node;
    } else {
        find_front_node(&((*fir_node)->p), later_node);
    }
}

Node* find_specific_node(Node** fir_node, int index, int i){
    if (i == index + 1){
        return *fir_node;
    }
    else{
        ++ i;
        find_specific_node(&((*fir_node)->p), index, i);
    }
}