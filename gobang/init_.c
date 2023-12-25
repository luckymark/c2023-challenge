#include "gobang.h"
extern Board board_main;
void init_point_location(){
    for(int i=0;i<=16;i++){
        for(int j=0;j<=16;j++){
            if(i==0||j==0||i==16||j==16){
                board_main.lattice_extinct[i][j]=3;
            }
            else{
                board_main.point_location[i][j].x=LATTICE_WIDTH/2+(j-1)*LATTICE_WIDTH;
                board_main.point_location[i][j].y=LATTICE_WIDTH/2+(i-1)*LATTICE_WIDTH;
            }
        }
    }
}