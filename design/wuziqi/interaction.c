#include "interaction.h"
#include <raylib.h>
#include <stdlib.h>
#include "game.h"
#include "fontdata.h"
#include "interface.h"
#include "evaluate.h"
#include <stdio.h>

extern Global global;

// 处理菜单界面的点击
void HandleMenuClick()
{
	int x = GetMouseX();
	int y = GetMouseY();
	//如果鼠标点击在人机对战按钮上
	if (CheckCollisionPointRec((Vector2){ x, y },
		(Rectangle){ SCREEN_WIDTH / 2 - MENU_BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 - MENU_BUTTON_HEIGHT / 2 - 70,
					 MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT }))
	{
		// 用户选择了“人机对战”
		global.gameMode = PLAYER_VS_AI;
		global.gameState = SELECT_SIDE;
	}
	else if (CheckCollisionPointRec((Vector2){ x, y },
		(Rectangle){ SCREEN_WIDTH / 2 - MENU_BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 - MENU_BUTTON_HEIGHT / 2 + 20,
					 MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT }))
	{
		// 用户选择了“双人对战”
		global.gameMode = PLAYER_VS_PLAYER;
		global.gameState = PLAYING;
		global.prePlayerColor = global.player1.color = BLACK_CHESS;
		global.player2.color = WHITE_CHESS;
		global.curPlayer = global.firstPlayer = global.player1;
	}
}

// 处理选择界面的点击
void HandleSelectClick()
{
	int x = GetMouseX();
	int y = GetMouseY();
	//如果鼠标点击在先手按钮上
	if (CheckCollisionPointRec((Vector2){ x, y },
		(Rectangle){ SCREEN_WIDTH / 2 - MENU_BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 - MENU_BUTTON_HEIGHT / 2 - 70,
					 MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT }))
	{
		// 用户选择了先手
		global.prePlayerColor = global.player.color = BLACK_CHESS;
		global.AI.color = WHITE_CHESS;
		global.firstPlayer = global.player;
		global.gameState = PLAYING;
		global.curPlayer = global.player;
		global.stepNumber = 0;
	}
	else if (CheckCollisionPointRec((Vector2){ x, y },
		(Rectangle){ SCREEN_WIDTH / 2 - MENU_BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 - MENU_BUTTON_HEIGHT / 2 + 20,
					 MENU_BUTTON_WIDTH, MENU_BUTTON_HEIGHT }))
	{
		// 用户选择了后手
		global.prePlayerColor = global.player.color = WHITE_CHESS;
		global.AI.color = BLACK_CHESS;
		global.firstPlayer = global.AI;
		global.gameState = PLAYING;
		global.curPlayer = global.AI;
		global.stepNumber = 0;
	}
}

