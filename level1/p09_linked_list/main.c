#include "S_L_List.h"
int main() {
    New_Node * first=init_list();
    int first_num,second_num;
    Creat_List(first);
    print_list(first);
    first= reverse_list(first);
    print_list(first);
    first_num= research_num(first,5,1);
    second_num= research_num(first,5,2);
    printf("The first 5: %d\n",first_num);
    printf("The second 5: %d\n",second_num);
    return 0;
}