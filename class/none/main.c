#include <stdio.h>
#include <string.h>

int main(){

    printf("hello world!");
    char key[]="zhouzhengqi";
    int  b = strlen(key);
    printf("%llu ", sizeof(key));
    printf("%d ",b);
    return 0;
}
