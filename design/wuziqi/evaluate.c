#include <stdio.h>
#include "evaluate.h"
#include "interaction.h"

extern Global global;

// 评估表
HashTable evaluateHashTable[] = {
	{ EMPTY, 0 },
	{ MIAN_1, 0 },
	{ HUO_1, 1 },
	{ MIAN_2, 150 },
	{ HUO_1, 1 },
	{ MIAN_2_101, 250 },
	{ HUO_2, 650 },
	{ MIAN_3, 500 },
	{ HUO_1, 1 },
	{ MIAN_2_1001, 200 },
	{ HUO_2_101, 400 },
	{ MIAN_3_102, 800 },
	{ HUO_2, 650 },
	{ MIAN_3_201, 800 },
	{ HUO_3, 2000 },
	{ CHONG_4, 2500 },
	{ HUO_1, 1 },
	{ MIAN_2_10001, 100 },
	{ MIAN_2_1001, 200 },
	{ MIAN_3_1002, 600 },
	{ HUO_2_101, 400 },
	{ MIAN_3_10101, 550 },
	{ HUO_3_102, 3100 },
	{ CHONG_4_103, 2700 },
	{ HUO_2, 650 },
	{ MIAN_3_2001, 600 },
	{ HUO_3_201, 2100 },
	{ CHONG_4_202, 2600 },
	{ HUO_3, 2000 },
	{ CHONG_4_301, 2700 },
	{ HUO_4, 500000 },
	{ LIAN_5, 1000000 },
	{ MIAN_1, 0 },
	{ MIAN_1, 0 },
	{ MIAN_2_10001, 100 },
	{ HUN_10002, 175 },
	{ MIAN_2_1001, 200 },
	{ HUN_100101, 300 },
	{ MIAN_3_2001, 600 },
	{ HUN_1003, 725 },
	{ MIAN_2_101, 250 },
	{ HUN_101001, 300 },
	{ MIAN_3_10101, 550 },
	{ HUN_10102, 937 },
	{ MIAN_3_102, 800 },
	{ HUN_10201, 1000 },
	{ CHONG_4_301, 3000 },
	{ HUN_104, 3325 },
	{ MIAN_2, 150 },
	{ HUN_20001, 175 },
	{ MIAN_3_1002, 600 },
	{ HUN_2002, 750 },
	{ MIAN_3_201, 800 },
	{ HUN_20101, 937 },
	{ CHONG_4_202, 2600 },
	{ HUN_203, 3650 },
	{ MIAN_3, 500 },
	{ HUN_3001, 725 },
	{ CHONG_4_103, 2700 },
	{ HUN_302, 3650 },
	{ CHONG_4, 2500 },
	{ HUN_401, 3625 },
	{ LIAN_5, 1000000 },
	{ LIAN_6, 1000000 },
	{ EMPTY, 0 },
	{ HUO_1, 1 },
	{ HUO_1, 1 },
	{ MIAN_2, 150 },
	{ HUO_1, 1 },
	{ MIAN_2_101, 250 },
	{ HUO_2, 650 },
	{ MIAN_3, 500 },
	{ HUO_1, 1 },
	{ MIAN_2_1001, 200 },
	{ HUO_2_101, 400 },
	{ MIAN_3_102, 800 },
	{ HUO_2, 650 },
	{ MIAN_3_201, 800 },
	{ HUO_3, 3000 },
	{ CHONG_4, 2700 },
	{ MIAN_1, 0 },
	{ MIAN_2_10001, 100 },
	{ MIAN_2_1001, 200 },
	{ MIAN_3_1002, 600 },
	{ MIAN_2_101, 250 },
	{ MIAN_3_10101, 550 },
	{ MIAN_3_102, 800 },
	{ CHONG_4_103, 3000 },
	{ MIAN_2, 150 },
	{ MIAN_3_2001, 600 },
	{ MIAN_3_201, 800 },
	{ CHONG_4_202, 2600 },
	{ MIAN_3, 500 },
	{ CHONG_4_301, 2700 },
	{ CHONG_4, 2500 },
	{ LIAN_5, 1000000 },
	{ EMPTY, 0 },
};

