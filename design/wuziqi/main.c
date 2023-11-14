
#include <stdio.h>
#include "raylib.h"

int main(void)
{
	// 初始化
	//--------------------------------------------------------------------------------------
	const int screenWidth = 1140;
	const int screenHeight = 960;

	InitWindow(screenWidth, screenHeight, "五子棋");

	char imageChessBoardPath[256] = "C:\\Users\\81201\\CLionProjects\\c2023-challenge\\design\\wuziqi\\chessBoard2.png";
	char imageWhiteChessPath[256] = "C:\\Users\\81201\\CLionProjects\\c2023-challenge\\design\\wuziqi\\whiteChess.png";
	char imageBlackChessPath[256] = "C:\\Users\\81201\\CLionProjects\\c2023-challenge\\design\\wuziqi\\blackChess.png";

	Texture2D imageChessBoard = LoadTexture(imageChessBoardPath);
	Texture2D imageBlackChess = LoadTexture(imageBlackChessPath);
	Texture2D imageWhiteChess = LoadTexture(imageWhiteChessPath);

	SetTargetFPS(60);               // 设置帧率
	//--------------------------------------------------------------------------------------

	// 主要的循环
	while (!WindowShouldClose())    // 检测是否关闭
	{


		// 画图
		//----------------------------------------------------------------------------------
		BeginDrawing();
		//背景
		ClearBackground(RAYWHITE);
		//有立体感的棋盘
		DrawTexture(imageChessBoard, 0, 0, WHITE);
		//有立体感的棋盘格子
		for (int i = 0; i < 15; ++i) {
			DrawRectangle(65 + 60 * i, 64, 2, 840, BLACK);
			DrawRectangle(65, 64 + 60 * i, 840, 2, BLACK);
		}
		//增加棋盘上的点
		DrawCircle(65 + 60 * 3, 64 + 60 * 3, 5, BLACK);
		DrawCircle(65 + 60 * 3, 64 + 60 * 11, 5, BLACK);
		DrawCircle(65 + 60 * 11, 64 + 60 * 3, 5, BLACK);
		DrawCircle(65 + 60 * 11, 64 + 60 * 11, 5, BLACK);
		DrawCircle(65 + 60 * 7, 64 + 60 * 7, 5, BLACK);
        //棋子
		DrawTexture(imageBlackChess,37,37,WHITE);
		DrawTexture(imageWhiteChess,37,97,WHITE);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// 结束
	//--------------------------------------------------------------------------------------
	CloseWindow();        // 关闭窗口和OpenGL
	//--------------------------------------------------------------------------------------

	return 0;
}
