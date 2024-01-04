#pragma once
#include "stackAndSeqList.h"

// 处理菜单界面的点击
void HandleMenuClick();

// 处理选择界面的点击
void HandleSelectClick();

// 根据PVP游戏内的点击，更新游戏状态
void UpDatePVPGame();

// 根据pve游戏内的点击，更新游戏状态
void UpDatePVEGame();

// 悔棋操作
void RegretStepPVE();

// 下棋操作
void PutChess(int row, int col);

// 游戏结束后，弹出游戏结束窗口，根据玩家选择的操作，返回相应的操作
GameClick GameOverWindow();

// 处理游戏结束窗口的点击
GameClick HandleGameOverClick();
// 交换当前玩家
void StepExchange();

// 判断当前棋手是否是AI
bool IsAI();
