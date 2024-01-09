#include <cstdio>
#include <windows.h>
#include <conio.h>
using namespace std;

char map[11][21]={
        "T  #################",
        "#                  #",
        "### ####   ##### ###",
        "### ###  #    ## ###",
        "#   ### ### # ## ###",
        "# #     ### #   ##M#",
        "# # #######   # ##E#",
        "#   ###     ### ##O#",
        "### ########### ##W#",
        "###      #Meow#     ",
        "####################"
};
int main()
{
    CONSOLE_CURSOR_INFO c={1,0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&c);
    printf("使用 w s a d控制人物T移动..\r\n");
    system("pause");
    system("cls");
    for(int i=0;i<=10;i++)
        puts(map[i]);
    int x=0,y=0;
    for(;;){
        char input=getch();
        switch(input){
            case 'w':
                if(x==0)break;
                if(map[x-1][y]!='#') {
                    map[x][y] = ' ';
                    map[x - 1][y] = 'T';
                    x -= 1;
                }
                break;
            case 's':
                if(x==10)break;
                if(map[x+1][y]!='#') {
                    map[x][y] = ' ';
                    map[x + 1][y] = 'T';
                    x += 1;
                }
                break;
            case 'a':
                if(y==0)break;
                if(map[x][y-1]!='#') {
                    map[x][y] = ' ';
                    map[x][y - 1] = 'T';
                    y -= 1;
                }
                break;
            case 'd':
                if(y==20)break;
                if(map[x][y+1]!='#') {
                    map[x][y] = ' ';
                    map[x][y + 1] = 'T';
                    y += 1;
                }
                break;
        }
        system("cls");
        for(int i=0;i<=10;i++)
            puts(map[i]);
        if(x==9&&y==19)
            break;
    }
    printf("you win!\r\n");
    system("pause");
    return 0;
}