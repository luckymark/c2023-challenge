#include "link.h"

Node *head = NULL;

int search_m(int isAll){
    int target = 0;
    printf("pls input target number: ");
    scanf("%d", &target);
    int ret = search(head, target);
    int d = 0;
    while(ret != -1){
        ret += d;
        printf("%d\n", ret);
        int flag = 0;
        if(!isAll){
            printf("input \'n\' to find the next\n"
                   "input \'e\' to exit\n");
            char sub_cmd[64];
            scanf("%63s", sub_cmd);
            if(!strcmp(sub_cmd, "n")){
                flag = 1;
            }else if(!strcmp(sub_cmd, "e")){
                flag = 2;
            }
        }
        if(isAll || flag == 1){
            Node *p = head;
            d = ret;
            for(int i = 0; i < d; i ++){
                p = p -> next;
            }
            ret = search(p, target);
        }else if(flag == 2){
            return 0;
        }
    }
    return 1;
}

int get_cmd(){
    char cmd[64];
    printf("pls input command: ");
    scanf("%63s", cmd);
    if(!strcmp(cmd, "insert")){
        printf("pls input value: ");
        Node *nd = (Node *)malloc(sizeof(int) + sizeof(Node *));
        scanf("%d",&(nd->value));
        head = insert(head, nd);
    }else if(!strcmp(cmd, "print")){
        print(head);
    }else if(!strcmp(cmd, "exit")){
        return 0;
    }else if(!strcmp(cmd, "search")){
        search_m(0);
    }else if(!strcmp(cmd, "search_all")){
        search_m(1);
    }else if(!strcmp(cmd, "r_sort")){
        head = r_sort(head);
        printf("down\n");
    }else if(!strcmp(cmd, "help")){
        printf("r_sort\t反序\n"
               "search\t查询某值的第一个位置\n"
               "exit\t离开\n"
               "print\t输出链表\n"
               "search_all\t查询链表中所有为某值的节点\n"
               );
    }
    return 1;
}

int main(){
    system("chcp 65001");
    while(get_cmd());
    return 0;
}
