#include "../headers/alpha_beta_pruning.h"

const int statements[PATTERN_NUM] = {
        //500000,      // 五连
        //500000,
        //500000,
        //500000,
        200000,      // 活四
        70000,       // 连三
        50000,
        50000,       // 冲四
        5500,        // 死四
        22500,        // 跳三
        22500,        // 跳三
        8000,        // 眠三
        8000,        // 眠三
        1000,        // 死三
        1000,        // 连二
        720,        // 跳二
        600,        // 大跳二
        500,        // 眠二
        500,        // 眠二
        300,        // 死二
        1,
        1,
};

const char patterns[PATTERN_NUM][PATTERN_SIZE] = {
        // # 表示同色棋子, @ 表示不可下棋处, $ 表示可下棋处, ! 表示暂未完成, % 表示边界
        //"@#####$",
        //"@#####@",
        //"$#####@",
        //"$#####$",
        "$####$",
        "$###$",
        "@####$",
        "$####@",
        "@####@",
        "$##$#$",
        "$#$##$",
        "@###$",
        "$###@",
        "@###@",
        "$##$",
        "$#$#$",
        "$#$$#$",
        "@##$",
        "$##@",
        "@##@",
        "$#@",
        "@#$",
};

int best_pos[2] = {-1, -1};

int get_score(Gobang *gobang, int x, int y);

int find_patten(char *str){
    /*
     * 从给出的11位长的模式串中找到符合的模式串
     */
    for(int i = 0; i < PATTERN_NUM; i ++){
        if(NULL != strstr(str, patterns[i])){
            return i;
        }
    }
    return -1;
}

void reset_piece_state(){
    for(int i = 0; i < BOARD_SIZE; i ++){
        for(int j = 0; j < BOARD_SIZE; j ++){
            memset(piece_state[i][j], 0, sizeof(int) * 4);
        }
    }
}

void init_score(Gobang *gobang) {
    /*if(is_init){
        return;
    }*/
    int i, x, y;
    for(i = 0; i < gobang->steps->sp; i ++){
        x = gobang->steps->stack[i][1];
        y = gobang->steps->stack[i][2];
        piece_score[x][y] = get_score(gobang, x, y);
    }
    is_init = 1;
}

void node_sort(Gobang *gobang){
    // 启发式搜索函数, 对于所有待搜索节点进行排序, 便于α-β剪枝

}

void update_score(Gobang *gobang) {
    // 更新棋盘分数可能变化的子的分数
    int i;
    int* prev_pos = gobang->steps->get_last_element(gobang->steps);
    int p_x = prev_pos[1], p_y = prev_pos[2], is_in_bound, dir = 1;

    // 仅更新分数可能更改的棋子的分数
    piece_score[prev_pos[1]][prev_pos[2]] = get_score(gobang, prev_pos[1], prev_pos[2]);

    for(i = 0; i < DIR_NUM; i ++) {
        // 遍历八个方向
        int count;    // 起始遍历点
        // 开始遍历
        for (;; dir *= -1) {
            count = 1;
            while (count <= 5) {
                // 得到下一个位置的坐标
                p_x += dir * direction[i][0];
                p_y += dir * direction[i][1];

                // 判断是否在棋盘内
                is_in_bound = p_x < BOARD_SIZE && p_y < BOARD_SIZE && p_x >= 0 && p_y >= 0;

                // 判断棋盘该位置的状态
                if (!is_in_bound) {
                    // 超出边界
                    break;
                }

                if (gobang->chessboard[p_x][p_y] == PLAYER_WHITE) {
                    // 有棋子位置
                    piece_score[p_x][p_y] = get_score(gobang, p_x, p_y);
                    count++;
                } else if(gobang->chessboard[p_x][p_y] == PLAYER_BLACK){
                    // 异色子， 判分后退出该轮
                    piece_score[p_x][p_y] = get_score(gobang, p_x, p_y);
                    break;
                } else if (gobang->chessboard[p_x][p_y] == 0){
                    // 没有子
                    count++;
                }
            }

            // 重置
            p_x = prev_pos[1];
            p_y = prev_pos[2];

            if (dir == -1) {
                // 反方向遍历完成, 退出循环
                dir = 1;
                break;
            }
        }
    }
}

