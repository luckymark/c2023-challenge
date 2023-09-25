#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SCREEN_WIDTH 80

int main() {
    int position = 0;
    int direction = 1;

    char word[] = "Uestc.ZhouZhengqi";
    int lenth = strlen(word);

    while (1) {
        system("cls");
        //位置移动
        for (int i = 0; i < position; i++) {
            printf(" ");
        }
        printf("%s\n", word);
        position += direction;
        //判断方向
        if (position >= SCREEN_WIDTH - lenth + 1 || position <= 0) {
            direction *= -1;
        }

        usleep(100000); // 控制运动速度，单位为微秒
    }

    return 0;
}