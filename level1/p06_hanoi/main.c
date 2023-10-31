#include <stdio.h>

int func(int n, char a, char b, char c){
    /*
     * 递归处理
     *
     * 将a中n个盘子移到c
     */
    if(n <= 0){
        return -1;
    }else if(n == 1){
        printf("%c -> %c\n", a, c);
        return 1;
    }else{
        // 先从A到B, 移动n-1个
        func(n - 1, a, c, b);
        // 将最后一个移到c
        printf("%c -> %c\n", a, c);
        // 将b中移到c
        func(n - 1, b, a, c);
    }
    
}

int main() {
    func(5, 'A', 'B', 'C');
    return 0;
}
