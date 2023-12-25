
#include <raylib.h>
#include "fontdata.h"
#include "game.h"
#include "interface.h"
#include "interaction.h"
#include "evaluate.h"

Global global;

// 初始化游戏
void InitGame()
{
	InitAndLoadImgFont();
	InitChessBoard();
	InitVirtualChessBoard();
	global.gameState = MENU; // 默认回到菜单界面
	global.gameResult = UNFINISHED;
	global.finalClick = CLICK_NONE;
	StackChessInit(&global.stackChess);
	StackChessInit(&global.stackVirtualChess);
}

// 初始化五子棋棋盘
void InitChessBoard()
{
	for (int row = 0; row < BOARD_ROW; ++row)
	{
		for (int col = 0; col < BOARD_COL; ++col)
		{
			global.gameBoard[row][col].x = START_CHESS_X + row * LINEAR_SPACING;
			global.gameBoard[row][col].y = START_CHESS_Y + col * LINEAR_SPACING;
			global.gameBoard[row][col].color = EMPTY_CHESS;
		}
	}
}

// 初始化虚拟棋盘
void InitVirtualChessBoard()
{
	for (int row = 0; row < BOARD_ROW; ++row)
	{
		for (int col = 0; col < BOARD_COL; ++col)
		{
			global.virtualBoard[row][col].x = START_CHESS_X + row * LINEAR_SPACING;
			global.virtualBoard[row][col].y = START_CHESS_Y + col * LINEAR_SPACING;
			global.virtualBoard[row][col].color = EMPTY_CHESS;
		}
	}
}

// 菜单窗口处理
void MenuWindow()
{
	InitChessBoard();
	InitVirtualChessBoard();
	global.lastCol = global.lastRow = -1;
	static int count = 0;
	if (count == 0)
	{
		global.fontChi = LoadAndGetFont();
		count++;
	}
	DrawMenu();
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		//根据鼠标点击的位置，处理菜单点击事件，改变游戏状态
		HandleMenuClick();
	}
}

// 选择先手窗口处理
void SelectSideWindow()
{
	DrawSelectSideMenu();

	// 处理菜单点击事件
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		//根据鼠标点击的位置，处理先手选择菜单点击事件，改变游戏状态
		HandleSelectClick();
		if (global.gameState != MENU)
		{
			return;
		}
	}
}

// 玩家对战窗口处理
void GamePVP()
{
	static int count = 0;
	if (count == 0)
	{
		global.fontChi = LoadAndGetFont();
		count++;
	}
	DrawBox();
	DrawChess();
	// 只要不是复盘状态，直接就更新游戏结果
	if (global.finalClick != REPLAY && global.lastRow != -1 && global.lastCol != -1)
	{
		global.gameResult = UpdateGameResult(global.prePlayerColor);
	}
	//如果游戏结束，就修改游戏状态为结束，否则就更新游戏
	if (global.gameResult != UNFINISHED && global.finalClick != REPLAY)
	{
		global.gameState = GAME_OVER;
	}
	else
	{
		UpDatePVPGame();
	}
}

// 人机对战窗口处理
void GamePVE()
{
	static int count = 0;
	if (count == 0)
	{
		global.fontChi = LoadAndGetFont();
		count++;
	}
	DrawBox();
	// 只要不是复盘状态，直接就更新游戏结果
	if (global.finalClick != REPLAY && global.lastRow != -1 && global.lastCol != -1)
	{
		global.gameResult = UpdateGameResult(global.prePlayerColor);
	}
	//如果游戏结束，就修改游戏状态为结束，否则就更新游戏
	if (global.gameResult != UNFINISHED && global.finalClick != REPLAY)
	{
		global.gameState = GAME_OVER;
	}
	else
	{
		UpDatePVEGame();
	}
	DrawChess();
}

// 更新游戏状态
void UpDateGameState()
{
	switch (global.gameState)
	{
	case MENU:
		// 如果菜单窗口已经准备好，就画菜单，并处理菜单点击
		if (IsWindowReadyForMenu())
		{
			MenuWindow();
		}
		break;
	case SELECT_SIDE:
		// 如果先手选择窗口已经准备好，就画选择界面，并处理选择界面点击
		if (IsWindowReadyForSelect())
		{
			SelectSideWindow();
		}
		break;
	case PLAYING:
		// 如果游戏窗口已经准备好（PVP），就画游戏界面，并处理游戏界面点击
		if (IsWindowReadyForPVP())
		{
			GamePVP();
		}
		else if (IsWindowReadyForPVE())
		{
			GamePVE();
		}
		break;
	case GAME_OVER:
		DrawChess();
		BeginDrawing();
		EndDrawing();
		//获取游戏结束时的点击选择，主要目的是为了处理复盘
		global.finalClick = GameOverWindow();
	default:
		break;
	}
}

// 更新游戏结果
GameResult UpdateGameResult(ChessColor curChessColor)
{
	//判断是否有五子连珠
	Point point = { global.lastRow, global.lastCol };
	if(CheckFiveInGame(point))
	{
		if(global.gameMode == PLAYER_VS_PLAYER)
		{
			if (global.gameBoard[global.lastRow][global.lastCol].color == BLACK_CHESS)
			{
				return BLACK_WIN;
			}
			else
			{
				return WHITE_WIN;
			}
		}
		else
		{
			if (global.gameBoard[global.lastRow][global.lastCol].color == global.player.color)
			{
				return PLAYER_WIN;
			}
			else
			{
				return PLAYER_LOSE;
			}
		}
	}


	int row, col;
	//反向判断是否平局
	for (row = 0; row < BOARD_ROW; row++)
	{
		for (col = 0; col < BOARD_COL; col++)
		{
			if (global.gameBoard[row][col].color == EMPTY_CHESS)
			{
				return UNFINISHED;
			}
		}
	}
	return DRAW;
}

// 检查某个方向是否有五子连珠
bool CheckFiveDirectionInGame(Point point, int offsetX, int offsetY)
{
	int count = 1;
	int row = point.row;
	int col = point.col;
	ChessColor color = global.gameBoard[row][col].color;
	// 从当前位置向两个方向遍历，如果遇到相同颜色的棋子，就count++，否则就退出循环
	while (1)
	{
		row += offsetX;
		col += offsetY;
		if (row < 0 || row >= BOARD_ROW || col < 0 || col >= BOARD_COL)
		{
			break;
		}
		if (global.gameBoard[row][col].color == color)
		{
			count++;
		}
		else
		{
			break;
		}
	}
	row = point.row;
	col = point.col;
	while (1)
	{
		row -= offsetX;
		col -= offsetY;
		if (row < 0 || row >= BOARD_ROW || col < 0 || col >= BOARD_COL)
		{
			break;
		}
		if (global.gameBoard[row][col].color == color)
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

// 检查是否有五子连珠
bool CheckFiveInGame(Point point)
{
	//判断是否有五子连珠
	if (CheckFiveDirectionInGame(point, 1, 0) ||
		CheckFiveDirectionInGame(point, 0, 1) ||
		CheckFiveDirectionInGame(point, 1, 1) ||
		CheckFiveDirectionInGame(point, 1, -1))
	{
		return true;
	}
	return false;
}

// 结束操作
void DoFinish()
{
	// 释放字体和图片
	UnloadFontAndImg();
	StackChessDestroy(&global.stackChess);
	StackChessDestroy(&global.stackVirtualChess);
}
