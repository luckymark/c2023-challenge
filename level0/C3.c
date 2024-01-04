#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//计算数组的和
int sum_Arr(int size, int arr[]){
    int i, sum = 0;
    for (i = 0; i < size; i ++)
        sum = sum + arr[i];

    return sum;
}

//编写阶乘函数
int Fal(int beg_num){
    int pdt = 1;
    for (beg_num; beg_num > 0; beg_num --)
        pdt = beg_num * pdt;
    return pdt;
}

//用递归算阶乘
int re_Fal(int beg_num){
    int pdt;
    if (beg_num > 1) {
        pdt = beg_num * re_Fal(beg_num - 1);
    }
    else
        pdt = 1;
    return pdt;
}

//编写斐波那契函数
int Fibo(int x){
    if (x > 1)
        return (Fibo(x - 1) + Fibo(x - 2));
    else if (x == 1)
        return 1;
    else
        return 0;
}

//判断是否为直角三角形
int jud_RAT(int x, int y, int z){
    int arr[3], i, j, num;
    arr[0] = x;
    arr[1] = y;
    arr[2] = z;
    for(i = 0; i < 2; i ++){
        for(j = 0; j < 2 - i; j ++)
            if (arr[j] < arr[j + 1]) {
                num = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = num;
            }
    }
    if ((arr[0] ^ 2) == ((arr[1]) ^ 2) + ((arr[2]) ^ 2))
        printf("%s", "是直角三角形\n");
    else
        printf("%s", "不是直角三角形\n");
}

//判断两个矩形是否有重叠
struct Rec {
    int x;
    int y;
    int length;
    int width;
};


void Overloop(struct Rec rec1, struct Rec rec2){
    if (rec1.x < rec2.x + rec2.width &&
        rec1.x + rec1.width > rec2.x &&
        rec1.y < rec2.y + rec2.length &&
        rec1.y + rec1.length > rec2.y)
        printf("%s", "两个矩形重叠\n");
    else
        printf("%s", "两个矩形不重叠\n");
};


//将美元换算成人民币
float A_ts_C(float Ame, float rate){
    float Chi;
    Chi = Ame * rate;
    return Chi;
}


int main(){
    //数组和
    int input_arr[10000], i, input_num1;
    system("chcp 65001");
    printf("%s", "请输入一些数，我将为您计算其内所有元素的和\n");
    printf("%s","输入完第一个数字后，请换行输入下一个\n输入完毕后，请换行输入”0“\n");
    for (i = 0; ; i ++) {
        scanf("%d", &input_num1);
        printf("\n");
        if (input_num1 == 0)
            break;
        else
            input_arr[i] = input_num1;
    }
    printf("和是%d", sum_Arr(i + 1, input_arr));

    //阶乘
    int input_num;
    printf("%s", "请输入一个数字，我将为您计算它的阶乘\n");
    scanf("%d", &input_num);
    printf("结果是%d\n", re_Fal(input_num));

    //斐波那契
    int input_num2;
    printf("%s", "请输入一个数字，我将用斐波那契函数为您输出一个结果\n");
    scanf("%d", &input_num2);
    printf("结果是%d\n", Fibo(input_num2));

    //直角三角形
    int input_num3, input_num4, input_num5;
    printf("%s", "请输入三角形的三条边长，我将为您判断是不是直角三角形");
    printf("%s", "\n每输入一个数字，请空格一下\n");
    scanf("%d %d %d", &input_num3, &input_num4, &input_num5);
    jud_RAT(input_num3, input_num4, input_num5);

    //矩形重叠
    printf("%s", "请依次输入两个矩形的左上端点横、纵坐标、长、宽，每输入一个数字空一格，输入完一个矩形的数据后换行输入下一个矩形数据\n");
    struct Rec rec1, rec2;
    scanf("%d %d %d %d", &rec1.x, &rec1.y, &rec1.length, &rec1.width);
    printf("\n");
    scanf("%d %d %d %d", &rec2.x, &rec2.y, &rec2.length, &rec2.width);
    Overloop(rec1, rec2);

    //美元人民币换算
    float input_num6, input_num7;
    printf("%s", "请按顺序输入美元和汇率，我将为您将美元数换算成人民币\n每输入一个数字，请空格一次\n");
    scanf("%f %f", &input_num6, &input_num7);
    printf("换算成人民币应该是%f", A_ts_C(input_num6, input_num7));
}
