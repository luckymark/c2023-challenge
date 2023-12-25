#pragma once

#include "stackAndSeqList.h"

//初始化游戏
void InitGame();

// 初始化棋盘状态
void InitChessBoard();

// 初始化虚拟棋盘状态
void InitVirtualChessBoard();

// 游戏菜单界面
void MenuWindow();

// 选择界面
void SelectSideWindow();

// PVP游戏界面
void GamePVP();

// PVE游戏界面
void GamePVE();

// 根据游戏状态画不同的界面,并根据玩家的点击更新游戏状态
void UpDateGameState();

// 更新游戏结果
GameResult UpdateGameResult(ChessColor curChessColor);

// 检查是否有五子连珠
bool CheckFiveInGame(Point point);

// 检查某个方向是否有五子连珠
bool CheckFiveDirectionInGame(Point point, int offsetX, int offsetY);

// 结束操作
void DoFinish();