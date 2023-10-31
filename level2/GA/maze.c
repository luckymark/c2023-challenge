#include "maze.h"


// gui表现
const char SPACE = ' ';
const char WALL = '#';
const char PLAYER = '@';

// 操作
/*const char UP = 72;
const char DOWN = 80;
const char LEFT = 75;
const char RIGHT = 77;*/

// 值, 16 * 16的迷宫
const int WID = 16;
const int LEN = 16;

const int MOVE_MODE[4][2] = {
        // 第一位表示上下, 第二位表示左右
        {-1, 0},     // 向上
        {1, 0},     // 向下
        {0, -1},     // 向左
        {0, 1}      // 向右
};

int player_move(Maze *maze, int mode);
void reset(Maze *maze);
int get_access_num(Maze *maze);

Maze *create_maze(int length, int width){
    if(length > LEN || width > WID){
        printf("长/宽度过大");
        return NULL;
    }
    Maze *maze = (Maze *)malloc(sizeof(Maze));
    maze -> length = length;
    maze -> width = width;
    srand(0);   // 去除随机
    // 创建栈
    Stack *stack = create_stack(length * width);

    // 记录未遍历位置
    int count = length * width;

    // 创建迷宫数组
    int arr_length = length * 2 + 1;
    int arr_width = width * 2 + 1;
    char ** map = (char **) malloc(arr_length * sizeof(char *));
    int ram_size = arr_width * (int)sizeof(char) * 2;
    for(int i = 0; i < arr_length; i ++){
        map[i] = (char *) malloc(ram_size);
    }

    // 初始化为墙
    for(int i = 0; i < arr_length; i ++){
        for(int j = 0; j < arr_width; j ++){
            map[i][j] = WALL;  // 使用 @ 来表示墙
        }
    }

    // 回溯算法生成迷宫

    int dir[4] = {1, 1, 1, 1};
    // 0: 向上, 1: 向下, 2: 向左, 3: 向右

    int location[2] = {1, 1};   // 起始点坐标, 下标0表示上下, 下标1表示左右

    int dir_num;    // 从当前位置可以到达的方向

    while(count) {
        // 初始化
        dir_num = 4;
        dir[0] = 1;
        dir[1] = 1;
        dir[2] = 1;
        dir[3] = 1;
        int x = location[0];
        int y = location[1];

        if(x == 1 || map[x - 2][y] == SPACE){
            // 在最上层或上方已被标记, 无法向上
            dir_num --;
            dir[0] = 0;
        }
        if(x == arr_length - 2 || map[x + 2][y] == SPACE){
            // 无法向下
            dir_num --;
            dir[1] = 0;
        }
        if(y == 1 || map[x][y - 2] == SPACE){
            // 无法向左
            dir_num --;
            dir[2] = 0;
        }
        if(y == arr_width - 2 || map[x][y + 2] == SPACE){
            // 无法向右
            dir_num --;
            dir[3] = 0;
        }

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
            int * loc = stack -> pop(stack);
            location[0] = loc[0];
            location[1] = loc[1];
            continue;
        }else if(move_dir >= 2){
            // 左右移动
            if(move_dir == 2){
                y -= 2;
                map[x][y + 1] = SPACE;
            }else{
                y += 2;
                map[x][y - 1] = SPACE;
            }
            count --;
        }else{
            // 上下移动
            if(move_dir){
                x += 2;
                map[x - 1][y] = SPACE;
            }else{
                x -= 2;
                map[x + 1][y] = SPACE;
            }
            count --;
        }
        location[0] = x;
        location[1] = y;
        stack -> append(stack, location);
        map[x][y] = SPACE;
    }

    map[1][0] = SPACE;
    map[arr_length - 2][arr_width - 1] = SPACE;
    maze -> maze = map;
    maze -> player_move = player_move;
    maze -> player = (int *)malloc(sizeof(int) * 2);
    maze -> player[0] = 1;
    maze -> player[1] = 0;
    maze -> maze[maze -> player[0]][maze -> player[1]] = PLAYER;
    maze -> destination = (int *) malloc(sizeof(int) * 2);
    maze -> destination[0] = length * 2 - 1;
    maze -> destination[1] = width * 2;
    maze -> reset = reset;
    maze -> get_access_num = get_access_num;
    return maze;
}

void print_maze(Maze *maze){
    int length = maze -> length;
    int width = maze -> width;
    for(int i = 0; i < length * 2 + 1; i ++){
        for(int j = 0; j < width * 2 + 1; j ++){
            putchar(maze -> maze[i][j]);
        }
        putchar('\n');
    }
}

int player_move(Maze *maze, int mode){
    /*
     * 返回0, 成功移动, 返回-1, 移动失败
     */
    int dx = MOVE_MODE[mode][0];
    int dy = MOVE_MODE[mode][1];
    int *player = maze -> player;
    if(player[1] + dy == -1 || player[1] + dy == maze->width * 2 + 1){
        return -1;
    }
    /*if(player[0] == 30 || player[0] <= 0 || player[0] == 0 || player[1] < 0){
        printf("\n?????\n");
        printf("x : %d\n", player[0]);
        printf("y : %d\n", player[1]);
        print_maze(maze);
        int j = 0;
    }*/

    char to_location = maze->maze[player[0] + dx][player[1] + dy];

    if(to_location == WALL){
        return -1;  // 无法移动
    }
    maze -> maze[maze -> player[0]][maze -> player[1]] = SPACE;
    player[0] += dx;
    player[1] += dy;
    maze -> maze[maze -> player[0]][maze -> player[1]] = PLAYER;
    if(player[0] == maze -> destination[0] && player[1] == maze -> destination[1]){
        return 1;
        // 到达终点
    }
    return 0;   // 成功移动
}

void reset(Maze *maze){
    maze -> maze[maze -> player[0]][maze -> player[1]] = SPACE;
    maze -> player[0] = 1;
    maze -> player[1] = 0;
    maze -> maze[maze -> player[0]][maze -> player[1]] = PLAYER;
}

int get_access_num(Maze *maze){
    int x = maze->player[0];
    int y = maze->player[1];
    int res = 0;
    for(int i = 0; i < 4; i ++){
        int dx = MOVE_MODE[i][0];
        int dy = MOVE_MODE[i][1];
        if(y + dy < 0){
            // 左为墙
            res += 2;
            continue;
        } else if (y + dy >  maze->width * 2){
            // 右为墙
            res += 1;
            continue;
        }
        if(maze->maze[x + dx][y + dy] == WALL){
            res += 8 >> i;
        }
    }
    return res;
}