// 基于极大值极小值搜索和Alpha-Beta剪枝的AI算法获取最佳落子点
void GetBestPoint()
{
	// 如果是第一步，下在棋盘中间
	if (global.stepNumber == 0)
	{
		global.bestPoint.row = 7;
		global.bestPoint.col = 7;
	}
	else
	{
		// 如果不是第一步，就基于极大极小值搜索，找到最佳落子点
		MinMaxSearch(MAX_DEPTH, -INFINITY, INFINITY);
	}
}

// 基于极大值极小值搜索和Alpha-Beta剪枝的AI算法
int MinMaxSearch(int depth, int alpha, int beta)
{
	// 递归到底，返回局势评估值
	if (depth == 0)
	{
		return evaluateSituation();
	}

	bool isRoot = depth == MAX_DEPTH;

	// 遍历棋盘上的VIRTUAL_CHESS，即AI可以落子的位置,
	// 寻找可以成为连五和阻止对手连五的位置和可以成为活四和阻止对手活四的位置并设置为第一优先级
	// 寻找可以成为四三和三三的位置和可以成为四三和三三的位置并设置为第二优先级
	// 寻找可以成为冲四和阻止对手冲四的位置和可以成为活三和阻止对手活三的位置并设置为第三优先级
	// 寻找可以成为活二和阻止对手活二的位置和可以成为眠三和阻止对手眠三的位置并设置为第四优先级
	int firstSize = 0;
	int secondSize = 0;
	int thirdSize = 0;
	int forthSize = 0;
	Chess first[MAX_FIR];
	Chess second[MAX_SEC];
	Chess third[MAX_THI];
	Chess forth[MAX_FOU];
	GiveBoardPriority(first, second, third, forth, &firstSize, &secondSize, &thirdSize, &forthSize);

	for (int i = 0; i < firstSize; ++i)
	{
		int row = first[i].x;
		int col = first[i].y;
		Point point = { row, col };
		int count = 0;
		int score = 0;
		int x[25];
		int y[25];
		// 在当前位置判断是否有连五，如果有，就不再搜索，如果上一步棋是AI下的直接返回最大值-1，如果上一步棋是玩家下的直接返回最小值+1
		if (CheckFive(point))
		{
			score = IsAI() ? INFINITY - 1 : -INFINITY + 1;
		}
		else
		{
			// 落子
			PutVirtualChess(point, &count, x, y);
			// 递归生成博弈树，并评估叶子结点的局势
			score = MinMaxSearch(depth - 1, alpha, beta);
			//打印虚拟棋盘，打印在控制台上，用于调试
			//PrintfVirtualChessBoard();
			// 撤销落子
			RevokeVirtualChess(point, count, x, y);
			//PrintfVirtualChessBoard();
		}

		if (IsAI())
		{
			// AI要选对自己最有利的节点（分最高的）
			if (score > alpha)
			{
				// 最高值被刷新，更新alpha值
				alpha = score;
				if (isRoot)
				{
					// 根节点处更新AI最好的棋位
					global.bestPoint = point;
					//printf("可能的一级节点: %d %d\n", global.bestPoint.row, global.bestPoint.col);
					//printf("alpha: %d\n", alpha);
				}
			}
		}
		else
		{
			// 对手要选对AI最不利的节点（分最低的）
			if (score < beta)
			{
				// 最低值被刷新，更新beta值
				beta = score;
			}
		}

		if (alpha >= beta)
		{
			// 剪枝
			break;
		}
	}

	for (int i = 0; i < secondSize; ++i)
	{
		if (alpha >= beta)
		{
			// 剪枝
			break;
		}
		int row = second[i].x;
		int col = second[i].y;
		Point point = { row, col };
		int count = 0;
		int score = 0;
		int x[25];
		int y[25];
		// 在当前位置判断是否有连五，如果有，就不再搜索，如果上一步棋是AI下的直接返回最大值-1，如果上一步棋是玩家下的直接返回最小值+1
		if (CheckFive(point))
		{
			score = IsAI() ? INFINITY - 1 : -INFINITY + 1;
		}
		else
		{
			// 落子
			PutVirtualChess(point, &count, x, y);
			// 递归生成博弈树，并评估叶子结点的局势
			score = MinMaxSearch(depth - 1, alpha, beta);
			//打印虚拟棋盘，打印在控制台上，用于调试
			//PrintfVirtualChessBoard();
			// 撤销落子
			RevokeVirtualChess(point, count, x, y);
			//PrintfVirtualChessBoard();
		}
		if (IsAI())
		{
			// AI要选对自己最有利的节点（分最高的）
			if (score > alpha)
			{
				// 最高值被刷新，更新alpha值
				alpha = score;
				if (isRoot)
				{
					// 根节点处更新AI最好的棋位
					global.bestPoint = point;
					//printf("可能的二级节点: %d %d\n", global.bestPoint.row, global.bestPoint.col);
					//printf("alpha: %d\n", alpha);
				}
			}
		}
		else
		{
			// 对手要选对AI最不利的节点（分最低的）
			if (score < beta)
			{
				// 最低值被刷新，更新beta值
				beta = score;
			}
		}

		if (alpha >= beta)
		{
			// 剪枝
			break;
		}
	}

	for (int i = 0; i < thirdSize; ++i)
	{
		if (alpha >= beta)
		{
			// 剪枝
			break;
		}
		int row = third[i].x;
		int col = third[i].y;
		Point point = { row, col };
		int count = 0;
		int score = 0;
		int x[25];
		int y[25];
		// 在当前位置判断是否有连五，如果有，就不再搜索，如果上一步棋是AI下的直接返回最大值-1，如果上一步棋是玩家下的直接返回最小值+1
		if (CheckFive(point))
		{
			score = IsAI() ? INFINITY - 1 : -INFINITY + 1;
		}
		else
		{
			// 落子
			PutVirtualChess(point, &count, x, y);
			// 递归生成博弈树，并评估叶子结点的局势
			score = MinMaxSearch(depth - 1, alpha, beta);
			//打印虚拟棋盘，打印在控制台上，用于调试
			//PrintfVirtualChessBoard();
			// 撤销落子
			RevokeVirtualChess(point, count, x, y);
			//PrintfVirtualChessBoard();
		}
		if (IsAI())
		{
			// AI要选对自己最有利的节点（分最高的）
			if (score > alpha)
			{
				// 最高值被刷新，更新alpha值
				alpha = score;
				if (isRoot)
				{
					// 根节点处更新AI最好的棋位
					global.bestPoint = point;
					//printf("可能的三级节点: %d %d\n", global.bestPoint.row, global.bestPoint.col);
					//printf("alpha: %d\n", alpha);
				}
			}
		}
		else
		{
			// 对手要选对AI最不利的节点（分最低的）
			if (score < beta)
			{
				// 最低值被刷新，更新beta值
				beta = score;
			}
		}

		if (alpha >= beta)
		{
			// 剪枝
			break;
		}
	}

	for (int i = 0; i < forthSize; ++i)
	{
		if (alpha >= beta)
		{
			// 剪枝
			break;
		}
		int row = forth[i].x;
		int col = forth[i].y;
		Point point = { row, col };
		int count = 0;
		int score = 0;
		int x[25];
		int y[25];
		// 在当前位置判断是否有连五，如果有，就不再搜索，如果上一步棋是AI下的直接返回最大值-1，如果上一步棋是玩家下的直接返回最小值+1
		if (CheckFive(point))
		{
			score = IsAI() ? INFINITY - 1 : -INFINITY + 1;
		}
		else
		{
			// 落子
			PutVirtualChess(point, &count, x, y);
			// 递归生成博弈树，并评估叶子结点的局势
			score = MinMaxSearch(depth - 1, alpha, beta);
			//打印虚拟棋盘，打印在控制台上，用于调试
			//PrintfVirtualChessBoard();
			// 撤销落子
			RevokeVirtualChess(point, count, x, y);
			//PrintfVirtualChessBoard();
		}

		if (IsAI())
		{
			// AI要选对自己最有利的节点（分最高的）
			if (score > alpha)
			{
				// 最高值被刷新，更新alpha值
				alpha = score;
				if (isRoot)
				{
					// 根节点处更新AI最好的棋位
					global.bestPoint = point;
					//printf("可能的四级节点: %d %d\n", global.bestPoint.row, global.bestPoint.col);
					//printf("alpha: %d\n", alpha);
				}
			}
		}
		else
		{
			// 对手要选对AI最不利的节点（分最低的）
			if (score < beta)
			{
				// 最低值被刷新，更新beta值
				beta = score;
			}
		}
		if (alpha >= beta)
		{
			// 剪枝
			break;
		}
	}

	firstSize = 0;
	secondSize = 0;
	thirdSize = 0;
	forthSize = 0;

	return IsAI() ? alpha : beta;
}

