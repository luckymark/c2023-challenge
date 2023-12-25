#include <raylib.h>
#include <stdio.h>
#include "game.h"
#include "fontdata.h"

extern Global global;

// 画棋盘
void DrawBoard()
{
	//有立体感的棋盘
	DrawTexture(global.imageChessBoard, 0, 0, WHITE);
	//有立体感的棋盘格子
	for (int i = 0; i < 15; ++i)
	{
		DrawRectangle(START_X + LINEAR_SPACING * i, START_Y, 2, 840, BLACK);
		DrawRectangle(START_X, START_Y + LINEAR_SPACING * i, 840, 2, BLACK);
	}
	//增加棋盘上的点
	DrawCircle(START_X + LINEAR_SPACING * 3, START_Y + LINEAR_SPACING * 3, 5, BLACK);
	DrawCircle(START_X + LINEAR_SPACING * 3, START_Y + LINEAR_SPACING * 11, 5, BLACK);
	DrawCircle(START_X + LINEAR_SPACING * 11, START_Y + LINEAR_SPACING * 3, 5, BLACK);
	DrawCircle(START_X + LINEAR_SPACING * 11, START_Y + LINEAR_SPACING * 11, 5, BLACK);
	DrawCircle(START_X + LINEAR_SPACING * 7, START_Y + LINEAR_SPACING * 7, 5, BLACK);

	char buffer[10];
	// 输出棋盘左侧数字
	for (int i = BOARD_COL; i > 0; --i)
	{
		sprintf(buffer, "%d", i);
		DrawTextEx(global.fontFigures, buffer, (Vector2){ 25, 950 - 60 * i }, 30, 2, BLACK);
	}
	// 棋盘下方输出大写字母从A到O
	for (int i = 0; i < BOARD_ROW; ++i)
	{
		sprintf(buffer, "%c", 'A' + i);
		DrawTextEx(global.fontEng, buffer, (Vector2){ 60 + 60 * i, 920 }, 30, 2, BLACK);
	}

	//棋盘右侧中间部分，屏幕范围内增加按键：悔棋、认输、重新开始、返回主菜单,退出;画没有棱角的矩形
	DrawRectangleRounded((Rectangle){ BUTTON_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT }, 0.5f, 0, BUTTON_COLOR);
	DrawRectangleRounded((Rectangle){ BUTTON_X, BUTTON_Y + BUTTON_SPACING, BUTTON_WIDTH, BUTTON_HEIGHT },
		0.5f,
		0,
		BUTTON_COLOR);
	DrawRectangleRounded((Rectangle){ BUTTON_X, BUTTON_Y + 2 * BUTTON_SPACING, BUTTON_WIDTH, BUTTON_HEIGHT },
		0.5f,
		0,
		BUTTON_COLOR);
	DrawRectangleRounded((Rectangle){ BUTTON_X, BUTTON_Y + 3 * BUTTON_SPACING, BUTTON_WIDTH, BUTTON_HEIGHT },
		0.5f,
		0,
		BUTTON_COLOR);
	DrawRectangleRounded((Rectangle){ BUTTON_X, BUTTON_Y + 4 * BUTTON_SPACING, BUTTON_WIDTH, BUTTON_HEIGHT },
		0.5f,
		0,
		BUTTON_COLOR);

	//在矩形按键一圈外面描边
	DrawRectangleRoundedLines((Rectangle){ BUTTON_X, BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT }, 0.5f, 0, 1, BLACK);
	DrawRectangleRoundedLines((Rectangle){ BUTTON_X, BUTTON_Y + BUTTON_SPACING, BUTTON_WIDTH, BUTTON_HEIGHT },
		0.5f,
		0,
		1,
		BLACK);
	DrawRectangleRoundedLines((Rectangle){ BUTTON_X, BUTTON_Y + 2 * BUTTON_SPACING, BUTTON_WIDTH, BUTTON_HEIGHT },
		0.5f,
		0,
		1,
		BLACK);
	DrawRectangleRoundedLines((Rectangle){ BUTTON_X, BUTTON_Y + 3 * BUTTON_SPACING, BUTTON_WIDTH, BUTTON_HEIGHT },
		0.5f,
		0,
		1,
		BLACK);
	DrawRectangleRoundedLines((Rectangle){ BUTTON_X, BUTTON_Y + 4 * BUTTON_SPACING, BUTTON_WIDTH, BUTTON_HEIGHT },
		0.5f,
		0,
		1,
		BLACK);
}

