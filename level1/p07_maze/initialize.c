#include "head_maze.h"

extern int map[101][101];
extern int large;
extern int level;
void Initialize(int num){
    int i = 0,j = 0;
    //地图只能是奇数
    if(num % 2 == 0)
        large++;
    //地图初始化为0内部初始化间隔的1，外部初始化为-1
    for(i = 0;i < large;i++){
        for (j = 0; j < large; j++) {
            if(i < large && j < large){
                map[i][j] = 0;
            }
            if(i >= large || j >= large){
                map[i][j] = -1;
            }
            if(i % 2 == 1 && j % 2 == 1){
                map[i][j] = 1;
            }
        }
    }
    //开始创建地图
    if(level == 1){
        Creat_01(1,1);
    }
    //把随机的路径初始化为1
    for (i = 0; i < large; i++) {
        for(j = 0;j < large; j++){
            if(map[i][j] == 5){
                map[i][j] = 1;
            }
        }
    }
    map[1][1] = 3;
    map[large - 2][large - 2] = 4;
}
