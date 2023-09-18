#include <stdio.h>
#include <windows.h>

#define MAX 120
#define SLEEP_TIME 10
#define SPEED 1

int main() {
    // setbuf(stdout, 0);  // 禁用缓冲区
    int index = 0;
    char str[MAX] = {};
    int last = 0;
    char c = 'c';
    int dx = SPEED;
    while(1){
        str[last] = last == MAX - 1 ? '\0' : ' ';
        str[index] = c;
        last = index;
        printf("%s", str);
        Sleep(SLEEP_TIME);
        system("cls");
        index += dx;
        if(index >= MAX){
            index = MAX - 1;
            dx *= -1;
        } else if(index < 0){
            index = 0;
            dx *= -1;
        }
    }
    return 0;
}
