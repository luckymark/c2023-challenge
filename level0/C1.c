#include <stdio.h>
#include <stdlib.h>

int judge_pn(){
    int input_num;
    printf("%s", "请输入您需要判断的数字\n");
    scanf("%d", &input_num);
    if (input_num < 0)
        printf("%s", "您输入的是负数\n");
    else
        printf("%s", "您输入的是正数\n");
    return 0;
};

int judge_db(){
    int input_num;
    printf("%s", "请输入您需要判断的数字\n");
    scanf("%d", &input_num);
    if (input_num/2 == 0)
        printf("%s", "您输入的是偶数\n");
    else
        printf("%s", "您输入的是奇数\n");
    return 0;
}

void find_max(){
    int num_list[10000], input_num, i, * p;
    printf("%s", "您可以输入多个数字，每输入一个数字，请换行输入下一个\n输入完毕后，请换行输入'000'\n");
    for (i = 0; ;i ++) {
        scanf("%d", &input_num);
        if (input_num == 000)
            break;
        else
            num_list[i] = input_num;
    }
    int max_num;
    p = &max_num;
    max_num = num_list[0];
    for (i = 1;i <= (sizeof(num_list)/sizeof(num_list[0])); i++){
        if (num_list[i] <= max_num)
            continue;
        else
            *p = num_list[i];
    }
    printf("您所输入的所有数字中，最大的数字是：%d", max_num);
}

int main(){
    int i, input_num;
    system("chcp 65001");

    for (i = 1; ; i ++) {
        printf("%s", "请选择您的操作\n若需要判断一个数的正负，请输入1\n若需要判断一个数是否为偶数，请按2\n若需要帮您找出最大数，请按3\n若需要退出程序，请按0\n");
        scanf("%d", &input_num);
        if (input_num == 1)
            judge_pn();
        else if (input_num == 2)
            judge_db();
        else if (input_num == 3)
            find_max();
        else if (input_num == 0)
            break;
        else{
            printf("%s", "Please follow the instructions");
            break;
            }
    }
    return 0;
}