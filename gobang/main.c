#include "headers/gui.h"
#include "headers/gobang.h"
#include "headers/alpha_beta_pruning.h"




void ai_move(Gobang *gobang){
    long start = clock();
    if(gobang->steps->is_empty(gobang->steps)){
        best_pos[0] = 7;
        best_pos[1] = 7;
    } else {
        init_score(gobang);
        first_search(gobang, MAX_DEPTH, -INFINITY, INFINITY - 1, ai);
    }
    long end = clock();
    printf("\ntime: %ld ms\n", end - start);
    if(best_pos[0] == -1){
        printf("[ERROR] FAILED TO SEARCH THE ANSWER!!!\n");
        best_pos[0] = 14;
        best_pos[1] = 14;
    } else {
        fall(gobang, best_pos[0], best_pos[1]);
    }
    best_pos[0] = -1;
    best_pos[1] = -1;
}

int player_move(Gobang *gobang, int x, int y){
    return fall(gobang, x, y);
}

int main() {
    Gobang *gobang = create_gobang();
    init();
    ai = PLAYER_WHITE;
    gobang_gui(gobang, player_move, ai_move, &ai);

}