int get_score(Gobang *gobang, const int x, const int y){
    if(gobang->chessboard[x][y] == 0){
        return 0;
    }
    int i;
    char pattern[PATTERN_SIZE] = {0}; // 位于x, y坐标的棋子的字符串模式
    PIECE piece = gobang->chessboard[x][y];
    int score = 0;
    int is_in_bound, space_count;
    int p_x = x, p_y = y, dir = 1;

    for(i = 0; i < DIR_NUM; i ++){
        // 遍历八个方向
        if(piece_state[x][y][i]){
            // 该棋子当前方向已经遍历
            continue;
        }
        // 初始化
        int mid = 5, count;    // 起始遍历点
        memset(pattern, 0, sizeof(pattern));
        pattern[5] = '#';
        // 开始遍历
        for(;;dir *= -1){
            count = 1;
            space_count = 2;   // 运行一个方向上有两个空格
            while(count <= 5){
                // 得到下一个位置的坐标
                p_x += dir * direction[i][0];
                p_y += dir * direction[i][1];

                // 判断是否在棋盘内
                is_in_bound = p_x < BOARD_SIZE && p_y < BOARD_SIZE && p_x >= 0 && p_y >= 0;

                // 判断棋盘该位置的状态
                if(!is_in_bound){
                    // 超出边界
                    if(pattern[mid + dir * (count - 1)] != '$' && pattern[mid + dir * (count - 1)] != '\0'){
                        // 上一个非空， 不会出现 ##$@之类的情况
                        pattern[mid + dir * count] = '@';
                    }
                    break;
                }

                if(gobang->chessboard[p_x][p_y] == -piece){
                    // 是异色棋
                    if(pattern[mid + dir * (count - 1)] != '$' && pattern[mid + dir * (count - 1)] != '\0'){
                        // 上一个非空， 不会出现 ##$@之类的情况
                        pattern[mid + dir * count] = '@';
                    }
                    break;
                } else if (gobang->chessboard[p_x][p_y] == piece){
                    // 同色棋
                    pattern[mid + dir * count] = '#';
                    piece_state[p_x][p_y][i] = 1;
                    // 暂时不优化对于接近棋盘边界的算法
                } else if (gobang->chessboard[p_x][p_y] == 0){
                    // 可下棋位置
                    if(space_count > 0){
                        pattern[mid + dir * count] = '$';
                        space_count --;
                    }
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

        // 单直线遍历完成, 开始匹配
        int start_index = 0;    // 匹配开始的下标
        int suc_index = -1; // 成功匹配的下标, -1则表示没有匹配到

        int left = 0, right = PATTERN_SIZE - 1;
        // 去除左侧多余的 \0 和 $
        for(; left < PATTERN_SIZE; left ++){
            if(pattern[left] == '\0'){
                left++;
            } else {
                break;
            }
        }
        suc_index = find_patten(pattern + left);
        if(suc_index != -1){
            score += statements[suc_index];
            if((suc_index == 16 || suc_index == 17) && piece == PLAYER_WHITE){
                score++;
            }
        }
        if(is_win(gobang)){
            score += 1000000;
        }
    }
    return score * piece;   // 对于电脑玩家, 落子时 player = 1 (白子), 此时白子的分为正分
}

long long evaluate(Gobang *gobang){
    /*
     * 评估棋盘局势
     */
    // 如果必赢, 也可以直接算分, 只需要对于自己必赢选择最短路径, 对于对方必赢选择最长路径即可
    // 或许?
    reset_piece_state();    // 重置状态
    int x, y, i;
    long long  chessboard_score = 0;
    for(i = 0; i < gobang->steps->sp; i ++){
        x = gobang->steps->stack[i][1];
        y = gobang->steps->stack[i][2];
        chessboard_score += piece_score[x][y];
    }
    return chessboard_score;
}

long long search(Gobang *gobang, int depth, long long alpha, long long beta, PIECE cur_player){
    /*
     * 搜索算法, 返回一个分数(暂时不优化)
     */
    if(depth == 0 || gobang->pos_steps_num == 0 || is_win(gobang)){
        // 遍历到底层, 开始算分
        return evaluate(gobang);
    }

    // 搜索
    /*
     * 每种状态的棋盘看看作一个结点
     *
     * 对于一个棋盘状态
     * 其含有属性: 分数, 通过evaluate方法评估棋局局势得出
     * 显然得到分数时该棋盘状态已经被遍历得到
     */

    long long score;

    if(cur_player == PLAYER_WHITE){
        // max 层
        for(int i = 0; i < BOARD_SIZE; i ++){
            for(int j = 0; j < BOARD_SIZE; j ++){
                if(gobang->pos_steps[i][j] == 0){
                    continue;
                }
                /*for(int k = MAX_DEPTH - depth; k > 0; k --){
                    fprintf(file, "\t");
                }
                fprintf(file,"WHITE fall (%d, %d) depth: %d\n",i, j, depth);*/
                fall(gobang, i, j); // 下棋
                update_score(gobang);
                score = search(gobang, depth - 1, alpha, beta, -cur_player);
                if(score > alpha){
                    alpha = score;
                    if (depth == MAX_DEPTH){
                        best_pos[1] = j;
                        best_pos[0] = i;
                    }
                    white_pos[0] = i;
                    white_pos[1] = j;
                }
                /*for(int k = MAX_DEPTH - depth; k > 0; k --){
                    fprintf(file, "\t");
                }
                fprintf(file,"score: %lld\n", score);
                for(int k = MAX_DEPTH - depth; k > 0; k --){
                    fprintf(file, "\t");
                }
                fprintf(file,"[DEBUG] depth: %d, score: %lld in (%d, %d)\n\n", depth, alpha, black_pos[0], black_pos[1]);*/
                remove_piece(gobang, i, j);
                update_score(gobang);
                if(alpha >= beta){
                    return alpha;
                }
            }
        }
        return alpha;

    } else {
        // min 层
        int f = 0;
        for(int i = 0; i < BOARD_SIZE; i ++){
            for(int j = 0; j < BOARD_SIZE; j ++){
                if(gobang->pos_steps[i][j] == 0){
                    continue;
                }
                /*for(int k = MAX_DEPTH - depth; k > 0; k --){
                fprintf(file, "\t");
                }
                fprintf(file,"BLACK fall (%d, %d) depth: %d\n",i, j, depth);*/
                fall(gobang, i, j); // 下棋
                update_score(gobang);
                score =  search(gobang, depth - 1, alpha, beta, -cur_player);
                if(score < beta){
                    beta = score;
                    black_pos[0] = i;
                    black_pos[1] = j;
                }
                remove_piece(gobang, i, j);
                update_score(gobang);
                /*for(int k = MAX_DEPTH - depth; k > 0; k --){
                fprintf(file, "\t");
                }
                fprintf(file,"score: %lld\n", score);
                for(int k = MAX_DEPTH - depth; k > 0; k --){
                fprintf(file, "\t");
                }
                fprintf(file, "[DEBUG] depth: %d, score: %lld in (%d, %d)\n", depth, beta, white_pos[0], white_pos[1]);*/
                if(alpha >= beta){
                    return beta;
                }
            }
        }
        return beta;
    }
}

long long first_search(Gobang *gobang, int depth, long long alpha, long long beta, PIECE cur_player){
    /*
     * 搜索算法, 返回一个分数(暂时不优化)
     */
    if(depth == 0 || gobang->pos_steps_num == 0){
        // 遍历到底层, 开始算分
        return evaluate(gobang);
    }

    // 搜索
    /*
     * 每种状态的棋盘看看作一个结点
     *
     * 对于一个棋盘状态
     * 其含有属性: 分数, 通过evaluate方法评估棋局局势得出
     * 显然得到分数时该棋盘状态已经被遍历得到
     */

    long long score;

    if(cur_player == PLAYER_WHITE){
        // max 层
        for(int count = 8; count >= 0; count ++){
            /*for(){

            }*/
        }
        return alpha;

    } else {
        // min 层
        for(int i = 0; i < BOARD_SIZE; i ++){
            for(int j = 0; j < BOARD_SIZE; j ++){
                if(gobang->pos_steps[i][j] == 0){
                    continue;
                }

                // printf("BLACK fall (%d, %d) depth: %d\t",i, j, depth);

                fall(gobang, i, j); // 下棋
                update_score(gobang);
                score =  search(gobang, depth - 1, alpha, beta, -cur_player);
                if(score < beta){
                    beta = score;
                }
                remove_piece(gobang, i, j);
                update_score(gobang);
                // printf("score: %lld\n", score);
                /*if(depth == MAX_DEPTH - 1){
                    printf("[DEBUG] depth: %d, score: %lld in (%d, %d)\n", depth, beta, i, j);
                }*/
                if(alpha >= beta){
                    return beta;
                }
            }
        }
        return beta;
    }
}
