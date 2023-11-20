#include "../headers/gobang.h"
void generate_steps(Gobang *gobang, int x, int y);

const int direction[DIR_NUM][2] = {
        {1, 0}, // 下
        {0, 1}, // 右
        {1, 1}, // 右下
        {-1, 1} // 右上
};  // 遍历方向时使用的方向常量

Gobang *create_gobang(){
    Gobang *gobang = (Gobang *)malloc(sizeof(Gobang));
    memset(gobang, 0, sizeof(Gobang));
    gobang->chessboard = (int **) malloc(sizeof(int *) * BOARD_SIZE);
    for(int i = 0; i < BOARD_SIZE; i ++){
        gobang->chessboard[i] = (int *) malloc(sizeof(int) * BOARD_SIZE);
        memset(gobang->chessboard[i], 0, sizeof(int) * BOARD_SIZE);
    }
    gobang->pos_steps = (int **) malloc(sizeof(int *) * BOARD_SIZE);
    for(int i = 0; i < BOARD_SIZE; i ++){
        gobang->pos_steps[i] = (int *) malloc(sizeof(int) * BOARD_SIZE);
        memset(gobang->pos_steps[i], 0, sizeof(int) * BOARD_SIZE);
    }
    gobang->pos_steps_num = 0;
    gobang->now_player = PLAYER_BLACK;
    gobang->steps = create_stack(BOARD_SIZE * BOARD_SIZE);
    return gobang;
}

int is_win(Gobang *gobang){
    /*
     * 返回获胜的玩家的棋子, 如果没人获胜, 则返回0
     */
    // int prev_x, prev_y;
    if(gobang->steps->sp < 9){
        return 0;
    }
    PIECE piece;

    int *prev = gobang->steps->get_last_element(gobang->steps);

    if(gobang->now_player == PLAYER_WHITE){
        // 现在到白棋, 则上一步是黑棋下的, 检验黑棋
        /*prev_x = gobang->prevOperate[0][0];
        prev_y = gobang->prevOperate[0][1];*/
        piece = PLAYER_BLACK;
    } else {
        // 反之白棋
        /*prev_x = gobang->prevOperate[1][0];
        prev_y = gobang->prevOperate[1][1];*/
        piece = PLAYER_WHITE;
    }
    int count;
    int is_in_bound;
    int x = prev[1], y = prev[2], dir = 1;
    for(int i = 0; i < DIR_NUM; i ++){
        count = 1;
        for(;;dir *= -1){
            x += dir * direction[i][0];
            y += dir * direction[i][1];
            is_in_bound = x < BOARD_SIZE && y < BOARD_SIZE && x >= 0 && y >= 0;
            while(is_in_bound && gobang->chessboard[x][y] == piece){
                // 如果颜色相同, 则棋子加一
                x += dir * direction[i][0];
                y += dir * direction[i][1];
                count++;
                is_in_bound = x < BOARD_SIZE && y < BOARD_SIZE && x >= 0 && y >= 0;
            }
            x = prev[1];
            y = prev[2];
            if(dir == -1){
                // 反方向遍历完成, 退出循环
                dir = 1;
                break;
            }
        }
        if(count >= 5){
            // 达到获胜条件, 返回获胜棋子
            return piece;
        }
    }
    return 0;   // 没有一方棋子获胜, 返回0
}

int fall(Gobang *gobang, int x, int y){
    /*
     * 通过坐标落子
     */
    if(!(x < BOARD_SIZE && y < BOARD_SIZE && x >= 0 && y >= 0)){
        return -100;  // 超出边界, 落子失败
    } else if(gobang->chessboard[x][y] != 0){
        return -101;  // 已有子, 落子失败
    }

    PIECE piece = gobang->now_player;

    // 落子
    gobang->chessboard[x][y] = piece;   // 落子, 用 2 来表示最近的操作

    // 添加步骤
    gobang->steps->append(gobang->steps, piece, x, y);

    // 生成可能落子点
    generate_steps(gobang, x, y);

    // 将原本的上一步修改为之前步 (暂时舍弃)
    /*int *prev = gobang->steps->get_last_element(gobang->steps);

    int prev_x = prev[1], prev_y = prev[2];
    int index = piece == PLAYER_WHITE ? 1 : 0; // 如果是白子, 则下标为1, 如果是黑子, 下标为0
    prev_x = gobang->prevOperate[index][0];
    prev_y = gobang->prevOperate[index][1];*/
    /*if(prev_x != -1 && prev_y != -1){
        // 存在上一步, 为-1时表示没有上一步
        // gobang->chessboard[prev_x][prev_y] = piece; // 用 1 来表示之前的操作
    }*/
    // 更新上一步棋
    /*gobang->prevOperate[index][0] = x;
    gobang->prevOperate[index][1] = y;*/

    // 交换玩家
    gobang->now_player *= -1;   // 因为定义方式, * (-1)即可交换棋手

    return piece;   // 下了什么棋, 返回什么棋
}