// 画棋盘上的文字
void DrawBoardChar()
{
	DrawTextEx(global.fontChi, "五子棋", (Vector2){ 960, 50 }, 50, 0, BLACK);
	DrawTextEx(global.fontChi, "返回主菜单", (Vector2){ 945, 320 }, 30, 0, BLACK);
	DrawTextEx(global.fontChi, "悔棋", (Vector2){ 990, 410 }, 30, 0, BLACK);
	DrawTextEx(global.fontChi, "认输", (Vector2){ 990, 500 }, 30, 0, BLACK);
	DrawTextEx(global.fontChi, "重新开始", (Vector2){ 960, 590 }, 30, 0, BLACK);
	DrawTextEx(global.fontChi, "退出", (Vector2){ 990, 680 }, 30, 0, BLACK);
}

// 画棋盘上的棋盒
void DrawBox()
{
	if (global.gameMode == PLAYER_VS_PLAYER)
	{
		if (global.player.color == BLACK_CHESS)
		{
			DrawTexture(global.imageChessBoxBlack, 950, 150, WHITE);
			DrawTexture(global.imageChessBoxWhite, 930, 770, WHITE);
		}
		else
		{
			DrawTexture(global.imageChessBoxWhite, 930, 150, WHITE);
			DrawTexture(global.imageChessBoxBlack, 950, 770, WHITE);
		}
	}
	else if (global.gameMode == PLAYER_VS_AI)
	{
		if (global.player1.color == BLACK_CHESS)
		{
			DrawTexture(global.imageChessBoxBlack, 950, 150, WHITE);
			DrawTexture(global.imageChessBoxWhite, 930, 770, WHITE);
		}
		else
		{
			DrawTexture(global.imageChessBoxWhite, 930, 150, WHITE);
			DrawTexture(global.imageChessBoxBlack, 950, 770, WHITE);
		}
	}
}

// 画棋盘上的棋子
void DrawChess()
{

	// 在最后的棋子周围画一个围绕棋子的圆圈用于提示
	if (global.lastRow != -1 && global.lastCol != -1)
		DrawCircle(global.gameBoard[global.lastRow][global.lastCol].x + 28,
			global.gameBoard[global.lastRow][global.lastCol].y + 28, 29, WHITE);

	for (int row = 0; row < BOARD_ROW; ++row)
	{
		for (int col = 0; col < BOARD_COL; ++col)
		{
			if (global.gameBoard[row][col].color == BLACK_CHESS)
			{
				DrawTexture(global.imageBlackChess, global.gameBoard[row][col].x, global.gameBoard[row][col].y, WHITE);
			}
			else if (global.gameBoard[row][col].color == WHITE_CHESS)
			{
				DrawTexture(global.imageWhiteChess, global.gameBoard[row][col].x, global.gameBoard[row][col].y, WHITE);
			}
		}
	}

}

bool IsWindowReadyForSelect()
{
	return !IsWindowHidden() && (global.gameState == SELECT_SIDE);
}
bool IsWindowReadyForMenu()
{
	return !IsWindowHidden() && (global.gameState == MENU);
}
bool IsWindowReadyForPVP()
{
	return !IsWindowHidden() && (global.gameState == PLAYING) && global.gameMode == PLAYER_VS_PLAYER;
}
bool IsWindowReadyForPVE()
{
	return !IsWindowHidden() && (global.gameState == PLAYING) && global.gameMode == PLAYER_VS_AI;
}

