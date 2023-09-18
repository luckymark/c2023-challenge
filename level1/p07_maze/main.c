#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define MIN_LEN 3
#define MIN_WID 3
#define MAX_LEN 255
#define MAX_WID 255
#define SPACE ' '
#define WALL '#'
#define PLAYER '@'
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int **createStack(int size);
int push(int **stack, int x, int y, int location);
int pop(int **stack, int location);
char **createMaze(int length, int width);
int playerMove(char **maze, int *player);

int push(int **stack, int x, int y, int location){
    stack[location][0] = x;
    stack[location][1] = y;
    return 0;
};

int pop(int **stack, int location){
    stack[location][0] = 0;
    stack[location][1] = 0;
    return 0;
}


char **createMaze(int length, int width){
    /*
     * 回溯算法
     * length决定一维大小
     * width决定二维大小
     * */
    srand(time(0));

    if(length < MIN_LEN || width < MIN_WID || length > MAX_LEN || width > MAX_WID){
        return NULL;
    }
    // 生成栈用于储存状态
    int **stack = createStack(length * width);
    int index = 0;
    int count = length * width;
    // 生成地图
    int arr_length = length * 2 + 1;
    int arr_width = width * 2 + 1;
    char **p = (char **) malloc(arr_length * sizeof(char *));
    int ram_size = arr_width * sizeof(char) * 2;
    for(int i = 0; i < arr_length; i ++){
        p[i] = (char *) malloc(ram_size);
    }
    for(int i = 0; i < arr_length; i ++){
        for(int j = 0;j < arr_width; j ++){
            // printf("%p\n", &p[i][j]);
            p[i][j] = WALL;  // 使用 @ 来表示墙
        }
    }

    int dir[4] = {1, 1, 1, 1};
    // 0: 向上, 1: 向下, 2: 向左, 3: 向右
    int x = 1;  // 起始点x坐标, 上下为x
    int y = 1;  // 起始点y坐标, 左右为y
    int dir_num;                // 从当前位置可以到达的方向
    while(count){
        dir_num = 4;
        dir[0] = 1;
        dir[1] = 1;
        dir[2] = 1;
        dir[3] = 1;
        if(x == 1 || p[x - 2][y] == SPACE){
            // 在最上层或上方已被标记, 无法向上
            dir_num --;
            dir[0] = 0;
        }
        if(x == arr_length - 2 || p[x + 2][y] == SPACE){
            // 无法向下
            dir_num --;
            dir[1] = 0;
        }
        if(y == 1 || p[x][y - 2] == SPACE){
            // 无法向左
            dir_num --;
            dir[2] = 0;
        }
        if(y == arr_width - 2 || p[x][y + 2] == SPACE){
            // 无法向右
            dir_num --;
            dir[3] = 0;
        }
        // 获取最终方向
        int move_dir = -1;
        if(dir_num){
            int r = rand() % dir_num;
            for(int i = 0; i < 4; i ++){
                if(dir[i] && !r){
                    move_dir = i;
                    break;
                }else if(dir[i] && r){
                    r --;
                }
            }
        }
        if(move_dir == -1){
            // 无路可走, 弹栈
            pop(stack, index);
            index --;
            x = stack[index][0];
            y = stack[index][1];
        }else if(move_dir >= 2){
            // 左右移动
            if(move_dir == 2){
                y -= 2;
                p[x][y + 1] = SPACE;
            }else{
                y += 2;
                p[x][y - 1] = SPACE;
            }
            index ++;
            count --;
        }else{
            // 上下移动
            if(move_dir){
                x += 2;
                p[x - 1][y] = SPACE;
            }else{
                x -= 2;
                p[x + 1][y] = SPACE;
            }
            index ++;
            count --;
        }
        push(stack, x, y, index);
        p[x][y] = SPACE;
    }
    p[1][0] = SPACE;
    p[arr_length - 2][arr_width - 1] = SPACE;
    return p;
}

int **createStack(int size){
    int **arr =  (int **)malloc(size * sizeof(int *));
    for(int i = 0; i < size; i ++){
        arr[i] = (int *) malloc(2 * sizeof(int));
    }
    return arr;
}

int playerMove(char **maze, int *player){
    /*
     * 获取键盘事件, 得到玩家的运动方向
     * */
    char input = getch();
    switch (input) {
        case UP:
            if(maze[player[0] - 1][player[1]] == WALL){
                // printf("e\n");
                return -1;
            }
            maze[player[0]][player[1]] = SPACE;
            player[0] --;
            maze[player[0]][player[1]] = PLAYER;
            return 0;
        case DOWN:
            if(maze[player[0] + 1][player[1]] == WALL){
                // printf("e\n");
                return -1;
            }
            maze[player[0]][player[1]] = SPACE;
            player[0] ++;
            maze[player[0]][player[1]] = PLAYER;
            return 1;
        case LEFT:
            if(player[1] == 0 || maze[player[0]][player[1] - 1] == WALL){
                // printf("e\n");
                return -1;
            }
            maze[player[0]][player[1]] = SPACE;
            player[1] --;
            maze[player[0]][player[1]] = PLAYER;
            return 2;
        case RIGHT:
            if(maze[player[0]][player[1] + 1] == WALL){
                // printf("e\n");
                return -1;
            }
            maze[player[0]][player[1]] = SPACE;
            player[1] ++;
            maze[player[0]][player[1]] = PLAYER;
            return 3;
        default:
            return -1;
    }
}

void printMaze(char **maze, int length, int width){
    for(int i = 0; i < length * 2 + 1; i ++){
        for(int j = 0; j < width * 2 + 1; j ++){
            printf("%c", maze[i][j]);
        }
        printf("\n");
    }
}

int maze(){
    int length = 8;
    int width = 8;
    char **maze = createMaze(length, width);
    int player[2] = {1, 0};
    maze[player[0]][player[1]] = PLAYER;
    int ret;
    printMaze(maze, length, width);
    while(1){
        ret = playerMove(maze, player);
        system("cls");
        printMaze(maze, length, width);
        if((player[0] == length * 2  - 1) && (player[1] == width * 2)){
            printf("success !!!!\n");
            printf("pls press \'e\' to exit \'a\' to play again\n");
            char c = 0;
            scanf("%c", &c);
            if(c == 'e'){
                return 0;
            }else if(c == 'a'){
                return 1;
            }
        }
        if(ret == -1){
            continue;
        }
    }
}

int main(){
    while(maze());
    return 0;
}
