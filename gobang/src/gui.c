#include "../headers/gui.h"

void gobang_gui(Gobang *gobang, int (*player_move)(Gobang *gobang, int x, int y), void (*ai_move)(Gobang *gobang), int *ai_piece){
    // 初始化窗口
    int mode = 2;   // 默认AI后手
    InitWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"gobang AI");
    SetTraceLogLevel(LOG_WARNING);

    // 设置背景色
    Color color = GetColor(0xfafafaff);

    // 加载图片资源
    Texture t_chess_board = LoadTexture("..\\..\\gobang\\res\\chessboard.png");
    Texture t_white = LoadTexture("..\\..\\gobang\\res\\white_piece.png");
    Texture t_black = LoadTexture("..\\..\\gobang\\res\\black_piece.png");
    Texture t_selected = LoadTexture("..\\..\\gobang\\res\\selected.png");
    Texture t_black_win = LoadTexture("..\\..\\gobang\\res\\black_win.png");
    Texture t_white_win = LoadTexture("..\\..\\gobang\\res\\white_win.png");
    Texture t_pressSpace2Continue = LoadTexture("..\\..\\gobang\\res\\pressSpace2Continue.png");
    Texture t_take_back = LoadTexture("..\\..\\gobang\\res\\takeBack.png");
    Texture t_pressS2SwitchModes = LoadTexture("..\\..\\gobang\\res\\pressS2switchModes.png");
    Texture modes[3] = {
            LoadTexture("..\\..\\gobang\\res\\pvp.png"),   // pvp 0
            LoadTexture("..\\..\\gobang\\res\\AIFirstHand.png"),   // AI first 1
            LoadTexture("..\\..\\gobang\\res\\AISecondHand.png")   // AI second 2
    };

    int piece_start_x = CHESSBOARD_START_X + MARGIN - PIECE_SIZE / 2 + 1;
    int piece_start_y = CHESSBOARD_START_Y + MARGIN - PIECE_SIZE / 2 + 1;
    int mouse_x, mouse_y, selected_x, selected_y, re_x, re_y;
    int win = -100;
    int pos_x, pos_y;
    int mouse_pos_x, mouse_pos_y;
    int player_move_success = 1;
    int is_game_end = 0;

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

        if(IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)){
            print_debug_msg(gobang);
        }
        if(!is_game_end){
            if(gobang->now_player == *ai_piece && (player_move_success == 1 || gobang->steps->is_empty(gobang->steps))){
                // 该电脑了
                ai_move(gobang);
                win = is_win(gobang);
            }
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                // 按下鼠标 且 玩家可以行动
                // 落子
                player_move_success = abs(player_move(gobang, re_x, re_y));
                // 判断是否获胜
                win = is_win(gobang);
            }
            if(IsKeyPressed(KEY_R)){
                // 撤回
                if(!(mode == 1 && gobang->steps->sp == 1)){
                    // AI先手第一步不撤回
                    if(mode != 0){
                        // 非玩家局面多撤回一次
                        take_back(gobang);
                    }
                    take_back(gobang);
                }
            } else if (IsKeyPressed(KEY_S)){
                // 在游戏未下子时方可切换
                mode ++;
                mode %= 3;
                if(mode == 0){
                    // 玩家对垒
                    *ai_piece = -0;
                } else if(mode == 1){
                    // AI 执黑棋
                    *ai_piece = -1;    // 切换AI棋子， 重新开始
                } else if (mode == 2){
                    // AI 执白棋
                    *ai_piece = 11;
                }
                while (!gobang->steps->is_empty(gobang->steps)){
                    take_back(gobang);
                }
                is_game_end = 0;
                win = -100;
            }
        }


        if(is_game_end && IsKeyPressed(KEY_SPACE)){
            while (!gobang->steps->is_empty(gobang->steps)){
                take_back(gobang);
            }
            is_game_end = 0;
            win = -100;
        }


        // 绘制
        BeginDrawing();
        // printf("111\n");
        ClearBackground(color);
        DrawTexture(t_chess_board, CHESSBOARD_START_X, CHESSBOARD_START_Y, WHITE);
        DrawTexture(t_take_back, 900, CHESSBOARD_START_Y + 100, WHITE);
        DrawTexture(t_pressS2SwitchModes, 900, CHESSBOARD_START_Y + 200, WHITE);
        mode %= 3;
        DrawTexture(modes[mode], 900, 900, WHITE);
        // DrawTexture(t_black_win, 1000, 1000, WHITE);
        for(int i = 0; i < 15; i ++){
            for(int j = 0; j < 15; j ++){
/*                if(gobang->chessboard == 0){
                    continue;
                }*/
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

        if(win == PLAYER_BLACK || win == PLAYER_WHITE){
            is_game_end = 1;
            if(win == PLAYER_WHITE){
                DrawTexture(t_white_win, 900, CHESSBOARD_START_Y, WHITE);
            } else {
                DrawTexture(t_black_win, 900, CHESSBOARD_START_Y, WHITE);
            }
            DrawTexture(t_pressSpace2Continue, CHESSBOARD_START_X, 900, WHITE);
        }
        EndDrawing();
    }
    UnloadTexture(t_chess_board);
    UnloadTexture(t_white);
    UnloadTexture(t_black);
    UnloadTexture(t_selected);
    // UnloadImage(chess_board);
    CloseWindow();
}