void InitAndLoadImgFont()
{
	static const char imageChessBoardPath[] = "./chessBoard2.png";
	static const char imageWhiteChessPath[] = "./whiteChess.png";
	static const char imageBlackChessPath[] = "./blackChess.png";
	static const char imageChessBoxBlackPath[] =
		"./chessBoxBlack.png";
	static char imageChessBoxWhitePath[] =
		"./chessBoxWhite.png";
	static const char fontEngPath[] = "C:\\Windows\\Fonts\\segoeuib.ttf";
	static const char fontFiguresPath[] = "C:\\Windows\\Fonts\\COOPBL.TTF";

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "五子棋");
	SetTargetFPS(60);
	//读取字体
	global.fontEng = LoadFont(fontEngPath);
	global.fontFigures = LoadFont(fontFiguresPath);
	//读取图片
	global.imageChessBoard = LoadTexture(imageChessBoardPath);
	global.imageChessBoxWhite = LoadTexture(imageChessBoxWhitePath);
	global.imageChessBoxBlack = LoadTexture(imageChessBoxBlackPath);
	global.imageBlackChess = LoadTexture(imageBlackChessPath);
	global.imageWhiteChess = LoadTexture(imageWhiteChessPath);
}

// 释放字体和图片
void UnloadFontAndImg()
{
	UnloadTexture(global.imageChessBoard);
	UnloadTexture(global.imageChessBoxWhite);
	UnloadTexture(global.imageChessBoxBlack);
	UnloadTexture(global.imageBlackChess);
	UnloadTexture(global.imageWhiteChess);
	UnloadFont(global.fontEng);
	UnloadFont(global.fontFigures);
}

// 画菜单界面
void DrawMenu()
{

	//画一个菜单
	//--------------------------------------------------------------------------------------
	DrawRectangle(SCREEN_WIDTH / 2 - MENU_WIDTH / 2,
		SCREEN_HEIGHT / 2 - MENU_WIDTH / 2,
		MENU_WIDTH,
		MENU_HEIGHT,
		MENU_COLOR);
	DrawRectangleLines(SCREEN_WIDTH / 2 - MENU_WIDTH / 2,
		SCREEN_HEIGHT / 2 - MENU_WIDTH / 2,MENU_WIDTH,MENU_HEIGHT,BLACK);
	DrawRectangleRounded((Rectangle){ SCREEN_WIDTH / 2 - MENU_BUTTON_WIDTH / 2,
									  SCREEN_HEIGHT / 2 - MENU_BUTTON_HEIGHT / 2 - 70, MENU_BUTTON_WIDTH,
									  MENU_BUTTON_HEIGHT },
		0.5f, 0, BUTTON_COLOR);
	DrawRectangleRounded((Rectangle){ SCREEN_WIDTH / 2 - MENU_BUTTON_WIDTH / 2,
									  SCREEN_HEIGHT / 2 - MENU_BUTTON_HEIGHT / 2 + 20, MENU_BUTTON_WIDTH,
									  MENU_BUTTON_HEIGHT },
		0.5f, 0, BUTTON_COLOR);
	// 给两个按钮描边
	DrawRectangleRoundedLines((Rectangle){ SCREEN_WIDTH / 2 - MENU_BUTTON_WIDTH / 2,
										   SCREEN_HEIGHT / 2 - MENU_BUTTON_HEIGHT / 2 - 70, MENU_BUTTON_WIDTH,
										   MENU_BUTTON_HEIGHT },
		0.5f, 0, 1, BLACK);
	DrawRectangleRoundedLines((Rectangle){ SCREEN_WIDTH / 2 - MENU_BUTTON_WIDTH / 2,
										   SCREEN_HEIGHT / 2 - MENU_BUTTON_HEIGHT / 2 + 20, MENU_BUTTON_WIDTH,
										   MENU_BUTTON_HEIGHT },
		0.5f, 0, 1, BLACK);
	DrawTextEx(global.fontChi, "请选择！",
		(Vector2){ SCREEN_WIDTH / 2 - MENU_BUTTON_WIDTH / 2, SCREEN_HEIGHT / 2 - MENU_BUTTON_HEIGHT / 2 - 140 },
		50, 2, BLACK);
	DrawTextEx(global.fontChi, "人机对战",
		(Vector2){ SCREEN_WIDTH / 2 - MENU_BUTTON_WIDTH / 2 + 20, SCREEN_HEIGHT / 2 - MENU_BUTTON_HEIGHT / 2 - 60 },
		30, 0, BLACK);
	DrawTextEx(global.fontChi, "双人对战",
		(Vector2){ SCREEN_WIDTH / 2 - MENU_BUTTON_WIDTH / 2 + 20, SCREEN_HEIGHT / 2 - MENU_BUTTON_HEIGHT / 2 + 30 },
		30, 0, BLACK);
	//--------------------------------------------------------------------------------------

}