/*
给棋盘上的VIRTUAL_CHESS赋予优先级，优先级分为四个等级，分别是连五和阻止对手连五的位置和可以成为活四和阻止对手活四的位置并设置为第一优先级
寻找可以成为四三和三三的位置和可以成为四三和三三的位置并设置为第二优先级
寻找可以成为冲四和阻止对手冲四的位置和可以成为活三和阻止对手活三的位置并设置为第三优先级
寻找可以成为活二和阻止对手活二的位置和可以成为眠三和阻止对手眠三的位置并设置为第四优先级
 */
void GiveBoardPriority(Chess fir[],
	Chess sec[],
	Chess thi[],
	Chess fou[],
	int* firSize,
	int* secSize,
	int* thiSize,
	int* fouSize)
{
	SL sl;
	SeqListInit(&sl);
	for (int row = 0; row < BOARD_ROW; ++row)
	{
		for (int col = 0; col < BOARD_COL; ++col)
		{
			if (global.virtualBoard[row][col].color == VIRTUAL_CHESS)
			{
				// 读取当前位置四个方向上的棋型
				int count = 1;
				bool inMyFir = false;
				bool inMySec = false;
				bool inMyThi = false;
				bool inMyFou = false;
				bool inEnemyFir = false;
				bool inEnemySec = false;
				bool inEnemyThi = false;
				bool inEnemyFou = false;
				JudgeModel myJudge = { false, false, false, false, false,
									   false, false, false, false, false,
									   false, false };

				JudgeModel enemyJudge = { false, false, false, false, false,
										  false, false, false, false, false,
										  false, false };

				ReadChessModel(&count, row, col, 1, 0, global.curPlayer.color, &sl);
				CheckChessModel(sl.a, &count, &myJudge.inHFir, &myJudge.inHThi, &myJudge.inHFou);
				ReadChessModel(&count, row, col, 0, 1, global.curPlayer.color, &sl);
				CheckChessModel(sl.a, &count, &myJudge.inVFir, &myJudge.inVThi, &myJudge.inVFou);
				ReadChessModel(&count, row, col, 1, 1, global.curPlayer.color, &sl);
				CheckChessModel(sl.a, &count, &myJudge.inLSFir, &myJudge.inLSThi, &myJudge.inLSFou);
				ReadChessModel(&count, row, col, 1, -1, global.curPlayer.color, &sl);
				CheckChessModel(sl.a, &count, &myJudge.inRSFir, &myJudge.inRSThi, &myJudge.inRSFou);

				if (myJudge.inHFir || myJudge.inVFir || myJudge.inLSFir || myJudge.inRSFir)
				{
					inMyFir = true;
				}
				if (myJudge.inHThi || myJudge.inVThi || myJudge.inLSThi || myJudge.inRSThi)
				{
					inMyThi = true;
				}
				if (myJudge.inHFou || myJudge.inVFou || myJudge.inLSFou || myJudge.inRSFou)
				{
					inMyFou = true;
				}
				if (myJudge.inHThi && (myJudge.inVThi || myJudge.inLSThi || myJudge.inRSThi) ||
					myJudge.inVThi && (myJudge.inHThi || myJudge.inLSThi || myJudge.inRSThi) ||
					myJudge.inLSThi && (myJudge.inHThi || myJudge.inVThi || myJudge.inRSThi) ||
					myJudge.inRSThi && (myJudge.inHThi || myJudge.inVThi || myJudge.inLSThi))
				{
					inMySec = true;
				}

				ChessColor enemyColor = global.curPlayer.color == BLACK_CHESS ? WHITE_CHESS : BLACK_CHESS;
				ReadChessModel(&count, row, col, 1, 0, enemyColor, &sl);
				CheckChessModel(sl.a, &count, &enemyJudge.inHFir, &enemyJudge.inHThi, &enemyJudge.inHFou);
				ReadChessModel(&count, row, col, 0, 1, enemyColor, &sl);
				CheckChessModel(sl.a, &count, &enemyJudge.inVFir, &enemyJudge.inVThi, &enemyJudge.inVFou);
				ReadChessModel(&count, row, col, 1, 1, enemyColor, &sl);
				CheckChessModel(sl.a, &count, &enemyJudge.inLSFir, &enemyJudge.inLSThi, &enemyJudge.inLSFou);
				ReadChessModel(&count, row, col, 1, -1, enemyColor, &sl);
				CheckChessModel(sl.a, &count, &enemyJudge.inRSFir, &enemyJudge.inRSThi, &enemyJudge.inRSFou);

				if (enemyJudge.inHFir || enemyJudge.inVFir || enemyJudge.inLSFir || enemyJudge.inRSFir)
				{
					inEnemyFir = true;
				}
				if (enemyJudge.inHThi || enemyJudge.inVThi || enemyJudge.inLSThi || enemyJudge.inRSThi)
				{
					inEnemyThi = true;
				}
				if (enemyJudge.inHFou || enemyJudge.inVFou || enemyJudge.inLSFou || enemyJudge.inRSFou)
				{
					inEnemyFou = true;
				}
				if (enemyJudge.inHThi && (enemyJudge.inVThi || enemyJudge.inLSThi || enemyJudge.inRSThi) ||
					enemyJudge.inVThi && (enemyJudge.inHThi || enemyJudge.inLSThi || enemyJudge.inRSThi) ||
					enemyJudge.inLSThi && (enemyJudge.inHThi || enemyJudge.inVThi || enemyJudge.inRSThi) ||
					enemyJudge.inRSThi && (enemyJudge.inHThi || enemyJudge.inVThi || enemyJudge.inLSThi))
				{
					inEnemySec = true;
				}

				if ((inMyFir || inEnemyFir) && *firSize < MAX_FIR)
				{
					fir[*firSize].x = row;
					fir[*firSize].y = col;
					fir[*firSize].color = HIGHLIGHT_CHESS;
					(*firSize)++;
				}
				else if ((inMySec || inEnemySec) && *secSize < MAX_SEC)
				{
					sec[*secSize].x = row;
					sec[*secSize].y = col;
					sec[*secSize].color = MIDDLE_LIGHT_CHESS;
					(*secSize)++;
				}
				else if ((inMyThi || inEnemyThi) && *thiSize < MAX_THI)
				{
					thi[*thiSize].x = row;
					thi[*thiSize].y = col;
					thi[*thiSize].color = LIGHT_CHESS;
					(*thiSize)++;
				}
				else if ((inMyFou || inEnemyFou) && *fouSize < MAX_FOU)
				{
					fou[*fouSize].x = row;
					fou[*fouSize].y = col;
					fou[*fouSize].color = LIGHT_CHESS;
					(*fouSize)++;
				}
			}
		}
	}
	SeqListDestroy(&sl);
}

