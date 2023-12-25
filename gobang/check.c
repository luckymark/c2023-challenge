#include"gobang.h"
extern Board board_main;
extern int turn;
Vector2 check_hit(void){
    Vector2 none={-1,-1};
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        Vector2 left_key_location=GetMousePosition();
        for(int i=1;i<=15;i++){
            for(int j=1;j<=15;j++){
                if((board_main.point_location[i][j].x-left_key_location.x)*(board_main.point_location[i][j].x-left_key_location.x)
                   +(board_main.point_location[i][j].y-left_key_location.y)*(board_main.point_location[i][j].y-left_key_location.y)<=625&&board_main.lattice_extinct[i][j]==0){
                    Vector2 l={j,i};
                    turn=1;
                    return l;
                }
            }
        }
        return none;
    }
    return none;
}