// 根据PVP游戏内的点击，更新游戏状态
void UpDatePVPGame()
{
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		int x = GetMouseX();
		int y = GetMouseY();
		//如果下棋位置在棋盘内
		if (CheckCollisionPointRec((Vector2){ x, y },
			(Rectangle){ START_X, START_Y, LINEAR_SPACING * 14, LINEAR_SPACING * 14 }))
		{
			if (global.finalClick != REPLAY)
			{
				//把鼠标点击的位置转换成棋盘上的位置
				int row =
					(x - START_X) % LINEAR_SPACING < LINEAR_SPACING / 2 ? (x - START_X) / LINEAR_SPACING :
					(x - START_X) / LINEAR_SPACING + 1;
				int col =
					(y - START_Y) % LINEAR_SPACING < LINEAR_SPACING / 2 ? (y - START_Y) / LINEAR_SPACING :
					(y - START_Y) / LINEAR_SPACING + 1;
				//如果下棋位置没有棋子
				if (global.gameBoard[row][col].color == EMPTY_CHESS)
				{
					//把棋子放在棋盘上
					global.gameBoard[row][col].color = global.curPlayer.color;
					global.lastCol = col;
					global.lastRow = row;
					//把棋子放在栈中
					Chess chess;
					chess.x = global.gameBoard[row][col].x;
					chess.y = global.gameBoard[row][col].y;
					chess.color = global.curPlayer.color;
					StackChessPush(&global.stackChess, chess);
					//记录上一位玩家并交换当前玩家
					global.prePlayerColor = global.curPlayer.color;
					StepExchange();
				}
			}
		}
			//如果点在返回主菜单
		else if ((CheckCollisionPointRec((Vector2){ x, y },
			(Rectangle){ 940, 310, 160, 50 })))
		{
			global.gameState = MENU;
			global.finalClick = CLICK_NONE;
			StackChessClear(&global.stackChess);
		}
			//如果点在悔棋
		else if ((CheckCollisionPointRec((Vector2){ x, y },
			(Rectangle){ 940, 400, 160, 50 })))
		{
			if (!StackChessEmpty(&global.stackChess))
			{
				Chess chess1 = StackChessPop(&global.stackChess);
				global.gameBoard[(chess1.x - START_CHESS_X) / LINEAR_SPACING][(chess1.y - START_CHESS_Y)
					/ LINEAR_SPACING].color = EMPTY_CHESS;
				// 读取上一步棋子的位置
				if (!StackChessEmpty(&global.stackChess))
				{
					Chess chess2 = StackChessTop(&global.stackChess);
					global.lastRow = (chess2.x - START_CHESS_X) / LINEAR_SPACING;
					global.lastCol = (chess2.y - START_CHESS_Y) / LINEAR_SPACING;
				}
				else
				{
					global.lastRow = global.lastCol = -1;
				}
				StepExchange();
				global.finalClick = CLICK_NONE;
			}
		}
			//如果点在认输,弹出新窗口，你输了！
		else if ((CheckCollisionPointRec((Vector2){ x, y },
			(Rectangle){ 940, 490, 160, 50 })))
		{
			global.gameState = GAME_OVER;
			global.gameResult = global.curPlayer.color == BLACK_CHESS ? WHITE_WIN : BLACK_WIN;
		}
			//如果点在重新开始
		else if ((CheckCollisionPointRec((Vector2){ x, y },
			(Rectangle){ 940, 580, 160, 50 })))
		{
			InitChessBoard();
			global.curPlayer = global.firstPlayer;
			StackChessClear(&global.stackChess);
			global.lastCol = global.lastRow = -1;
			global.finalClick = CLICK_NONE;
		}
			//如果点在退出
		else if ((CheckCollisionPointRec((Vector2){ x, y },
			(Rectangle){ 940, 670, 160, 50 })))
		{
			DoFinish();
			exit(-1);
		}
	}
}

