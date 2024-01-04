
#include "fontdata.h"

Font LoadAndGetFont() {
	unsigned char* fontFileData;
	Font fontChi;
	// 字体文件大小
	unsigned int fileSize = 0;
	// 加载字体文件
	fontFileData = LoadFileData("c:\\windows\\fonts\\STXINGKA.TTF", &fileSize);
	char text[] = "五子请选择您先手还是后手悔棋认输重新开始白棋胜利黑棋胜利平局退出重新开始！你输了双人对战人机对战返回主菜单赢了输了";
	int codepointsCount = 0;
	// 转化为codepoints
	int* codepoints = LoadCodepoints(text, &codepointsCount);
	// 加载字体
	fontChi = LoadFontFromMemory(".ttf", fontFileData, fileSize, 32, codepoints, codepointsCount);
	UnloadCodepoints(codepoints);
	UnloadFileData(fontFileData);
	return fontChi;
}

void MyUnloadFontData(Font font) {
	UnloadFont(font);
}
