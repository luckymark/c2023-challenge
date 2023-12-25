#include"gobang.h"
#include<time.h>
Board board_main={{0},{0},{0},{0}};
int step=0;
int turn=0;
int computer_next_i=0,computer_next_j=0;
FILE * fp,* fp_2;
int result=-1;
int main(){
    fp=fopen("D:/githubdesktop/c2023-challenge/gobang/debug_data.txt","w");
    fp_2=fopen("D:/githubdesktop/c2023-challenge/gobang/time_test.txt","w");
    srand(time(0));
    InitWindow(WIDTH,HEIGHT,"Go_bang");
    Image back_ground=LoadImage("D:/githubdesktop/c2023-challenge/gobang/board.png");
    Texture B_G= LoadTextureFromImage(back_ground);
    Image board= GenImageColor(WIDTH,HEIGHT,BLANK);
    init_point_location();

    while(!WindowShouldClose()){
        DrawTexture(B_G,0,0,WHITE);
        BeginDrawing();
        draw_background();
        if(turn==0)
            player_move(&board);
        else{
            computer_move(&board);
        }
        Texture t_texture= LoadTextureFromImage(board);
        DrawTexture(t_texture,0,0,WHITE);
        EndDrawing();
        UnloadTexture(t_texture);
        if(result==1){
            if(turn==0)
                result=2;
            else
                result=1;
            break;
        }
    }
    if(result!=-1){
        InitWindow(WIDTH/2,HEIGHT/2,"The_result");
        while(!WindowShouldClose()){
            ClearBackground(WHITE);
            BeginDrawing();
            if(result==1){
                DrawText("Congratulation!",80,150,50,RED);
                DrawText("The player win!",110,300,40,RED);
            }
            if(result==2){
                DrawText("Don't give up!",90,150,50,BLACK);
                DrawText("The Alpha_cat win!",80,300,40,BLACK);
            }
            EndDrawing();
        }
        CloseWindow();
    }
    fclose(fp);
    fclose(fp_2);
    return 0;
}