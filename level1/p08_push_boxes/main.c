#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define LENGTH 10
#define WIDTH 10
#define SPACE ' '
#define WALL '#'
#define BOD '^'
#define PLAYER 'P'

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
/*
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
*/
#define BOX 'B'
#define GOAL '$'
#define BOX_COUNT 5
#define GOAL_COUNT 5
#define ALL_LEVEL 5
#define RETRY 114
#define NEXT 110

int getKeyboardEvent();
void printMap();
void getMap();
int isWin();
int saveScore();
int getScore();

char map[LENGTH][WIDTH];
int player[2];
int boxes[BOX_COUNT][2];
int goal[GOAL_COUNT][2];
int level = 1;
int score[5] = {0, 0, 0, 0, 0};
int count = 0;
int n_score = 100;

int getScore(){
    char src[] = "D:\\class\\r\\c2023-challenge\\level1\\p08_push_boxes\\score.txt";
    char s[5] = "";
    FILE *fp = fopen(src, "r");
    for(int i = 0; i < ALL_LEVEL; i ++){
        score[i] = atoi(fgets(s, 10, fp));
    }
    fclose(fp);
    //for(int i = 0; i < 5; i ++){
    //    printf("%d\n", score[i]);
    //}
    return 0;
}

int reset(){
    system("cls");
    count = 0;
    n_score = 100;
    player[0] = 0;
    player[1] = 0;
    for(int i = 0;i < BOX_COUNT; i ++){
        boxes[i][0] = 0;
        boxes[i][1] = 0;
        goal[i][0] = 0;
        goal[i][1] = 0;
        getScore();
    }
    memset(map, 0, LENGTH * WIDTH * sizeof(char));
    return 0;
}

int getBox(int dx, int dy){
    for(int i = 0; i < BOX_COUNT; i ++){
        if(player[0] + dx == boxes[i][0] && player[1] + dy == boxes[i][1]){
            return i;
        }
    }
    return 0;
}

int saveScore(){
    char src[] = "D:\\class\\r\\c2023-challenge\\level1\\p08_push_boxes\\score.txt";
    FILE *fp = fopen(src, "w");
    for(int i = 0; i < 5; i ++){
        fprintf(fp, "%d\n", score[i]);
    }
    fclose(fp);
    return 0;
}

int moveCheck(int dx, int dy, int dir){
    char dir_player = map[player[0] + dx][player[1] + dy];
    if(dir_player == WALL){
        // printf("e\n");
        return -1;
    }else if(map[player[0] + dx][player[1] + dy] == BOX){
        int i = getBox(dx, dy);
        char dir_box = map[boxes[i][0] + dx][boxes[i][1] + dy];
        if(dir_box == WALL || dir_box == BOX){
            return -1;
        }else{
            map[boxes[i][0]][boxes[i][1]] = SPACE;
            boxes[i][0] += dx;
            boxes[i][1] += dy;
            // map[boxes[i][0]][boxes[i][1]] = BOX;
        }
    }
    n_score --;
    map[player[0]][player[1]] = SPACE;
    player[0] += dx;
    player[1] += dy;
    // map[player[0]][player[1]] = PLAYER;
    return dir;
}

int isWin(){
    int n = count;
    for(int i = 0; i < count; i ++){
        for(int j = 0; j < count; j ++){
            if(boxes[i][0] == goal[j][0] && boxes[i][1] == goal[j][1]){
                n --;
            }
        }
    }
    // printf("%d", count);
    return !n;
}

int getKeyboardEvent(){
    /*
     * 获取键盘事件, 得到玩家的运动方向
     * */
    int input = getch();
    // int none = getch();
    switch (input) {
        case 224:
            break;
        case UP:
            return moveCheck(-1, 0, 0);
        case DOWN:
            return moveCheck(1, 0, 1);
        case LEFT:
            return moveCheck(0, -1, 2);
        case RIGHT:
            return moveCheck(0, 1, 3);
        case RETRY:
            return -2;
        //case NEXT:
        //    return -3;
        default:
            return -1;
    }
    return -1;
}

void getMap(){
    count = 0;
    FILE *fp = NULL;
    // memset(p, '\0',7 ram_size * MAX_LEN);
    char src[] = "D:\\class\\r\\c2023-challenge\\level1\\p08_push_boxes\\pushBox1.txt";
    src[56] = (char)(48 + level);
    //char src[] = ".\\pushBox1.txt";
    //src[9] = (char)(48 + level);
    // printf("%s", src);
    fp = fopen(src, "r");
    int box_count = 0;
    int goal_count = 0;
    for(int i = 0; i < 10;i ++)
    {
        for(int j = 0; j < 10;)
        {
            char r = '\0';
            fscanf(fp, "%c", &r);       //读入字符
            if(r == '\n'){
                // printf("\n");
                continue;
            }else if(r == EOF){
                return;
            }else if(r == PLAYER){
                player[0] = i;
                player[1] = j;
            }else if(r == BOX){
                boxes[box_count][0] = i;
                boxes[box_count][1] = j;
                box_count ++;
                count ++;
            }else if(r == GOAL){
                goal[goal_count][0] = i;
                goal[goal_count][1] = j;
                goal_count ++;
            }else if(r == BOD){
                r = ' ';
            }
            map[i][j] = r;
            // printf("%c", p[i][j]);
            j ++;
        }
    }
    fclose(fp);
}

void printMap(){
    printf("P is Player\nB is box\n$ is goal\npress \'r\' to try again\n");
    printf("level: %d\n", level);
    printf("score: %d\n", n_score);
    printf("the best score in this level is %d\n", score[level - 1]);
    for(int i = 0; i < count; i ++){
        map[goal[i][0]][goal[i][1]] = GOAL;
    }
    for(int i = 0; i < count; i ++){
        map[boxes[i][0]][boxes[i][1]] = BOX;
    }
    map[player[0]][player[1]] = PLAYER;
    for(int i = 0; i < LENGTH; i ++){
        for(int j = 0; j < WIDTH; j ++){
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
    /*
    for(int i = 0; i < BOX_COUNT; i ++){
        printf("box %d: x: %d, y: %d\n", i, boxes[i][0], boxes[i][1]);
    }
     */
}

int win(){
    if(n_score > score[level - 1]){
        score[level - 1] = n_score;
        saveScore();
    }
    fflush(stdin);
    printf("success !!!!\n");
    printf("pls press \'e\' to exit \'c\' to continue\n");
    char c = 0;
    scanf("%c", &c);
    if(c == 'e'){
        return 0;
    }else if(c == 'c'){
        if(ALL_LEVEL == level){
            printf("u wins!!! Press Any Key to exit");
            getchar();
            return 0;
        }
        level ++;
        return 1;
    }
    return 0;
}

int pushBox(){
    reset();
    getMap();
    printMap();
    // getKeyboardEvent();
    //getScore();
    int ret;
    while(1){
        ret = getKeyboardEvent();
        if(ret == -2){
            reset();
            getMap();
            return 1;
        }
        system("cls");
        printMap();
        if(isWin()){
            return win();
        }
    }
}

int main() {
    /*
     * Clion 工作区没在当前目录, 我直接用绝对路径了
     * */
    // set buf(stdout, 0);
    while(pushBox());
    // getScore();
    return 0;
}