// 根据pve游戏内的点击，更新游戏状态
void UpDatePVEGame()
{
	if (!IsAI())
	{
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			int x = GetMouseX();
			int y = GetMouseY();
			//如果下棋位置在棋盘内
			if (CheckCollisionPointRec((Vector2){ x, y },
				(Rectangle){ START_X, START_Y, LINEAR_SPACING * 14, LINEAR_SPACING * 14 }))
			{
				if (global.finalClick != REPLAY)
				{
					//把鼠标点击的位置转换成棋盘上的位置
					int row =
						(x - START_X) % LINEAR_SPACING < LINEAR_SPACING / 2 ? (x - START_X) / LINEAR_SPACING :
						(x - START_X) / LINEAR_SPACING + 1;
					int col =
						(y - START_Y) % LINEAR_SPACING < LINEAR_SPACING / 2 ? (y - START_Y) / LINEAR_SPACING :
						(y - START_Y) / LINEAR_SPACING + 1;
					//如果下棋位置没有棋子或者是虚拟棋子
					if (global.gameBoard[row][col].color == EMPTY_CHESS
						|| global.gameBoard[row][col].color == VIRTUAL_CHESS)
					{
						PutChess(row, col);
						//记录下棋者并交换棋手
						global.prePlayerColor = global.curPlayer.color;
						StepExchange();
					}
				}
			}
				//如果点在返回主菜单
			else if ((CheckCollisionPointRec((Vector2){ x, y },
				(Rectangle){ 940, 310, 160, 50 })))
			{
				global.gameState = MENU;
				global.finalClick = RESTART;
				StackChessClear(&global.stackChess);
				StackChessClear(&global.stackVirtualChess);
			}
				//如果点在悔棋
			else if ((CheckCollisionPointRec((Vector2){ x, y },
				(Rectangle){ 940, 400, 160, 50 })))
			{
				if (!StackChessEmpty(&global.stackChess))
				{
					RegretStepPVE();
				}
			}
				//如果点在认输,弹出新窗口，你输了！
			else if ((CheckCollisionPointRec((Vector2){ x, y },
				(Rectangle){ 940, 490, 160, 50 })))
			{
				global.gameState = GAME_OVER;
				global.gameResult = PLAYER_LOSE;
			}
				//如果点在重新开始
			else if ((CheckCollisionPointRec((Vector2){ x, y },
				(Rectangle){ 940, 580, 160, 50 })))
			{
				InitChessBoard();
				InitVirtualChessBoard();
				global.curPlayer = global.firstPlayer;
				StackChessClear(&global.stackChess);
				StackChessClear(&global.stackVirtualChess);
				global.lastCol = global.lastRow = -1;
				global.stepNumber = 0;
				global.finalClick = RESTART;
			}
				//如果点在退出
			else if ((CheckCollisionPointRec((Vector2){ x, y },
				(Rectangle){ 940, 670, 160, 50 })))
			{
				DoFinish();
				exit(-1);
			}
		}
	}
	else
	{
		// 如果是电脑的回合，就根据电脑的算法，更新游戏状态
		GetBestPoint();
		int row = global.bestPoint.row;
		int col = global.bestPoint.col;
		PutChess(row, col);
		//printf("AI: %d %d ------------------------------------\n", row, col);
		//记录下棋者并交换棋手
		global.prePlayerColor = global.curPlayer.color;
		StepExchange();
	}
}

// 悔棋操作
void RegretStepPVE()
{
	// 检查是否可以悔棋
	if (global.stackChess.size < 2)
	{
		global.finalClick = CLICK_NONE;
		return;
	}

	Chess chess = StackChessPop(&global.stackChess);
	global.gameBoard[(chess.x - START_CHESS_X) / LINEAR_SPACING][(chess.y - START_CHESS_Y) / LINEAR_SPACING].color =
		EMPTY_CHESS;
	global.virtualBoard[(chess.x - START_CHESS_X) / LINEAR_SPACING][(chess.y - START_CHESS_Y) / LINEAR_SPACING].color =
		VIRTUAL_CHESS;

	for (int i = 0; i < global.pushVirtualChessQuantity[global.stepNumber - 1]; ++i)
	{
		Chess virtualChess = StackChessPop(&global.stackVirtualChess);
		global.virtualBoard[(virtualChess.x - START_CHESS_X) / LINEAR_SPACING][(virtualChess.y - START_CHESS_Y)
			/ LINEAR_SPACING].color = EMPTY_CHESS;
	}

	global.stepNumber--;

	chess = StackChessPop(&global.stackChess);

	global.gameBoard[(chess.x - START_CHESS_X) / LINEAR_SPACING][(chess.y - START_CHESS_Y) / LINEAR_SPACING].color =
		EMPTY_CHESS;
	global.virtualBoard[(chess.x - START_CHESS_X) / LINEAR_SPACING][(chess.y - START_CHESS_Y) / LINEAR_SPACING].color =
		VIRTUAL_CHESS;

	for (int i = 0; i < global.pushVirtualChessQuantity[global.stepNumber - 1]; ++i)
	{
		Chess virtualChess = StackChessPop(&global.stackVirtualChess);
		global.virtualBoard[(virtualChess.x - START_CHESS_X) / LINEAR_SPACING][(virtualChess.y - START_CHESS_Y)
			/ LINEAR_SPACING].color = EMPTY_CHESS;
	}

	global.stepNumber--;

	// 读取上一步棋子的位置
	if (!StackChessEmpty(&global.stackChess))
	{
		Chess chess2 = StackChessTop(&global.stackChess);
		global.lastRow = (chess2.x - START_CHESS_X) / LINEAR_SPACING;
		global.lastCol = (chess2.y - START_CHESS_Y) / LINEAR_SPACING;
	}
	else
	{
		global.lastRow = global.lastCol = -1;
	}

	global.finalClick = CLICK_NONE;
}

