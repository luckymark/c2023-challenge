//说1万遍“你好！”
#include <stdio.h>

int main(){
    system("chcp 65001");
    for (int i = 0; i < 10000; i++) {
        printf("你好 ");
    }
    return 0;
}