// 画选择先手界面
void DrawSelectSideMenu()
{
	static int count = 0;
	if (count == 0)
	{
		global.fontChi = LoadAndGetFont();
		count++;
	}
	//画一个菜单
	//--------------------------------------------------------------------------------------
	DrawRectangle(SCREEN_WIDTH / 2 - MENU_WIDTH / 2,
		SCREEN_HEIGHT / 2 - MENU_WIDTH / 2,
		MENU_WIDTH,
		MENU_HEIGHT,
		MENU_COLOR);
	DrawRectangleRounded((Rectangle){ SCREEN_WIDTH / 2 - MENU_BUTTON_WIDTH / 2,
									  SCREEN_HEIGHT / 2 - MENU_BUTTON_HEIGHT / 2 - 70, MENU_BUTTON_WIDTH,
									  MENU_BUTTON_HEIGHT },
		0.5f, 0, BUTTON_COLOR);
	DrawRectangleRounded((Rectangle){ SCREEN_WIDTH / 2 - MENU_BUTTON_WIDTH / 2,
									  SCREEN_HEIGHT / 2 - MENU_BUTTON_HEIGHT / 2 + 20, MENU_BUTTON_WIDTH,
									  MENU_BUTTON_HEIGHT },
		0.5f, 0, BUTTON_COLOR);
	// 给两个按钮和菜单描边
	DrawRectangleRoundedLines((Rectangle){ SCREEN_WIDTH / 2 - MENU_BUTTON_WIDTH / 2,
										   SCREEN_HEIGHT / 2 - MENU_BUTTON_HEIGHT / 2 - 70, MENU_BUTTON_WIDTH,
										   MENU_BUTTON_HEIGHT },
		0.5f, 0, 1, BLACK);
	DrawRectangleRoundedLines((Rectangle){ SCREEN_WIDTH / 2 - MENU_BUTTON_WIDTH / 2,
										   SCREEN_HEIGHT / 2 - MENU_BUTTON_HEIGHT / 2 + 20, MENU_BUTTON_WIDTH,
										   MENU_BUTTON_HEIGHT },
		0.5f, 0, 1, BLACK);
	DrawRectangleLines(SCREEN_WIDTH / 2 - MENU_WIDTH / 2,
		SCREEN_HEIGHT / 2 - MENU_WIDTH / 2,MENU_WIDTH,MENU_HEIGHT,BLACK);
	DrawTextEx(global.fontChi, "请选择您先手还是后手",
		(Vector2){ SCREEN_WIDTH / 2 - MENU_BUTTON_WIDTH / 2 - 70, SCREEN_HEIGHT / 2 - MENU_BUTTON_HEIGHT / 2 - 140 },
		30, 2, BLACK);
	DrawTextEx(global.fontChi, "先手",
		(Vector2){ SCREEN_WIDTH / 2 - MENU_BUTTON_WIDTH / 2 + 50, SCREEN_HEIGHT / 2 - MENU_BUTTON_HEIGHT / 2 - 60 },
		30, 0, BLACK);
	DrawTextEx(global.fontChi, "后手",
		(Vector2){ SCREEN_WIDTH / 2 - MENU_BUTTON_WIDTH / 2 + 50, SCREEN_HEIGHT / 2 - MENU_BUTTON_HEIGHT / 2 + 30 },
		30, 0, BLACK);
	//--------------------------------------------------------------------------------------
}