// 下棋操作
void PutChess(int row, int col)
{
	//把棋子放在棋盘上
	global.gameBoard[row][col].color = global.curPlayer.color;
	global.lastCol = col;
	global.lastRow = row;
	//把棋子放在虚拟棋盘上
	global.virtualBoard[row][col].color = global.curPlayer.color;

	//把棋子放在栈中
	Chess chess;
	chess.x = global.gameBoard[row][col].x;
	chess.y = global.gameBoard[row][col].y;
	chess.color = global.curPlayer.color;
	StackChessPush(&global.stackChess, chess);

	int count = 0;
	if(global.stepNumber <= 4)
	{
		//把虚拟棋盘上该棋子周围八个方向上没有棋子的两个位置标记为虚拟棋子（用于AI算法）
		for (int i = row - 1; i <= row + 1; ++i)
		{
			for (int j = col - 1; j <= col + 1; ++j)
			{
				if (i >= 0 && i < BOARD_ROW && j >= 0 && j < BOARD_COL && global.virtualBoard[i][j].color == EMPTY_CHESS)
				{
					global.virtualBoard[i][j].color = VIRTUAL_CHESS;
					Chess virtualChess;
					virtualChess.x = global.virtualBoard[i][j].x;
					virtualChess.y = global.virtualBoard[i][j].y;
					virtualChess.color = VIRTUAL_CHESS;
					StackChessPush(&global.stackVirtualChess, virtualChess);
					count++;
				}
			}
		}
	}
	else
	{
		//把虚拟棋盘上该棋子周围八个方向上没有棋子的两个位置标记为虚拟棋子（用于AI算法）
		for (int i = row - 2; i <= row + 2; ++i)
		{
			for (int j = col - 2; j <= col + 2; ++j)
			{
				if (i >= 0 && i < BOARD_ROW && j >= 0 && j < BOARD_COL && global.virtualBoard[i][j].color == EMPTY_CHESS)
				{
					global.virtualBoard[i][j].color = VIRTUAL_CHESS;
					Chess virtualChess;
					virtualChess.x = global.virtualBoard[i][j].x;
					virtualChess.y = global.virtualBoard[i][j].y;
					virtualChess.color = VIRTUAL_CHESS;
					StackChessPush(&global.stackVirtualChess, virtualChess);
					count++;
				}
			}
		}
	}
	//记录该步棋子周围八个方向上没有棋子的两个位置的数量
	global.pushVirtualChessQuantity[global.stepNumber] = count;
	global.stepNumber++;
}

// 游戏结束后，弹出游戏结束窗口，根据玩家选择的操作，返回相应的操作
GameClick GameOverWindow()
{
	//创建一个新结束窗口
	InitWindow(GAME_OVER_WIDTH, GAME_OVER_HEIGHT, "结束");
	SetTargetFPS(60);
	static int count = 0;
	if (count == 0)
	{
		global.fontChi = LoadAndGetFont();
		count++;
	}
	while (!WindowShouldClose())
	{
		DrawGameOverMenu();
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			// 处理游戏结束窗口的点击
			GameClick gameOverClick = HandleGameOverClick();
			count = 0;
			return gameOverClick;
		}
		BeginDrawing();
		ClearBackground(RAYWHITE);
		EndDrawing();
	}
	count = 0;

	BeginDrawing();
	ClearBackground(RAYWHITE);
	EndDrawing();

	CloseWindow(); // 关闭窗口和OpenGL渲染上下文
	UnloadFontAndImg();
	MyUnloadFontData(global.fontChi);
	InitAndLoadImgFont();

	global.gameResult = UNFINISHED;
	global.gameState = PLAYING;
	global.finalClick = RESTART;
	global.fontChi = LoadAndGetFont();
	return REPLAY;
}

