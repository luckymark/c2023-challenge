//
// Created by Cz_13 on 2023/10/26.
//
#include "big_decimal.h"

int main(){
    // setbuf(stdout, 0);
    BigDecimal *bigDecimal = create_big_decimal_by_string("3");
    char *s = bigDecimal->to_string(bigDecimal);
    printf("%s", s);
    return 0;
}