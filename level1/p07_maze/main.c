
#include <time.h>
#include <windows.h>
#include "head_maze.h"


int map[101][101] = { 0 };
int large = 0;
int level = 0;
int now_x;
int now_y;
char str[(102) * (102)] = {'\0'};







int main(){
    system("chcp 65001");
    system("color 0A");
    srand((unsigned )time(NULL));
    int flag = 0;
    Menu();
    Initialize(large);
    while (1){
        flag = Move();
        if(1 == flag || -1 == flag){
            return 0;
        }
    }
}