// 检测当前链表内的棋型，如果有连五或活四就判断可以属于第一优先级并返回，否则
// 判断是否有冲四或活三就判断可以属于第三优先级，判断是否有活二或眠三就判断可以属于第四优先级
void CheckChessModel(SLDataType* pSLa, int* count, bool* inFir, bool* inThi, bool* inFou)
{
	if (*count < 7)
	{
		*count = 1;
		return;
	}
	int key = 0;
	for (int i = 0; i < *count - 5; ++i)
	{
		key = Hash(pSLa + i);
		ChessModel judgeModel = evaluateHashTable[key].chessModel;
		if (judgeModel == LIAN_5 || judgeModel == HUO_4)
		{
			*inFir = true;
			*count = 1;
			return;
		}
		else if (judgeModel == CHONG_4 || judgeModel == HUO_3 || judgeModel == HUO_3_102 || judgeModel == HUO_3_201 ||
			judgeModel == CHONG_4_103 || judgeModel == CHONG_4_202 || judgeModel == CHONG_4_301 || judgeModel == HUN_401
			||
				judgeModel == HUN_302 || judgeModel == HUN_203 || judgeModel == HUN_104)
		{
			*inThi = true;
		}
		else if (judgeModel == HUO_2 || judgeModel == HUO_2_101 || judgeModel == MIAN_3 || judgeModel == MIAN_3_102 ||
			judgeModel == MIAN_3_201 || judgeModel == MIAN_3_1002 || judgeModel == MIAN_3_2001
			|| judgeModel == MIAN_3_10101 ||
			judgeModel == HUN_1003 || judgeModel == HUN_10102 || judgeModel == HUN_10201 || judgeModel == HUN_20101 ||
			judgeModel == HUN_3001)
		{
			*inFou = true;
		}
	}
	*count = 1;
}

