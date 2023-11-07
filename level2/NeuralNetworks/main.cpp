//
// Created by cz241 on 11/7/2023.
//
#include <raylib.h>
#include "Network.h"

bool WritingData[8][8]={false};

void DrawInk(){
    for(int x=0;x<8;x++){
        for(int y=0;y<8;y++){
            if(WritingData[x][y]){
                DrawRectangle(100+x*50,100+y*50,50,50,BLUE);
            }
        }
    }
}
void DrawGridLine(){
    for(int x=0;x<=8;x++){
        DrawLine(100+x*50,100,100+x*50,500,WHITE);
        DrawLine(100,100+x*50,500,100+x*50,WHITE);
    }
}
void DrawButtons(){
    Vector2 mouse=GetMousePosition();
    DrawRectangle(600,100,100,50,BLUE);
    DrawText("Clear",610,110,30,WHITE);
    DrawRectangle(600,300,100,50,BLUE);
    DrawText("Test",610,310,30,WHITE);

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (mouse.x >= 600 && mouse.x <= 700 && mouse.y >= 100 && mouse.y <= 150) {
            //Clear
            for(int x=0;x<8;x++){
                for(int y=0;y<8;y++){
                    WritingData[x][y]=false;
                }
            }
        }
        else if(mouse.x >= 600 && mouse.x <= 700 && mouse.y >= 300 && mouse.y <= 350) {
            //Test

        }
    }

}

int main(){
    InitWindow(800,600,"Hello World!");
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(SKYBLUE);
        DrawGridLine();
        DrawButtons();
        DrawInk();
        int x=(GetMouseX()-100)/50;
        int y=(GetMouseY()-100)/50;
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
            if(x>=0&&x<8&&y>=0&&y<8)
              WritingData[x][y]=true;
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}