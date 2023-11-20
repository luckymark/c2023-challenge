#include "../headers/gui.h"

void gobang_gui(Gobang *gobang, int (*player_move)(Gobang *gobang, int x, int y), void (*ai_move)(Gobang *gobang)){
    // 初始化窗口
    InitWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"gobang AI");
    SetTraceLogLevel(LOG_WARNING);

    // 设置背景色
    Color color = GetColor(0xfafafaff);

    // 加载图片资源
    Texture t_chess_board = LoadTexture("F:\\code\\c\\gobang\\res\\chessboard.png");
    Texture t_white = LoadTexture("F:\\code\\c\\gobang\\res\\white_piece.png");
    Texture t_black = LoadTexture("F:\\code\\c\\gobang\\res\\black_piece.png");
    Texture t_selected = LoadTexture("F:\\code\\c\\gobang\\res\\selected.png");

    int piece_start_x = CHESSBOARD_START_X + MARGIN - PIECE_SIZE / 2 + 1;
    int piece_start_y = CHESSBOARD_START_Y + MARGIN - PIECE_SIZE / 2 + 1;
    int mouse_x, mouse_y, selected_x, selected_y, re_x, re_y;
    int win;
    int pos_x, pos_y;
    int mouse_pos_x, mouse_pos_y;
    int player_move_success;

    // 绘制
    while(!WindowShouldClose()) {

        // 鼠标坐标映射
        mouse_x = GetMouseX();
        mouse_y = GetMouseY();
        selected_x = (mouse_x - piece_start_x) / GAP_LENGTH;
        selected_y = (mouse_y - piece_start_y) / GAP_LENGTH;
        // selected是图像层的操作
        re_x = selected_y;  // 坐标映射
        re_y = selected_x;


        if(gobang->now_player == PLAYER_WHITE && player_move_success == -1){
            // 该电脑了

            ai_move(gobang);

            win = is_win(gobang);
        }
        player_move_success = 0;
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            // 按下鼠标 且 玩家可以行动
            printf("\n[DEBUG] (%d, %d)\n", re_x, re_y); // 控制台调试信息

            // 落子
            player_move_success = player_move(gobang, re_x, re_y);

            // 判断是否获胜
            win = is_win(gobang);
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)){
            print_debug_msg(gobang);
        }

        // 绘制
        BeginDrawing();
        // printf("111\n");
        ClearBackground(color);
        DrawTexture(t_chess_board, CHESSBOARD_START_X, CHESSBOARD_START_Y, WHITE);
        for(int i = 0; i < 15; i ++){
            for(int j = 0; j < 15; j ++){
                if(gobang->chessboard == 0){
                    continue;
                }
                pos_x = BOUNDARY_LENGTH + CHESSBOARD_START_X + GAP_LENGTH * j;
                pos_y = BOUNDARY_LENGTH + CHESSBOARD_START_Y + GAP_LENGTH * i;
                if(gobang->chessboard[i][j] < 0){
                    DrawTexture(t_black, pos_x, pos_y, WHITE);
                } else if (gobang->chessboard[i][j] > 0){
                    DrawTexture(t_white, pos_x, pos_y, WHITE);
                }
            }
        }

        if(selected_x < 15 && selected_y < 15){
            mouse_pos_x = BOUNDARY_LENGTH + CHESSBOARD_START_X + GAP_LENGTH * selected_x;
            mouse_pos_y = BOUNDARY_LENGTH + CHESSBOARD_START_Y + GAP_LENGTH * selected_y;
            DrawTexture(t_selected, mouse_pos_x, mouse_pos_y, WHITE);
        }


        EndDrawing();
        if(win == PLAYER_BLACK){
            printf("------------------------black winning !!!\n");
            getchar();
        } else if (win == PLAYER_WHITE){
            printf("------------------------white winning !!!\n");
            getchar();
        }
    }
    UnloadTexture(t_chess_board);
    UnloadTexture(t_white);
    UnloadTexture(t_black);
    UnloadTexture(t_selected);
    // UnloadImage(chess_board);
    CloseWindow();
}