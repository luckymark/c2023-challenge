#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <windows.h>

#define SCREEN_WIDTH 40
void ClearConsole()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD home = {0, 0};
    DWORD written;
    FillConsoleOutputCharacter(hOut, ' ', 80 * 25, home, &written);
    FillConsoleOutputAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE, 80 * 25, home, &written);
    SetConsoleCursorPosition(hOut, home);
}
int main() {
    int position = 0;
    int direction = 1;

    char word[] = "Uestc.ZhouZhengqi";
    int lenth = strlen(word);

    while (1) {
        ClearConsole();
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

}