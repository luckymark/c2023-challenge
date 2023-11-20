#include "headers/gui.h"
#include "headers/gobang.h"
#include "headers/alpha_beta_pruning.h"



void ai_move(Gobang *gobang){

    /*printf("\n[DEBUG]: \n");
    print_chessboard_in_stdin(gobang);
    printf("\n");
    print_pos_steps_in_stdin(gobang);
    printf("\n");*/

    long start = clock();
    is_init = 0;
    init_score(gobang);
    search(gobang, MAX_DEPTH, -INFINITY, INFINITY - 1, PLAYER_WHITE);
    long end = clock();
    printf("\ntime: %ld ms\n", end - start);
    if(best_pos[0] == -1){
        printf("[ERROR] FAILED TO SEARCH THE ANSWER!!!\n");
        best_pos[0] = 14;
        best_pos[1] = 14;
    } else {
        printf("[DEBUG] AI STEP: (%d, %d)\n", best_pos[0], best_pos[1]);
        fall(gobang, best_pos[0], best_pos[1]);
    }
    best_pos[0] = -1;
    best_pos[1] = -1;
}

int player_move(Gobang *gobang, int x, int y){
    return fall(gobang, x, y);
}

int main() {
    // 暂时默认电脑为白棋后手
    // file = fopen("F:\\code\\c\\gobang\\res\\m", "a");
    Gobang *gobang = create_gobang();
    gobang_gui(gobang, player_move, ai_move);
}