void print_chessboard_in_stdin(Gobang *gobang){
    for(int i = 0; i < BOARD_SIZE; i ++){
        for(int j = 0; j < BOARD_SIZE; j ++){
            printf("%+d ", gobang->chessboard[i][j]);
        }
        putchar('\n');
    }
}

void print_pos_steps_in_stdin(Gobang *gobang){
    for(int i = 0; i < BOARD_SIZE; i ++){
        for(int j = 0; j < BOARD_SIZE; j ++){
            printf("%+d ", gobang->pos_steps[i][j]);
        }
        putchar('\n');
    }
}

void generate_steps(Gobang *gobang, int x, int y){
    /*
     * 为当前角色生成可能的落子点, 在落子时生成
     * 生成策略: 距离已落子点曼哈顿距离小于等于2的所有点
     */
    int dir = 1;    // 正反方向
    int p_x = x, p_y = y;
    int is_in_bound, count;
    for(int i = 0; i < DIR_NUM; i ++){
        for(;;dir *= -1){
            count = 1;
            while(1){
                // 得到下一个位置的坐标
                p_x += dir * direction[i][0];
                p_y += dir * direction[i][1];

                // 判断是否在棋盘内
                is_in_bound = p_x < BOARD_SIZE && p_y < BOARD_SIZE && p_x >= 0 && p_y >= 0;

                // 判断棋盘该位置的状态
                if(!is_in_bound){
                    // 超出边界
                    break;
                }
                if(gobang->chessboard[p_x][p_y] == 0){
                    // 可以落子处
                    gobang->pos_steps_num ++;
                    gobang->pos_steps[p_x][p_y] ++;
                } else {
                    break;
                }

                // 到达最大长度
                if(count >= PRED_COUNT){
                    break;
                }

                count ++;
            }

            // 重置
            p_x = x;
            p_y = y;

            if(dir == -1){
                // 反方向遍历完成, 退出循环
                dir = 1;
                break;
            }
        }
    }
    // 遍历完成, 当前子位置无法落子
    gobang->pos_steps[x][y] = 0;
}

int remove_piece(Gobang *gobang, int x, int y){
    if(gobang->chessboard[x][y] == 0){
        printf("[ERROR] REMOVE_ERROR: there is no piece. x: %d, y %d\n", x, y);
        return -1;  // 没有子
    }

    int *step = gobang->steps->pop(gobang->steps);

    if(step[1] != x || step[2] != y){
        gobang->steps->append(gobang->steps, step[0], step[1], step[2]);
        return -2;  // 错误的撤销
    }

    // 移除棋子
    gobang->chessboard[x][y] = 0;

    // 交换玩家
    gobang->now_player *= -1;   // 因为定义方式, * (-1)即可交换棋手

    // 更新pos_steps, 显然更新之后周围都要受影响, 采用直接遍历周围棋子的方式更新
    int is_in_bound;
    for(int i = x - PRED_COUNT; i <= x + PRED_COUNT; i ++){
        for(int j = y - PRED_COUNT; j <= y + PRED_COUNT; j ++){
            is_in_bound = i < BOARD_SIZE && j < BOARD_SIZE && i >= 0 && j >= 0;
            if(is_in_bound){
                if(gobang->pos_steps[i][j] >= 1){
                    // 清空后重新填充
                    gobang->pos_steps_num --;
                    gobang->pos_steps[i][j] = 0;
                }
            }
        }
    }
    for(int i = x - PRED_COUNT; i <= x + PRED_COUNT; i ++){
        for(int j = y - PRED_COUNT; j <= y + PRED_COUNT; j ++){
            is_in_bound = i < BOARD_SIZE && j < BOARD_SIZE && i >= 0 && j >= 0;
            if(is_in_bound){
                if(gobang->chessboard[i][j] != 0){
                    generate_steps(gobang, i, j);
                }
            }
        }
    }

    return 1;
}

void print_debug_msg(Gobang *gobang){
    for(int i = 0; i < gobang->steps->sp; i ++){
        printf("fall(gobang, %d, %d);\n", gobang->steps->stack[i][1], gobang->steps->stack[i][2]);
    }
}