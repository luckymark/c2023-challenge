#include <raylib.h>
#include <unistd.h>
#include "stackAndSeqList.h"
#include "interface.h"
#include "game.h"

int main()
{
	system("chcp 65001");
	//初始化游戏
	InitGame();
	while (!WindowShouldClose())
	{
		// 画棋盘
		DrawBoard();
		DrawBoardChar();
		// 根据游戏状态画不同的界面
		UpDateGameState();

		BeginDrawing();
		EndDrawing();
	}

	CloseWindow();

	// 结束操作
	DoFinish();
	return 0;
}