// 处理游戏结束窗口的点击
GameClick HandleGameOverClick()
{
	int x = GetMouseX();
	int y = GetMouseY();
	//如果鼠标点击在重新开始按钮上
	if (CheckCollisionPointRec((Vector2){ x, y },
		(Rectangle){ GAME_OVER_WIDTH / 2 - GAME_OVER_BUTTON_WIDTH / 2,
					 GAME_OVER_HEIGHT / 2 - GAME_OVER_BUTTON_HEIGHT / 2 - 50,
					 GAME_OVER_BUTTON_WIDTH, GAME_OVER_BUTTON_HEIGHT }))
	{
		if (global.gameMode == PLAYER_VS_AI)
		{
			InitVirtualChessBoard();
			StackChessClear(&global.stackVirtualChess);
		}
		InitChessBoard();
		global.curPlayer = global.firstPlayer;
		StackChessClear(&global.stackChess);
		global.gameResult = UNFINISHED;
		global.gameState = PLAYING;
		global.lastRow = global.lastCol = -1;
		global.stepNumber = 0;

		BeginDrawing();
		ClearBackground(RAYWHITE);
		EndDrawing();
		CloseWindow();

		UnloadFontAndImg();
		MyUnloadFontData(global.fontChi);

		InitAndLoadImgFont();
		global.fontChi = LoadAndGetFont();
		DrawBoard();
		DrawBoardChar();
		return RESTART;
	}
		//如果鼠标点击在退出按钮上
	else if (CheckCollisionPointRec((Vector2){ x, y },
		(Rectangle){ GAME_OVER_WIDTH / 2 - GAME_OVER_BUTTON_WIDTH / 2,
					 GAME_OVER_HEIGHT / 2 - GAME_OVER_BUTTON_HEIGHT / 2 + 150,
					 GAME_OVER_BUTTON_WIDTH, GAME_OVER_BUTTON_HEIGHT }))
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		EndDrawing();

		CloseWindow();
		DoFinish();
		exit(-1);
	}
		//如果鼠标点击在返回主菜单按钮上
	else if (CheckCollisionPointRec((Vector2){ x, y },
		(Rectangle){ GAME_OVER_WIDTH / 2 - GAME_OVER_BUTTON_WIDTH / 2,
					 GAME_OVER_HEIGHT / 2 - GAME_OVER_BUTTON_HEIGHT / 2 + 50,
					 GAME_OVER_BUTTON_WIDTH, GAME_OVER_BUTTON_HEIGHT }))
	{
		global.gameResult = UNFINISHED;

		BeginDrawing();
		ClearBackground(RAYWHITE);
		EndDrawing();

		CloseWindow();

		MyUnloadFontData(global.fontChi);
		UnloadFontAndImg();

		InitAndLoadImgFont();
		StackChessClear(&global.stackChess);
		global.fontChi = LoadAndGetFont();
		global.gameState = MENU;
		return RETURN_MENU;
	}
	else
	{
		return CLICK_NONE;
	}
}

// 交换玩家的操作
void StepExchange()
{
	// 如果是玩家对战，就交换玩家
	if (global.gameMode == PLAYER_VS_PLAYER)
	{
		if (global.curPlayer.color == global.player1.color)
		{
			global.curPlayer = global.player2;
		}
		else
		{
			global.curPlayer = global.player1;
		}
	}
	// 如果是玩家对战AI，就交换玩家
	else
	{
		if (global.curPlayer.color == global.AI.color)
		{
			global.curPlayer = global.player;
		}
		else
		{
			global.curPlayer = global.AI;
		}
	}
}

// 判断当前棋手是否是AI
bool IsAI()
{
	return global.curPlayer.color == global.AI.color;
}
