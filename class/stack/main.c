//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//
//typedef struct Node
//{
//    int data;//定义数据域
//    struct Node *next;//定义后继指针域
//}Node;
//
//
//
//Node *initStack()
//{
//    Node *S = (Node *)malloc(sizeof(Node));//申请内存空间
//    S->data = 0;//第一个是头指针，数据域代表栈内的元素个数
//    S->next = NULL;//头指针指向空
//    return S;//返回头指针
//}
//int isEmpty(Node *S)
//{
//    if(S->next==NULL||S->data==0)//头指针后继为空或者头指针的数据域为0，表示该栈为空
//        return 1;
//    else
//        return 0;
//}
//
//int getTop(Node *S)
//{
//    if(isEmpty(S))//先判断栈是否为空
//        return -1;
//    else
//        return S->next->data;
//}
//
//void push(Node *S,int data)
//{
//    Node *node = (Node *)malloc(sizeof(Node));
//    node->data = data;//将数据写入新节点中
//    node->next = S->next;//新节点后继指向头节点的后继（新节点指向头节点的后一个节点）
//    S->next = node;//头节点指向新节点
//    S->data++;//头节点数据域加一
//}
//
//int pop(Node *S)
//{
//    int data;
//    if(isEmpty(S))//判断栈是否为空
//    {
//        return -1;
//    }
//    else
//    {
//        Node *node = S->next;//申请新节点存放头节点的下一个节点（第一个节点）
//        data = node->data;//将栈顶元素赋值给data
//        S->next = node->next;//将头节点指针直接指向头节点的下下一个节点
//        free(node);//释放第一个节点（栈顶元素）
//        return data;//返回栈顶元素
//    }
//}
//
//void printStack(Node *S)
//{
//    S = S->next;//头节点的下一个节点才是第一个节点
//    while(S)//S不空循环继续
//    {
//        printf("%d ",S->data);
//        S = S->next;//节点往后走
//    }
//    printf("\n");
//}
//
//int main()
//{
//    int i,j;
//    Node *S = initStack();//建立栈并初始化（相当于建立单链表并初始化）
//    for(i=1;i<=5;i++)
//    {
//        push(S,i);//验证进栈函数
//    }
//    printStack(S);//验证遍历输出函数
//    j = getTop(S);//验证取栈顶元素函数
//    printf("%d\n",j);
//    j = pop(S);//验证出栈操作（删除栈顶元素）
//    printStack(S);
//    printf("%d\n",j);
//    return 0;
//}