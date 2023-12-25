#ifndef C2023_CHALLENGE_SEARCH_FUNCTION_H
#define C2023_CHALLENGE_SEARCH_FUNCTION_H
#include "gobang.h"
#define ALPHA INT_MIN+1
#define BETA INT_MAX-1
typedef struct{
    int blank_i;
    int blank_j;
    int delta_score;
    int start_location_i[5];//存储起始i值
    int start_location_j[5];//存储起始j值
    int layer[5];//存储每个方向的值
}blank;
int judge_search(Board *,int,int);//检测是否需要着子。
int minimax_search(Board ,int layer,int c_alpha,int c_beta);//传入alpha及beta计算当前值
void evaluate(Board *,int i,int j);//需要改变结构中的局势分数，所以使用指针
void clear_value(Board *,int i,int j);//清除分数
int get_score(int);
int every_value(Board *,int i,int j,int num,int control);
int judge_win(Board *);
void quick_sort(blank *,int start,int end);
void Heuristically_evaluate(Board board_main,int i,int j,int state,blank * test_blank,int capacity);
void change(Board *,blank,int );
#endif //C2023_CHALLENGE_SEARCH_FUNCTION_H