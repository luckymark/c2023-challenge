#pragma once
#include "stackAndSeqList.h"

// 检测是否有五子连珠
bool CheckFive(Point point);

// 检测某个方向是否有五子连珠
bool CheckFiveDirection(Point point, int offsetX, int offsetY, ChessColor color);

// 基于极大值极小值搜索和Alpha-Beta剪枝的AI算法获取最佳落子点
void GetBestPoint();

// 极大值极小值搜索
int MinMaxSearch(int depth, int alpha, int beta);

// 评估局势
int evaluateSituation();

// 评估点的价值
int EvaluatePoint(int row, int col, ChessColor color);

// 评估某个方向的价值
int EvaluateDirection(int row, int col, int offsetX, int offsetY, ChessColor color);

// 评估顺序表中的点的价值
int EvaluateSL(SLDataType* pInt, int size);

// 哈希函数
int Hash(SLDataType* pInt);

// 在虚拟棋盘上落子
void PutVirtualChess(Point point, int* pCount, int pIntX[8], int pIntY[8]);

// 在虚拟棋盘上撤销落子
void RevokeVirtualChess(Point point, int count, int pIntX[8], int pIntY[8]);

// 读取当前链表中的棋型
SL ReadChessModel(int* pCount, int row, int col, int offsetX, int offsetY, ChessColor color, SL* sl);

// 给棋盘上的VIRTUAL_CHESS赋予优先级
void GiveBoardPriority(Chess fir[],
	Chess sec[],
	Chess thi[],
	Chess fou[],
	int* firSize,
	int* secSize,
	int* thiSize,
	int* fouSize);

// 检查当前位置的棋型
void CheckChessModel(SLDataType* pSLa, int* count, bool* inFir, bool* inThi, bool* inFou);