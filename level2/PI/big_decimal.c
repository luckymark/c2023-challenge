//
// Created by Cz_13 on 2023/10/30.
//
#include "big_decimal.h"

BigDecimal* add(BigDecimal*, BigDecimal*);
BigDecimal* subtract(BigDecimal*, BigDecimal*);
BigDecimal* multiply(BigDecimal*, BigDecimal*);
BigDecimal* divide(BigDecimal*, BigDecimal*, int);
char* to_string(BigDecimal*);
void print_big_decimal(BigDecimal*);
void set_integer(BigDecimal*, int);
void set_integer_by_index(BigDecimal*, int, int);

BigDecimal* create_big_decimal(int integer_size, int fraction_size, int sign){
    /*
     * 创建一位有多少位小数和多少位整数的decimal
     */
    BigDecimal* res = (BigDecimal *)malloc(sizeof(BigDecimal));
    res -> integer = (int*) malloc(sizeof(int) * (integer_size + fraction_size));
    res -> length = 0;
    res -> sign = sign >= 0 ? 1 : -1;
    res -> add = add;
    res -> subtract = subtract;
    res -> multiply = multiply;
    res -> divide = divide;
    res -> to_string = to_string;
    res -> print_big_decimal = print_big_decimal;
    res -> set_integer = set_integer;
    res -> set_integer_by_index = set_integer_by_index;
    return res;
}

BigDecimal* add(BigDecimal* bigDecimal1, BigDecimal* bigDecimal2){
    /*
     * 将bigDecimal2加到bigDecimal1上, 返回bigDecimal1更新后的值
     * 相当于 dot_index = integer * 10e(dot_index - length), dot_index != -1
     */
    //  依据小数点位置对齐

    // 123.4567      +
    //   1.23456
    int dot_index1 = bigDecimal1 -> dot_index;  // i1 * 10e(dot_index1)
    int dot_index2 = bigDecimal2 -> dot_index;  // i2 * 10e(dot_index2)

    int deviation = dot_index1 - dot_index2; // bigDecimal2 相对于 bigDecimal1偏移的位置

    for(int i = 0;;){

    }

    // 按对齐后创建新的integer, (判断对齐后首位是否进位来确定长度)并释放之前的

    // 直接相加

    // 动态规划进位

    return bigDecimal1;
}

BigDecimal* subtract(BigDecimal* bigDecimal1, BigDecimal* bigDecimal2){
    return bigDecimal1;
}

BigDecimal* multiply(BigDecimal* bigDecimal1, BigDecimal* bigDecimal2){
    return bigDecimal1;
}

BigDecimal* divide(BigDecimal* bigDecimal1, BigDecimal* bigDecimal2, int i){
    return bigDecimal1;
}

void set_integer(struct BigDecimal* bigDecimal, int value){
    int value_size;
}

void print_big_decimal(BigDecimal* bigDecimal){
    printf("%s", bigDecimal->to_string(bigDecimal));
}

void set_integer_by_index(BigDecimal* bigDecimal, int value, int index){

}

BigDecimal* create_big_decimal_by_string(char* decimal){
    /*
     * 将严格符合格式的字符串转换为BigDecimal
     */
    BigDecimal* res = (BigDecimal *) malloc(sizeof(BigDecimal));
    int length = 0;
    int sign = 1;
    char* dec = decimal;
    if(decimal[0] == '-'){
        // 负数
        sign = -1;
        dec ++;
    }

    int i = 0;
    int dot_index = 0;  // 小数点出现的位置, 为0则表示没有出现小数点
    int is_dot = 0;
    while(dec[i] != '\0'){
        if (is_dot == 1){
            dot_index --;   // 由于存储方式, 小数点仅会左移, 故仅支持小于0的情况
        }
        if(dec[i] != '.' ){
            length ++;
        } else {
            is_dot = 1;
        }
        i ++;
    }
    int* integer = (int *) malloc(sizeof(int) * length);
    i = 0;
    int j = 0;
    while (dec[i] != '\0'){
        if(dec[i] != '.'){
            integer[j] = dec[i] - '0';  // 允许integer的首位为0
            j ++;
        }
        i ++;
    }
    res->sign = sign;
    res->integer = integer;
    res->dot_index = dot_index;
    res->length = length;
    res -> add = add;
    res -> subtract = subtract;
    res -> multiply = multiply;
    res -> divide = divide;
    res -> to_string = to_string;
    res -> print_big_decimal = print_big_decimal;
    res -> set_integer = set_integer;
    res -> set_integer_by_index = set_integer_by_index;
    return res;
}

char* to_string(BigDecimal* bigDecimal){
    int sign_d = 0, dot_d = 0; // 由正负号和点号带来的偏差
    if(bigDecimal->sign == -1){
        sign_d = 1;
    }
    if(bigDecimal->dot_index != 0){
        dot_d = 1;
    }
    int string_len = bigDecimal->length + sign_d + dot_d;
    char* string = (char *) malloc(sizeof(char) * (string_len + 1));
    memset(string, 0, sizeof(char) * (string_len + 1));
    if(sign_d == 1){
        string[0] = '-';
    }

    int dot_index = bigDecimal->length + bigDecimal->dot_index;

    for(int i = sign_d, j = 0; i < string_len; i++, dot_index --){
        if(dot_index == 0 && dot_d == 1){
            // 如果没有小数点, 显然不会进入if
            string[i] = '.';
            continue;
        }
        string[i] = (char)(bigDecimal->integer[j++] + '0');
    }
    return string;
}