// 检查当是否有连五，如果有就返回true，否则返回false
bool CheckFive(Point point)
{
	if (CheckFiveDirection(point, 1, 0, global.curPlayer.color)
		|| CheckFiveDirection(point, 0, 1, global.curPlayer.color) ||
		CheckFiveDirection(point, 1, 1, global.curPlayer.color)
		|| CheckFiveDirection(point, 1, -1, global.curPlayer.color))
	{
		return true;
	}
	return false;
}

// 检查某个方向上是否有连五
bool CheckFiveDirection(Point point, int offsetX, int offsetY, ChessColor color)
{
	int count = 1;
	int row = point.row;
	int col = point.col;
	// 向某个方向遍历，如果当前棋子颜色与所下颜色相同则count++，如果为空或遇到墙或为敌人棋子则break，
	for (int i = 1; i < 6; ++i)
	{
		int x = row - i * offsetX;
		int y = col - i * offsetY;
		if (x == -1 || x == BOARD_ROW || y == -1 || y == BOARD_COL)
		{
			break;
		}
		if (global.virtualBoard[x][y].color == color)
		{
			count++;
		}
		else
		{
			break;
		}
	}
	for (int i = 1; i < 6; ++i)
	{
		int x = row + i * offsetX;
		int y = col + i * offsetY;
		if (x == -1 || x == BOARD_ROW || y == -1 || y == BOARD_COL)
		{
			break;
		}
		if (global.virtualBoard[x][y].color == color)
		{
			count++;
		}
		else
		{
			break;
		}
	}
	if (count >= 5)
	{
		return true;
	}
	return false;
}

