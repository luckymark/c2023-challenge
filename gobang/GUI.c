#include"gobang.h"
void draw_background(){
    Vector2 start_v={LATTICE_WIDTH/2,LATTICE_WIDTH/2};
    Vector2 end_v={WIDTH-LATTICE_WIDTH/2,LATTICE_WIDTH/2};
    for(int i=1;i<=15;i++){
        DrawLineEx(start_v,end_v,5,BLACK);
        start_v.y+=LATTICE_WIDTH;
        end_v.y+=LATTICE_WIDTH;
    }
    start_v.x=LATTICE_WIDTH/2;
    start_v.y=LATTICE_WIDTH/2;
    end_v.x=LATTICE_WIDTH/2;
    end_v.y=HEIGHT-LATTICE_WIDTH/2;
    for(int i=1;i<=15;i++){
        DrawLineEx(start_v,end_v,5,BLACK);
        start_v.x+=LATTICE_WIDTH;
        end_v.x+=LATTICE_WIDTH;
    }
    DrawCircle(LATTICE_WIDTH/2+3*LATTICE_WIDTH,LATTICE_WIDTH/2+3*LATTICE_WIDTH,10,BLACK);
    DrawCircle(LATTICE_WIDTH/2+11*LATTICE_WIDTH,LATTICE_WIDTH/2+3*LATTICE_WIDTH,10,BLACK);
    DrawCircle(LATTICE_WIDTH/2+3*LATTICE_WIDTH,LATTICE_WIDTH/2+11*LATTICE_WIDTH,10,BLACK);
    DrawCircle(LATTICE_WIDTH/2+11*LATTICE_WIDTH,LATTICE_WIDTH/2+11*LATTICE_WIDTH,10,BLACK);
    DrawCircle(LATTICE_WIDTH/2+7*LATTICE_WIDTH,LATTICE_WIDTH/2+7*LATTICE_WIDTH,10,BLACK);
}