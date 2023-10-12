#include <windows.h>
#include <stdio.h>

extern char str[(102) * (102)];
extern int large;
extern int map[101][101];
void ClearConsole()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD home = {0, 0};
    DWORD written;
    FillConsoleOutputCharacter(hOut, ' ', 80 * 25, home, &written);
    FillConsoleOutputAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE, 80 * 25, home, &written);
    SetConsoleCursorPosition(hOut, home);
}
void Print()
{

    int i = 0,j = 0;
    //将str初始化为空
    str[0] = '\0';
    ClearConsole();
    for(i = 0;i < large;i++)
    {
        for (j = 0; j < large; j++)
        {
            if(map[i][j] == 0)
            {
                strcat(str,"■");
            }
            if(map[i][j] == 1)
            {
                strcat(str," ");
            }
            if(map[i][j] == 3)
            {
                strcat(str,"⊙");
            }
            if(map[i][j] == 4)
            {
                strcat(str,"☆");
            }
            //调试时测试用的值
            if(map[i][j] == 5)
            {
                strcat(str,"◇");
            }
            if(map[i][j] == -1)
                break;
        }
        if(-1 != map[i][0])
        {
            strcat(str,"\n");
        }
    }
    printf("%s ",str);
}