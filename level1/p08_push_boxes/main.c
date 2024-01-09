#include <stdio.h>
#include<windows.h>
#include"push_boxes.h"
#include<time.h>
#include<stdbool.h>
bool flag=0;
COORD coord = {0,0};//��ʼ���λ��
DWORD bytes = 0;
int len=0;
int logo[6]={0};
int main() {
    CONSOLE_CURSOR_INFO mice;
    mice.dwSize=1;
    mice.bVisible=FALSE;
    HANDLE handle= GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorInfo(handle,&mice);//������ꡣ
    int step_number=0;
    time_t start_time=0,end_time=0;
    char maze[100][100];
    struct box location;
    struct box player;
    struct box boxes[6];
    struct box object[6];
    int dif=init_topic();
    init_0(maze);
    location=init_maze(maze,dif,&len,object,boxes);
    init_player(&player,dif);
    for(int i=0;i<len;i++)
    {
        boxes[i].l_x=location.x;
        boxes[i].l_y=location.y;
        boxes[i].sign='#';
    }
    for(int i=0;i<len;i++)
    {
        object[i].l_x=location.x;
        object[i].l_y=location.y;
        object[i].sign='&';
    }
    player.l_x=location.x;
    player.l_y=location.y;
    player.sign='@';
    print_maze(maze,location.x,location.y);
    HANDLE hOutBuf = CreateConsoleScreenBuffer(
            GENERIC_WRITE,
            FILE_SHARE_WRITE,
            NULL,
            CONSOLE_TEXTMODE_BUFFER,
            NULL
    );
    HANDLE hOutput = CreateConsoleScreenBuffer(
            GENERIC_WRITE,
            FILE_SHARE_WRITE,
            NULL,
            CONSOLE_TEXTMODE_BUFFER,
            NULL
    );
    start_time=clock();
    while(1){
        int key=key_check();
        if(key==-2) {
            FILE * fp;
            fp=fopen("D:/c2023-challenge/level1/c2023-challenge/level1/p08_push_boxes/The result","w");
            fprintf(fp,"Please try again!");
            fclose(fp);
            goto end;
        }
        double now_time=(double)(clock()-start_time)/CLOCKS_PER_SEC;
        int try=lose_check(now_time,step_number,dif);
        if(try<0){
            FILE * fp;
            fp=fopen("D:/c2023-challenge/level1/c2023-challenge/level1/p08_push_boxes/The result","w");
            if(try==-1)
                fprintf(fp,"Your time is over!Try again please!");
            else
                fprintf(fp,"Your steps are over!Try again please!");
            fclose(fp);
            goto end;
        }
        if(key==-1)
            continue;  //�����-1����û�д�������ͬʱ��������ҪһЩ��ʩ��
        int move=move_check(maze,key,&player,boxes,object);
        if(move==-1)
            continue;
        else {
            step_number++;
            init_object(maze,object);
            //print_maze(maze,location.x,location.y);
            flag=!flag;
            if(flag)
            {
                coord.Y = 0;
                for (int i = 0; i < location.y; i++,coord.Y++) {
                    WriteConsoleOutputCharacter(hOutBuf, maze[i], location.x+1 , coord, &bytes);
                    SetConsoleActiveScreenBuffer(hOutBuf);
                }
            }
            else{
                coord.Y = 0;
                for (int i = 0; i < location.y; i++,coord.Y++){
                    WriteConsoleOutputCharacter(hOutput, maze[i], location.x+1, coord, &bytes);
                    SetConsoleActiveScreenBuffer(hOutput);
                }
            }
            Sleep(300);
            if(move==2)
            {
                end_time=clock();
                double all_time=(double)(end_time-start_time)/CLOCKS_PER_SEC;
                double sco=score(all_time,step_number,dif);
                FILE * fp;
                fp=fopen("D:/c2023-challenge/level1/c2023-challenge/level1/p08_push_boxes/The result","w");
                fprintf(fp,"CONGRATULATION!!!YOU WIN!!!\n");
                fprintf(fp,"The time you spent:  %.2f\n",all_time);
                fprintf(fp,"The steps you took:  %d\n",step_number);
                fprintf(fp,"The score you get:  %.2f\n",sco);
                fclose(fp);
                break;
            }
        }
    }
    end:
    return 0;
}