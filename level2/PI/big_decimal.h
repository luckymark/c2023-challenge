//
// Created by Cz_13 on 2023/10/30.
//

#ifndef LEVEL2_BIG_INTEGER_H
#define LEVEL2_BIG_INTEGER_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct BigDecimal{
    // 浮点
    /*
     * 暂且不对诸如 0.000001 和 1000000等进行优化
     */
    int *integer;   // 数字
    int length;     // 实际长度, 不包含'-'和'.'
    int dot_index;    // 小数点位置, bigDecimal.value = integer * 10e(dot_index)
    int sign;   // >= 0 为正, < 0 为负
    struct BigDecimal* (*add)(struct BigDecimal*, struct BigDecimal*);
    struct BigDecimal* (*subtract)(struct BigDecimal*, struct BigDecimal*);
    struct BigDecimal* (*multiply)(struct BigDecimal*, struct BigDecimal*);
    struct BigDecimal* (*divide)(struct BigDecimal*, struct BigDecimal*, int);
    void (*print_big_decimal)(struct BigDecimal*);
    void (*set_integer)(struct BigDecimal*, int);
    void (*set_integer_by_index)(struct  BigDecimal*, int, int);
    char* (*to_string)(struct BigDecimal*);

} BigDecimal;

extern BigDecimal* create_big_decimal(int integer_size, int fraction_size, int sign);
extern BigDecimal* create_big_decimal_by_string(char *); // 将符合格式的字符串转变为大数字
#endif //LEVEL2_BIG_INTEGER_H