// 撤销在虚拟棋盘上的落子
void RevokeVirtualChess(Point point, int count, int pIntX[25], int pIntY[25])
{
	global.virtualBoard[point.row][point.col].color = VIRTUAL_CHESS;
	for (int i = 0; i < count; ++i)
	{
		global.virtualBoard[pIntX[i]][pIntY[i]].color = EMPTY_CHESS;
	}
	global.stepNumber--;
	StepExchange();
}

// 在虚拟棋盘上落子
void PutVirtualChess(Point point, int* pCount, int pIntX[25], int pIntY[25])
{
	global.virtualBoard[point.row][point.col].color = global.curPlayer.color;
	// 把当前位置周围八个方向上没有棋子的两个位置标记为虚拟棋子（用于AI算法）
	for (int i = point.row - 2; i <= point.row + 2; ++i)
	{
		for (int j = point.col - 2; j <= point.col + 2; ++j)
		{
			if (i >= 0 && i < BOARD_ROW && j >= 0 && j < BOARD_COL && global.virtualBoard[i][j].color == EMPTY_CHESS)
			{
				global.virtualBoard[i][j].color = VIRTUAL_CHESS;
				pIntX[*pCount] = i;
				pIntY[*pCount] = j;
				(*pCount)++;
			}
		}
	}
	global.stepNumber++;
	StepExchange();
}

// 评估当前局势
int evaluateSituation()
{
	int aiScore = 0;
	int playerScore = 0;
	// 遍历棋盘上的每个棋子，如果是空棋子或者虚拟棋子就跳过，否则评估该棋子的分数
	for (int row = 0; row < BOARD_ROW; ++row)
	{
		for (int col = 0; col < BOARD_COL; ++col)
		{
			if (global.virtualBoard[row][col].color == EMPTY_CHESS
				|| global.virtualBoard[row][col].color == VIRTUAL_CHESS)
			{
				continue;
			}

			int value = EvaluatePoint(row, col, global.virtualBoard[row][col].color);

			if (global.virtualBoard[row][col].color == global.AI.color)
			{
				aiScore += value;
			}
			else
			{
				playerScore += value;
			}
		}
	}
	// 返回AI分数减去玩家分数，彼此乘以不同的权重
	if(global.firstPlayer.color == global.AI.color)
	{
		return aiScore * LEAD_ATTACK_WEIGHT - playerScore * LEAD_DEFENSE_WEIGHT;
	}
	else
	{
		return aiScore * FOLLOW_ATTACK_WEIGHT - playerScore * FOLLOW_DEFENSE_WEIGHT;
	}
}

// 评估某个点的分数
int EvaluatePoint(int row, int col, ChessColor color)
{
	// 评估四个方向的分数
	int valueHorizontal = EvaluateDirection(row, col, 1, 0, color);
	int valueVertical = EvaluateDirection(row, col, 0, 1, color);
	int valueLeftSlant = EvaluateDirection(row, col, 1, 1, color);
	int valueRightSlant = EvaluateDirection(row, col, 1, -1, color);
	return valueHorizontal + valueVertical + valueLeftSlant + valueRightSlant;
}

