#pragma once

// 加载字体和图片
void InitAndLoadImgFont();

// 释放字体和图片
void UnloadFontAndImg();

// 判断是否准备好画菜单界面
bool IsWindowReadyForMenu();

// 判断是否准备好画选择界面
bool IsWindowReadyForSelect();

// 判断是否准备好画PVP游戏界面
bool IsWindowReadyForPVP();

// 判断是否准备好画PVE游戏界面
bool IsWindowReadyForPVE();

// 画游戏界面
void DrawBoard();

// 画棋盘上的字
void DrawBoardChar();

//根据玩家选择的棋子颜色，画玩家和电脑（或玩家1和2）的棋盒
void DrawBox();

// 画棋盘上的棋子
void DrawChess();

// 画菜单界面
void DrawMenu();

// 画选择界面
void DrawSelectSideMenu();

// 画游戏结束界面
void DrawGameOverMenu();