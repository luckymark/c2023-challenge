#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

char **createMaze(int length, int width){
    /*
     * 依据给定的长宽生成迷宫(二维数组)
     * 生成后
     * */
    //if(maze == NULL){
    //     return -1;
    //}
    int arr_length = length * 2 + 1;
    int arr_width = width * 2 + 1;
    char **p = (char **) malloc(arr_length * sizeof(char *));
    int ram_size = arr_width * sizeof(char);
    for(int i = 0; i < arr_length; i ++){
        p[i] = (char *) malloc(ram_size);
    }
    for(int i = 0; i < arr_length; i ++){
        for(int j = 0;j < arr_width; j ++){
            // printf("%p\n", &p[i][j]);
            p[i][j] = '@';
        }
    }
    p[arr_length - 2][0] = ' '; // 设置起点
    return p;
}

int getKeyboardEvent(){
    char input = getch();
    switch (input) {
        case 72:
            printf("up\n");
            break;
        case 80:
            printf("down\n");
            break;
        case 75:
            printf("left\n");
            break;
        case 77:
            printf("right\n");
            break;
        default:
            printf("other: %d\n", input);
            break;
    }
}
int main() {
    /*
     * 随机拆墙生成迷宫 + BFS验证可行性
     * 或者图算法生成迷宫, 生成出来即可行
     *
     * */
    int length = 11;
    int width = 17;
    char **maze = createMaze(length, width);
    for(int i = 0; i < length * 2 + 1; i ++){
        for(int j = 0;j < width * 2 + 1; j ++){
            printf("%c", maze[i][j]);
        }
        printf("\n");

    }
    return 0;
}