// 评估某个方向的分数
int EvaluateDirection(int row, int col, int offsetX, int offsetY, ChessColor color)
{
	int count = 1;
	SL JudgeSl;
	SeqListInit(&JudgeSl);
	ReadChessModel(&count, row, col, offsetX, offsetY, color, &JudgeSl);

	// 根据顺序表中的棋型，计算当前方向的分数
	int score = EvaluateSL(JudgeSl.a, count);
	SeqListDestroy(&JudgeSl);
	return score;
}

SL ReadChessModel(int* pCount, int row, int col, int offsetX, int offsetY, ChessColor color, SL* sl)
{
	sl->size = 0;
	// 头插法存储棋型
	// 头插当前棋子
	SeqListPushFront(&*sl, 1);
	/* 读取棋型的序列
	   向某个方向遍历，如果当前棋子颜色与所下颜色相同则头插1存入顺序表，如果为空则头插0存入顺序表，
	   如果为敌方棋子或者超出边界则头插2或者遍历到第六个位置后从原本的位置向反方向遍历，
	   或者遍历到第六个位置后从原本的位置向反方向遍历，直到遇到敌方棋子或者边界
	*/
	for (int i = 1; i < 6; ++i)
	{
		int x = row - i * offsetX;
		int y = col - i * offsetY;
		if (x == -1 || x == BOARD_ROW || y == -1 || y == BOARD_COL)
		{
			SeqListPushFront(&*sl, 2);
			*pCount += 1;
			break;
		}
		if (global.virtualBoard[x][y].color == color)
		{
			SeqListPushFront(&*sl, 1);
		}
		else if (global.virtualBoard[x][y].color == EMPTY_CHESS || global.virtualBoard[x][y].color == VIRTUAL_CHESS)
		{
			SeqListPushFront(&*sl, 0);
		}
		else
		{
			SeqListPushFront(&*sl, 2);
			*pCount += 1;
			break;
		}
		*pCount += 1;
	}
	for (int i = 1; i < 6; ++i)
	{
		int x = row + i * offsetX;
		int y = col + i * offsetY;
		if (x == -1 || x == BOARD_ROW || y == -1 || y == BOARD_COL)
		{
			SeqListPushBack(&*sl, 2);
			*pCount += 1;
			break;
		}
		if (global.virtualBoard[x][y].color == color)
		{
			SeqListPushBack(&*sl, 1);
		}
		else if (global.virtualBoard[x][y].color == EMPTY_CHESS || global.virtualBoard[x][y].color == VIRTUAL_CHESS)
		{
			SeqListPushBack(&*sl, 0);
		}
		else
		{
			SeqListPushBack(&*sl, 2);
			*pCount += 1;
			break;
		}
		*pCount += 1;
	}
	return *sl;
}

// 评估某个棋型的分数
int EvaluateSL(SLDataType* pInt, int size)
{
	ChessModel models[6] = { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY };
	int key = 0;
	bool calculated = false;
	int score = 0;
	if (size < 7)
	{
		return 0;
	}
	else
	{
		for (int i = 0; i < size - 5; ++i)
		{
			key = Hash(pInt + i);
			if (evaluateHashTable[key].chessModel == EMPTY || evaluateHashTable[key].chessModel == MIAN_1)
			{
				continue;
			}
			// 避免重复计算
			for (int j = 0; j < 6; ++j)
			{
				if (evaluateHashTable[key].chessModel == models[j])
				{
					calculated = true;
					break;
				}
			}
			if (!calculated)
			{
				models[i] = evaluateHashTable[key].chessModel;
				score += evaluateHashTable[key].score;
			}
			else
			{
				score += evaluateHashTable[key].score / 3;
			}
			calculated = false;
		}
	}
	return score;
}

// 哈希函数
int Hash(SLDataType* pInt)
{
	if (pInt[5] == 2)
	{
		return pInt[5] * 32 + pInt[4] * 16 + pInt[3] * 8 + pInt[2] * 4 + pInt[1] * 2 + pInt[0];
	}
	else
	{
		return pInt[0] * 32 + pInt[1] * 16 + pInt[2] * 8 + pInt[3] * 4 + pInt[4] * 2 + pInt[5];
	}
}