// 画游戏结束界面
void DrawGameOverMenu()
{
	DrawRectangle(0, 0, GAME_OVER_WIDTH, GAME_OVER_HEIGHT, MENU_COLOR);

	//重新开始的按钮
	DrawRectangleRounded((Rectangle){ GAME_OVER_WIDTH / 2 - GAME_OVER_BUTTON_WIDTH / 2,
									  GAME_OVER_HEIGHT / 2 - GAME_OVER_BUTTON_HEIGHT / 2 - 50,
									  GAME_OVER_BUTTON_WIDTH, GAME_OVER_BUTTON_HEIGHT },
		0.5f, 0, (Color){ 160, 82, 45, 255 });
	//返回主菜单的按钮
	DrawRectangleRounded((Rectangle){ GAME_OVER_WIDTH / 2 - GAME_OVER_BUTTON_WIDTH / 2,
									  GAME_OVER_HEIGHT / 2 - GAME_OVER_BUTTON_HEIGHT / 2 + 50,
									  GAME_OVER_BUTTON_WIDTH, GAME_OVER_BUTTON_HEIGHT },
		0.5f, 0, (Color){ 160, 82, 45, 255 });
	//退出的按钮
	DrawRectangleRounded((Rectangle){ GAME_OVER_WIDTH / 2 - GAME_OVER_BUTTON_WIDTH / 2,
									  GAME_OVER_HEIGHT / 2 - GAME_OVER_BUTTON_HEIGHT / 2 + 150,
									  GAME_OVER_BUTTON_WIDTH, GAME_OVER_BUTTON_HEIGHT },
		0.5f, 0, (Color){ 160, 82, 45, 255 });
	//输出结果
	if (global.gameResult == BLACK_WIN)
	{
		DrawTextEx(global.fontChi, "黑棋胜利！", (Vector2){ GAME_OVER_WIDTH / 2 - GAME_OVER_BUTTON_WIDTH / 2 + 20,
														   GAME_OVER_HEIGHT / 2 - GAME_OVER_BUTTON_HEIGHT / 2 - 140 },
			50, 0, BLACK);
	}
	else if (global.gameResult == WHITE_WIN)
	{
		DrawTextEx(global.fontChi, "白棋胜利！", (Vector2){ GAME_OVER_WIDTH / 2 - GAME_OVER_BUTTON_WIDTH / 2 + 20,
														   GAME_OVER_HEIGHT / 2 - GAME_OVER_BUTTON_HEIGHT / 2 - 140 },
			50, 0, BLACK);
	}
	else if (global.gameResult == DRAW)
	{
		DrawTextEx(global.fontChi, "平局！", (Vector2){ GAME_OVER_WIDTH / 2 - GAME_OVER_BUTTON_WIDTH / 2 + 60,
													   GAME_OVER_HEIGHT / 2 - GAME_OVER_BUTTON_HEIGHT / 2 - 140 },
			50, 0, BLACK);
	}
	else if (global.gameResult == PLAYER_WIN)
	{
		DrawTextEx(global.fontChi, "你赢了！", (Vector2){ GAME_OVER_WIDTH / 2 - GAME_OVER_BUTTON_WIDTH / 2 + 40,
														 GAME_OVER_HEIGHT / 2 - GAME_OVER_BUTTON_HEIGHT / 2 - 140 },
			50, 0, BLACK);
	}
	else if (global.gameResult == PLAYER_LOSE)
	{
		DrawTextEx(global.fontChi, "你输了！", (Vector2){ GAME_OVER_WIDTH / 2 - GAME_OVER_BUTTON_WIDTH / 2 + 40,
														 GAME_OVER_HEIGHT / 2 - GAME_OVER_BUTTON_HEIGHT / 2 - 140 },
			50, 0, BLACK);
	}
	DrawTextEx(global.fontChi, "重新开始", (Vector2){ GAME_OVER_WIDTH / 2 - GAME_OVER_BUTTON_WIDTH / 2 + 60,
													  GAME_OVER_HEIGHT / 2 - GAME_OVER_BUTTON_HEIGHT / 2 - 30 },
		35, 0, BLACK);
	DrawTextEx(global.fontChi, "返回主菜单", (Vector2){ GAME_OVER_WIDTH / 2 - GAME_OVER_BUTTON_WIDTH / 2 + 42,
														GAME_OVER_HEIGHT / 2 - GAME_OVER_BUTTON_HEIGHT / 2 + 70 },
		35, 0, BLACK);
	DrawTextEx(global.fontChi, "退出", (Vector2){ GAME_OVER_WIDTH / 2 - GAME_OVER_BUTTON_WIDTH / 2 + 95,
												  GAME_OVER_HEIGHT / 2 - GAME_OVER_BUTTON_HEIGHT / 2 + 170 },
		35, 0, BLACK);
}
