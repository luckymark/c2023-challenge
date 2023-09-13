#include <cstdio>
#include <windows.h>
#include <conio.h>
using namespace std;

char map[11][21]={
        "T  #################",
        "#          @      *#",
        "# # ####   ##### ###",
        "  # ###  #    ## ###",
        "  @ ### ##  * ## ###",
        "  #     ### #   ##M#",
        "# # ### ###   # ##E#",
        "#          *### ##O#",
        "### ########### ##W#",
        "###  *Bin#Meow#    #",
        "####################"
};
int main()
{
    CONSOLE_CURSOR_INFO c={1,0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&c);
    printf("使用 w s a d控制人物T移动 将'@'扔进垃圾桶'*'处\r\n");
    system("pause");
    system("cls");
    for(int i=0;i<=10;i++)
        puts(map[i]);
    int x=0,y=0,count=0,step=0;
    bool ThrowMyself=false;
    for(;;){
        char input=getch();
        step++;
        switch(input){
            case 'w':
                if(x==0)break;
                if(map[x-1][y]!='#') {
                    map[x][y] = ' ';
                    if(map[x-1][y]=='@'&&map[x-2][y]==' ')
                        map[x-2][y]='@';
                    else if(map[x-1][y]=='@'&&map[x-2][y]=='*'){
                        map[x-2][y]=' ';
                        map[x-1][y]=' ';
                        count++;
                    }else if(map[x-1][y]=='*'){
                        ThrowMyself=true;
                        map[x - 1][y] = 'T';
                        break;
                    }
                    map[x - 1][y] = 'T';
                    x -= 1;
                }
                break;
            case 's':
                if(x==10)break;
                if(map[x+1][y]!='#') {
                    map[x][y] = ' ';
                    if(map[x+1][y]=='@'&&map[x+2][y]==' ')
                        map[x+2][y]='@';
                    else if(map[x+1][y]=='@'&&map[x+2][y]=='*'){
                        map[x+2][y]=' ';
                        map[x+1][y]=' ';
                        count++;
                    }else if(map[x+1][y]=='*'){
                        ThrowMyself=true;
                        map[x + 1][y] = 'T';
                        break;
                    }
                    map[x + 1][y] = 'T';
                    x += 1;
                }
                break;
            case 'a':
                if(y==0)break;
                if(map[x][y-1]!='#') {
                    map[x][y] = ' ';
                    if(map[x][y-1]=='@'&&map[x][y-2]==' ')
                        map[x][y-2]='@';
                    else if(map[x][y-1]=='@'&&map[x][y-2]=='*'){
                        map[x][y-2]=' ';
                        map[x][y-1]=' ';
                        count++;
                    }
                    else if(map[x][y-1]=='*'){
                        ThrowMyself=true;
                        map[x][y-1] = 'T';
                        break;
                    }
                    map[x][y - 1] = 'T';
                    y -= 1;
                }
                break;
            case 'd':
                if(y==20)break;
                if(map[x][y+1]!='#') {
                    map[x][y] = ' ';
                    if(map[x][y+1]=='@'&&map[x][y+2]==' ')
                        map[x][y+2]='@';
                    else if(map[x][y+1]=='@'&&map[x][y+2]=='*'){
                        map[x][y+2]=' ';
                        map[x][y+1]=' ';
                        count++;
                    }
                    else if(map[x][y-1]=='*'){
                        ThrowMyself=true;
                        map[x][y-1] = 'T';
                        break;
                    }
                    map[x][y + 1] = 'T';
                    y += 1;
                }
                break;
        }
        system("cls");
        for(int i=0;i<=10;i++)
            puts(map[i]);
        if(ThrowMyself)
            break;
        if(count==2)
            break;
    }
    printf(ThrowMyself?"you threw yourself into the rubbish bin!\r\n":"you win!\r\n");
    printf("You walked %d steps & got %d score.\r\n",step,ThrowMyself?0:count*50-step);
    system("pause");
    return 0;
}