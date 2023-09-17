#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    system("chcp 65001");
    //说10000次你好
    int i = 1;
    for (i; i <= 10000; i++)
        printf("%s", "Hello!");
    //尝试代码的运行效果
    /*
    system("color 0a");
    while(1){
        printf("0 1");
    system("color 0a");
    }
    while(1){
        printf("%d\t",rand()/1000);
    }
    */

    //打印2-100的所有偶数
    int j;
    for (j = 2; j <= 100; j ++){
        if ((j % 2) == 0)
            printf("%d\n", j);
        else
            continue;
    }
    printf("\n");


    //打印1-100能被3整除但不能被5整除的数
    int k;
    for (k = 1; k <= 100; k ++){
        if (((k % 3) == 0) && ((k % 5) != 0))
            printf("%d\n", k);
        else
            continue;
    }
    printf("\n");


    //打印1-100内尾数为7的数及其总和（不再重复打印倍数代码）
    int u, sum = 0;
    for (u = 1; u <= 100; u ++) {
        if ((u % 10) == 7) {
            printf("%d\n", u);
            sum = sum + u;
        }
        else
            continue;
    }
    printf("\n这些数的和是%d\n", sum);

    //打印一个九九乘法表
    int v = 1;
    while (v <= 9){
        int j = 1;
        while (j <= v){
            printf("%d * %d = %d  ", v, j, (v * j));
            j ++;
        }
        v ++;
        printf("\n");
    }

    //逆序输出输入的n个数
    int num_list[10000], len;
    char input_num[4];
    printf("%s","请输入一些数字，我将为你将它们逆序输出\n输入完第一个数字后，请换行输入下一个\n输入完毕后，请换行输入”000“\n");
    for (i = 0; ; i ++){
        scanf("%s", &input_num);
        printf("\n");
        if (strcmp(input_num, "000") == 0)
            break;
        else
            num_list[i] = atoi(input_num);
    }
    for (len = i; len >= 0; len --)
        printf("%d\n", num_list[len]);

    //输入5个0-9的数并打印未输入的数
    int num_list2[5], o = 0, found_num = 10;
    printf("%s","请输入5个0-9的数，我会为您打印未输入的数\n");
    while(o < 5) {
        scanf("%d", &num_list2[o]);
        printf("\n");
        o ++;
    }
    for (i = 0; i <= 9; i ++){
        for (j = 0; j <= 4; j ++){
            if (i == num_list2[j])
                found_num = i;
            else
                continue;
        }
        if (i != found_num)
            printf("%d  ",i);
    }

    printf("\n");

    //为输入的0-9的五个数排序
    printf("%s", "为他们排序(冒泡)\n");
    int arr[5], num, temp_arr[10];
    for (i = 0; i <5; i++) {
        scanf("%d", &arr[i]);
        printf("\n");
    }

    //冒泡排序
    for (i = 0; i < 4; i ++){
        for (j = 0; j < 4 - i; j++){
            if (arr[j] > arr[j + 1]){
                num = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = num;
            }
        }
    }
    printf("%s", "排序后的数字是");

    for (i = 0; i < 5; i ++)
        printf("%d ", arr[i]);

    printf("\n\n");

    //桶排序
    printf("%s", "请输入0-9的五个数字，我将为他们排序(桶)\n");

    for (i = 0; i < 10; i ++)
        temp_arr[i] = 0;

    for (i = 0; i < 5; i ++)
        temp_arr[arr[i]] ++;

    for (i = 0, j = 0; i < 10; i ++)
        while (temp_arr[i] != 0){
            arr[j] = i;
            j ++;
            temp_arr[i] --;
        }

    for (i = 0; i < 5; i ++)
        printf("%d ", arr[i]);
}
