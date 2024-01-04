#include "../headers/alpha_beta_pruning.h"

Stack *inf_pieces = NULL;
int **src_statement = NULL;

const int statements[PATTERN_NUM] = {
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
        0,
        0,
};

const char patterns[PATTERN_NUM][PATTERN_SIZE] = {
        // # 表示同色棋子, @ 表示不可下棋处, $ 表示可下棋处
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
void generate_pred(Gobang *gobang, int depth);
void sub_generate_pred(int** src, int x, int y, int depth);
void heuristically_search(Gobang *gobang);

void heuristically_search(Gobang *gobang){
    /*
     * 启发式搜素
     */
    int max_same_piece_num;
    int dir = 1, count, is_in_bound;
    int p_x, p_y, piece;
    int match[4][2] = {
            {1, 1},
            {-1, 1},
            {1, -1},
            {-1, -1}
    };
    int dir_score[2];   // 某条线上的连子数， 0为白棋的连子数，1为黑棋的连子数
    int index[6] = {0, 0, 0, 0, 0, 0};
    for(int x = 0; x < BOARD_SIZE; x ++){
        for(int y = 0; y < BOARD_SIZE; y ++){
            if(gobang->pos_steps_num <= 0 || gobang->pos_steps[x][y] == 0){
                continue;
            }
            // 遍历所有的待考虑的落子点
            max_same_piece_num = 1;
            for(int i = 0; i < DIR_NUM; i ++){
                dir_score[0] = 0;
                dir_score[1] = 0;
                for(int j = 0; j < 4; j ++){
                    // 遍历(x, y)的一个方向
                    count = 1;
                    p_x = x;
                    p_y = y;
                    dir = match[j][0];
                    piece = match[j][1];
                    int space = 0;
                    while (count < 5){
                        p_x += dir * direction[i][0];
                        p_y += dir * direction[i][1];
                        is_in_bound = p_x < BOARD_SIZE && p_y < BOARD_SIZE && p_x >= 0 && p_y >= 0;
                        if (!is_in_bound) {
                            // 超了
                            break;
                        }
                        if(piece == gobang->chessboard[p_x][p_y]){
                            // 相同子
                            dir_score[j / 2] ++;
                        } else if (0 == gobang->chessboard[p_x][p_y]){
                            // 允许一个空格
                            if(space == 0) {
                                space = 1;
                            } else {
                                break;
                                // 有多于2个的空格
                            }
                        } else if (piece == -gobang->chessboard[p_x][p_y]){
                            // 异色子
                            break;
                        }
                        count++;
                    }
                    int t = dir_score[0] > dir_score[1] ? dir_score[0] : dir_score[1]; // 选取能连的最长的
                    max_same_piece_num = t > max_same_piece_num ? t : max_same_piece_num;
                    if (max_same_piece_num > 5) {
                        max_same_piece_num = 5;
                    }
                }
            }
            heu_locations[max_same_piece_num][index[max_same_piece_num]][0] = x;
            heu_locations[max_same_piece_num][index[max_same_piece_num]][1] = y;
            heu_locations[max_same_piece_num][index[max_same_piece_num] + 1][0] = -1;
            index[max_same_piece_num] ++;
            // 更新位置, 并标记结束位置
        }
    }
}


void sub_generate_pred(int** src, int x, int y, int depth){
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
                if(src[p_x][p_y] == 0){
                    // 可以落子处
                    pos_num[depth] ++;
                    pred_chessboard[depth][p_x][p_y] ++;
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
    pred_chessboard[depth][x][y] = 0;
}

void generate_pred(Gobang *gobang, int depth){
    /*
     * 更新 depth 层所用来考虑下子的位置, 依据depth + 1层
     */
    if (depth == MAX_DEPTH) {
        for(int i = 0; i < BOARD_SIZE; i ++){
            for (int j = 0; j < BOARD_SIZE; j ++) {
                src_statement[i][j] = gobang->chessboard[i][j];
            }
        }
    } else {
        for(int i = 0; i < BOARD_SIZE; i ++){
            for (int j = 0; j < BOARD_SIZE; j ++) {
                src_statement[i][j] =pred_chessboard[depth + 1][i][j];
            }
        }
    }
    for (int i = 0; i < BOARD_SIZE; i ++) {
        for (int j = 0; j < BOARD_SIZE; j ++) {
            sub_generate_pred(src_statement, i, j, depth);
        }
    }
}

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



void init_score(Gobang *gobang) {
    int i, x, y;
    for(i = 0; i < gobang->steps->sp; i ++){
        x = gobang->steps->stack[i][1];
        y = gobang->steps->stack[i][2];
        piece_score[x][y] = get_score(gobang, x, y);
    }
}

void quick_sort(int left, int right){
    /*
     * 对nodes进行排序, 从大到小, index 后的不排序
     */
    int base = nodes[MAX_DEPTH][left][0];
    int base_x = nodes[MAX_DEPTH][left][1];
    int base_y = nodes[MAX_DEPTH][left][2];
    if(left > right){
        return;
    }
    int l = left;
    int r = right;
    int temp[3];
    while(l != r){
        while (nodes[MAX_DEPTH][r][0] <= base && l < r){
            r --;
        }
        while (nodes[MAX_DEPTH][l][0] >= base && l < r){
            l ++;
        }
        if (l < r) {
            temp[0] = nodes[MAX_DEPTH][r][0];
            temp[1] = nodes[MAX_DEPTH][r][1];
            temp[2] = nodes[MAX_DEPTH][r][2];
            nodes[MAX_DEPTH][r][0] = nodes[MAX_DEPTH][l][0];
            nodes[MAX_DEPTH][r][1] = nodes[MAX_DEPTH][l][1];
            nodes[MAX_DEPTH][r][2] = nodes[MAX_DEPTH][l][2];
            nodes[MAX_DEPTH][l][0] = temp[0];
            nodes[MAX_DEPTH][l][1] = temp[1];
            nodes[MAX_DEPTH][l][2] = temp[2];
        }
    }
    nodes[MAX_DEPTH][left][0] = nodes[MAX_DEPTH][r][0];
    nodes[MAX_DEPTH][left][1] = nodes[MAX_DEPTH][r][1];
    nodes[MAX_DEPTH][left][2] = nodes[MAX_DEPTH][r][2];
    nodes[MAX_DEPTH][r][0] = base;
    nodes[MAX_DEPTH][r][1] = base_x;
    nodes[MAX_DEPTH][r][2] = base_y;
    quick_sort(left, l - 1);
    quick_sort(r + 1, right);
}

void pred_init(Gobang *gobang){
    /*
     * 生成 depth = MAX_DEPTH 的考虑步骤
     */
    generate_pred(gobang, MAX_DEPTH);
}

void node_sort(Gobang *gobang){
    // 启发式搜索函数, 对于所有待搜索节点进行排序, 便于α-β剪枝
    int index = 0;
    for(int i = 0; i < BOARD_SIZE; i ++){
        for(int j = 0; j < BOARD_SIZE; j ++){
            if(gobang->pos_steps[i][j] == 0){
                continue;
            }
            fall(gobang, i, j);
            nodes[MAX_DEPTH][index][0] = abs(get_score(gobang, i, j));
            nodes[MAX_DEPTH][index][1] = i;
            nodes[MAX_DEPTH][index][2] = j;
            index++;
            remove_piece(gobang, i, j);
        }
    }
    nodes[MAX_DEPTH][index][0] = -1;
    quick_sort(0, index - 1);
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
                    inf_pieces->append(inf_pieces, 0, p_x, p_y);
                    count++;
                } else if(gobang->chessboard[p_x][p_y] == PLAYER_BLACK){
                    // 异色子， 判分后退出该轮
                    piece_score[p_x][p_y] = get_score(gobang, p_x, p_y);
                    inf_pieces->append(inf_pieces, 0, p_x, p_y);

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

int init(){
    inf_pieces = create_stack(81);
    src_statement = (int **)malloc(sizeof(int) * BOARD_SIZE);
    for (int i = 0; i < BOARD_SIZE; i ++) {
        src_statement[i] = (int *) malloc(sizeof(int) * BOARD_SIZE);
    }
    return 0;
}

int get_score(Gobang *gobang, const int x, const int y){
    if(gobang->chessboard[x][y] == 0){
        return 0;
    }
    int i, in_is_win;
    char pattern[PATTERN_SIZE] = {0}; // 位于x, y坐标的棋子的字符串模式
    PIECE piece = gobang->chessboard[x][y];
    int score = 0;
    int is_in_bound, space_count;
    int p_x = x, p_y = y, dir = 1;

    // 遍历
    for(i = 0; i < DIR_NUM; i ++){
        // 遍历八个方向
        // 初始化
        int mid = 5, count;    // 起始遍历点
        in_is_win = 1;
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
                    if(space_count == 2){
                        // 如果说没有跳过空格，则加连子数
                        in_is_win ++;
                    }
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
        int suc_index; // 成功匹配的下标, -1则表示没有匹配到

        int left = 0;
        // 去除左侧多余的 \0 和 $
        for(; left < PATTERN_SIZE; left ++){
            if(pattern[left] == '$' && pattern[left + 1] == '$'){
                left ++;
                break;
            }
            if(pattern[left] != '\0') {
                break;
            }
        }
        suc_index = find_patten(pattern + left);
        if(suc_index != -1){
            score += statements[suc_index];
            if((suc_index == 16 || suc_index == 17) && piece == ai){
                score++;
            }
        }
        if(in_is_win >= 5){
            score += 1000000;
        }
    }
    return score * piece * ai;
}

int evaluate(Gobang *gobang){
    /*
     * 评估棋盘局势
     */
    int x, y, i;
    int chessboard_score = 0;
    for(i = 0; i < gobang->steps->sp; i ++){
        x = gobang->steps->stack[i][1];
        y = gobang->steps->stack[i][2];
        chessboard_score += piece_score[x][y];
    }
    return chessboard_score;
}

int search(Gobang *gobang, int depth, int alpha, int beta, PIECE cur_player){
    /*
     * 搜索算法, 返回一个分数
     */
    if(depth == 0 || gobang->pos_steps_num == 0){
        // 遍历到底层, 开始算分
        return evaluate(gobang);
    }
    // 搜索
    int score;
    if(cur_player == ai){
        // max 层
        for(int i = 0; i < BOARD_SIZE; i ++){
            for(int j = 0; j < BOARD_SIZE; j ++){
                if(gobang->pos_steps[i][j] == 0){
                    continue;
                }
                fall(gobang, i, j); // 下棋
                update_score(gobang);
                score = search(gobang, depth - 1, alpha, beta, -cur_player);
                if(score > alpha){
                    alpha = score;
                    if (depth == MAX_DEPTH){
                        best_pos[1] = j;
                        best_pos[0] = i;
                    }
                }
                remove_piece(gobang, i, j);
                while (inf_pieces->sp > 0){
                    int *res = inf_pieces->pop(inf_pieces);
                    piece_score[res[1]][res[2]] = get_score(gobang, res[1], res[2]);
                }
                if(alpha >= beta){
                    return alpha;
                }
            }
        }
        return alpha;
    } else {
        // min 层
        for(int i = 0; i < BOARD_SIZE; i ++){
            for(int j = 0; j < BOARD_SIZE; j ++){
                if(gobang->pos_steps[i][j] == 0){
                    continue;
                }
                fall(gobang, i, j); // 下棋
                update_score(gobang);
                score =  search(gobang, depth - 1, alpha, beta, -cur_player);
                if(score < beta){
                    beta = score;
                }
                remove_piece(gobang, i, j);
                while (inf_pieces->sp != 0){
                    int *res = inf_pieces->pop(inf_pieces);
                    piece_score[res[1]][res[2]] = get_score(gobang, res[1], res[2]);
                }
                if(alpha >= beta){
                    return beta;
                }
            }
        }
        return beta;

    }
}

int first_search(Gobang *gobang, int depth, int alpha, int beta, PIECE cur_player){
    /*
     * 第一次搜素
     */

    for(int i = 0; i < 6; i ++){
        heu_locations[i][0][0] = -1;
    }
    heuristically_search(gobang);
    int score;
    int i, j;
    for(int count = 5; count >= 0; count --){
        for(int index = 0; index < BOARD_SIZE * BOARD_SIZE; index ++){
            if (heu_locations[count][index][0] == -1) {
                break;
            }
            i = heu_locations[count][index][0];
            j = heu_locations[count][index][1];
            fall(gobang, i, j);
            update_score(gobang);
            score = search(gobang, depth - 1, alpha, beta, -cur_player);
            if(score > alpha){
                alpha = score;
                if (depth == MAX_DEPTH){
                    best_pos[1] = j;
                    best_pos[0] = i;
                }
            }
            remove_piece(gobang, i, j);
            update_score(gobang);
            if(alpha >= beta){
                return alpha;
            }
        }
    }
    return alpha;
}
