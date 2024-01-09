#include"search_function.h"
#include<time.h>
extern int step;
extern Board board_main;
extern int computer_next_i;//用静态变量来存储第一层电脑的要下棋的位置
extern int computer_next_j;
extern int turn;
extern FILE * fp;
extern FILE * fp_2;
extern int result;
void player_move(Image * board){
    Vector2 point={-1,-1};
    point=check_hit();
    if(point.x>=0&&point.y>=0){
        step++;
        board_main.lattice_extinct[(int)point.y][(int)point.x]=1;//用1表示玩家的位置
        ImageDrawCircle(board,board_main.point_location[(int)point.y][(int)point.x].x,board_main.point_location[(int)point.y][(int)point.x].y,LATTICE_R,BLACK);
        clear_value(&board_main,(int)point.y,(int)point.x);
        evaluate(&board_main,(int)point.y,(int)point.x);
        result=judge_win(&board_main);
    }
}
void computer_move(Image * board){
    clock_t start=clock();
    step++;
    fprintf(fp,"Step %d:\n",step);
    int p=minimax_search(board_main,LAYER,ALPHA,BETA);
    if(p<-50000000){
        int min=INT_MAX;
        for(int i=1;i<=15;i++){
            for(int j=1;j<=15;j++){
                if(!judge_search(&board_main,i,j))
                    continue;
                else{
                    int control_score_new=0;
                    int control_score_old=0;
                    control_score_old+= every_value(&board_main,i,j,2,-1);
                    control_score_old+= every_value(&board_main,i,j,4,-1);
                    control_score_old+= every_value(&board_main,i,j,6,-1);
                    control_score_old+= every_value(&board_main,i,j,8,-1);
                    board_main.lattice_extinct[i][j]=-1;
                    control_score_new+= every_value(&board_main,i,j,2,-1);
                    control_score_new+= every_value(&board_main,i,j,4,-1);
                    control_score_new+= every_value(&board_main,i,j,6,-1);
                    control_score_new+= every_value(&board_main,i,j,8,-1);//因为是-1，所以值没变，不用clear_value
                    board_main.lattice_extinct[i][j]=0;
                    fprintf(fp,"(%d,%d): %d\n",i,j,control_score_new-control_score_old);
                    if(control_score_new-control_score_old<min){
                        min=control_score_new-control_score_old;
                        computer_next_i=i;
                        computer_next_j=j;
                    }
                }
            }
        }
    }
    fprintf(fp,"\n\n\n");
    board_main.lattice_extinct[computer_next_i][computer_next_j]=-1;
    ImageDrawCircle(board,board_main.point_location[computer_next_i][computer_next_j].x,board_main.point_location[computer_next_i][computer_next_j].y,LATTICE_R,WHITE);
    clear_value(&board_main,computer_next_i,computer_next_j);
    evaluate(&board_main,computer_next_i,computer_next_j);
    result=judge_win(&board_main);
    clock_t end=clock();
    fprintf(fp_2,"%f\n",(double)(end-start)/CLOCKS_PER_SEC);
    turn=0;
}