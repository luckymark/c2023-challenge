#include<stdio.h>
#include<easyx.h>
#include<graphics.h>
#include<conio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>

#define ROWS 15//棋盘格子尺寸
#define MAX_ROW 15
#define COLS 15
#define GRID_SIZE 65//像素尺寸
#define XOFFSET 40//偏移量
#define YOFFSET 40


enum ChessType {//棋盘格子的状态
	None = 0,
	Black = 1,
	White = -1
};
enum Player {//棋手是人还是电脑
	robot = -1,
	human = 1,

};





//游戏结构
struct Game {
	//0表示没有棋子，1表示黑棋，-1表示白棋
	int map[ROWS][COLS];
	//游戏是否在运行
	bool isRunning;
	//定义消息变量
	ExMessage msg;//消息结构体，负责鼠标键盘
	//鼠标当前所在下标
	int row = 0;
	int col = 0;
	//上一次下的棋子的位置坐标
	int currentchess_row = 0;
	int currentchess_col = 0;
	//当前棋手
	ChessType currentChessType;
	Player player;
	//电脑下棋的坐标
	int robotRow = 1;
	int robotCol = 1;
	int specialRow, specialCol = 0;
	bool is_warning;
};
struct DirectionMap {
	int horizontal = {};
	int vertical = {};
	int leftOblique = {};
	int rightOblique = {};
};
typedef struct {
	int NumOf_2Dif[5], NumOf_1Dif[5], NumOf_0dif[5],NumOf_0jump[5],NumOf_1jump[5], NumOf_2jump[5],NumOf_warning;
}Count;

typedef struct State {
	int board[ROWS][COLS];//这一步的棋盘
	int val;//这一步的评分
	ChessType chesstype;//这一步的棋子类型
	int x, y;//下棋的坐标
	State* prev;//上一步棋局
} State;



//游戏初始化
void init(Game* pthis, int w, int h);
//游戏绘制
void render(Game* pthis);
//游戏更新
void update(Game* pthis);
//生成游戏界面
void creatUI(Game* pthis, IMAGE* theimage);
//人机切换
void shiftplayer(Game* pthis);
//机器下棋
void robotplay(Game* pthis);
//计算电脑下棋的坐标
void figure_coord(Game* pthis);

//搜索有棋子的邻居空位，只深搜这些空位
bool isNextchess(State* state, int x, int y, int n);//判断(x,y)坐标是否为符合条件的位置。
//n为1，判断直接相邻的空位；n为2，判断两格以内的所有空位

// 局部分数评估
int score(State* state, ChessType a);
bool judge(Game* pthis, int num);










//判断坐标为(x,y)的棋子周围的情况
//活一10，活二100，活三1000，活四10000，活五100000。死二10，死三100，死四1000。
//如果连子两侧没有被堵死，则称为活，如果只堵死一侧，称为死，如果都被堵死，则没有分数。
Count detect_succession(int MAP[][COLS], ChessType a, DirectionMap directionMap[][COLS]);
//单次搜索评估分数
//活一10，活二100，活三1000，活四10000，活五100000。死二10，死三100，死四1000。
int countPoint(int MAP[][COLS], ChessType a, DirectionMap directionMap[][COLS]);
//博弈树
//void generate_moves(State* state, int depth, bool maximizing_player, State* best_move);
//State alpha_beta_search(State* state, int depth);
//void generate_moves(State* state, int depth, bool maximizing_player, State* best_move);
//bool is_game_over(State* state);
//int search(int depth,State stepNode, int alpha, int beta, bool is_max);

bool is_win(State* state) {
	int x = state->x;
	int y = state->y;
	int player = state->board[x][y];
	int directions[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} };

	for (int i = 0; i < 4; i++) {
		int count = 1;
		for (int j = 1; j < 5; j++) {
			int new_x = x + directions[i][0] * j;
			int new_y = y + directions[i][1] * j;
			if (new_x >= 0 && new_x < 15 && new_y >= 0 && new_y < 15 && state->board[new_x][new_y] == player) {
				count++;
			}
			else {
				break;
			}
		}
		for (int j = 1; j < 5; j++) {
			int new_x = x - directions[i][0] * j;
			int new_y = y - directions[i][1] * j;
			if (new_x >= 0 && new_x < 15 && new_y >= 0 && new_y < 15 && state->board[new_x][new_y] == player) {
				count++;
			}
			else {
				break;
			}
		}
		if (count >= 5) {
			return true;
		}
	}
	return false;
}
int search(State* StepNode, int depth, int alpha, int beta, bool is_max) {
	if (depth == 0 || is_win(StepNode)) {
		int s = score(StepNode, is_max ? Black : White);
		return s;
	}

	if (is_max) {
		int maxEval = -INFINITY; // 假设负无穷为最小值
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				if (isNextchess) {
					State* NewstepNode = (State*)malloc(sizeof(State));
					memcpy(NewstepNode, StepNode, sizeof(State));
					NewstepNode->board[i][j] = Black; // 下棋
					NewstepNode->prev = StepNode;
					NewstepNode->x = i;
					NewstepNode->y = j;
					int s = search(NewstepNode, depth - 1, alpha, beta, is_max);
					NewstepNode->val = s;
					maxEval = max(maxEval, s);
					alpha = max(alpha, s); // 更新alpha值
					if (beta <= alpha) { // alpha-beta剪枝
						free(NewstepNode);
						return maxEval; // 返回当前最大值
					}
				}
			}
		}
		return maxEval; // 返回最大值
	}
	else { // is_min
		int minEval = INFINITY; // 假设正无穷为最大值
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				if (isNextchess) {
					State* NewstepNode = (State*)malloc(sizeof(State));
					memcpy(NewstepNode, StepNode, sizeof(State));
					NewstepNode->board[i][j] = White; // 下棋
					NewstepNode->prev = StepNode;
					NewstepNode->x = i;
					NewstepNode->y = j;
					int s = search(NewstepNode, depth - 1, alpha, beta, is_max);
					NewstepNode->val = s;
					minEval = min(minEval, s);
					beta = min(beta, s); // 更新beta值
					if (beta <= alpha) { // alpha-beta剪枝
						free(NewstepNode);
						return minEval; // 返回当前最小值
					}
				}
			}
		}
		return minEval; // 返回最小值
	}
}
typedef struct {
	int x;
	int y;
} Coordinate;

Coordinate get_best_move(Game*pthis,State* state, int depth) {
	Coordinate best_move = { -1, -1 }; // 初始化最佳坐标为无效值
	int best_score = -INFINITY; // 初始化最佳得分为负无穷
	if (judge(pthis, 4)) {
		best_move.x = pthis->specialRow;
		best_move.y = pthis->specialCol;
		return best_move;
	}
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (isNextchess(state, i, j,2)) { // 判断该位置是否可以落子
				State* new_state = (State*)malloc(sizeof(State));
				memcpy(new_state, state, sizeof(State));
				new_state->board[i][j] = Black; // 电脑落子为黑色
				new_state->prev = state;
				new_state->x = i;
				new_state->y = j;

				int score = search(new_state, depth, -INFINITY, INFINITY, true); // 搜索该落子后的局面得分
				if (score > best_score) { // 更新最佳得分和最佳坐标
					best_score = score;
					best_move.x = i;
					best_move.y = j;
				}
				free(new_state); // 释放内存
			}
		}
	}
	
	return best_move; // 返回最佳落子坐标
}





//判断五子连珠
bool horizontal(Game* pthis, int chess, int num);
bool vertical(Game* pthis, int chess,int num);
bool leftOblique(Game* pthis, int chess, int num);
bool rightOblique(Game* pthis, int chess,int num);
bool judge(Game* pthis, int num);





int main() {
	Game game;
	init(&game, 1000, 1000);
	IMAGE img_bg;//定义图片
	loadimage(&img_bg, L"D:\\五子棋游戏\\bk.jpg");//输入想要的图片
	putimage(0, 0, &img_bg);

	//处理鼠标操作

	//游戏主循环



	
	//默认人是先手
	game.player = human;
	while (game.isRunning) {

		//获取消息
		//尚未完善
		if (judge(&game,5)) {
			MessageBox(GetHWnd(), L"结束了", L"XXX ", MB_OK);
			game.isRunning = false;
		}
		if (game.player == human) {
			if (peekmessage(&game.msg)) {
				update(&game);//鼠标点击后生成白色棋子
			}
			creatUI(&game, &img_bg);//生成、更新游戏界面
		}
		else if (game.player == robot) {

			robotplay(&game);
			creatUI(&game, &img_bg);//生成、更新游戏界面
			shiftplayer(&game);//人机切换
		}
	}
	return 0;
}
//初始化棋盘
void init(Game* pthis, int w, int h) {
	srand(time(NULL));
	//创建一个窗口
	initgraph(w, h, EX_SHOWCONSOLE);
	pthis->isRunning = true;
	pthis->row = -1;
	pthis->col = -1;
	//pthis->currentChessType=rand()%2?Black:White;
	pthis->currentChessType = White;
	//创建棋盘
	//0表示没有棋子，1表示黑棋，-1表示白棋
	int map[ROWS][COLS] = {  };
	memcpy(pthis->map, map, sizeof(int) * ROWS * COLS);
}
//绘制棋子
void render(Game* pthis) {
	//绘制棋子
	for (int i = 0; i < ROWS; i++) {
		for (int k = 0; k < COLS; k++) {


			if (pthis->map[i][k] != None) {
				//求每个格子左上角的坐标
				int x = k * GRID_SIZE + XOFFSET;
				int y = i * GRID_SIZE + YOFFSET;
				//绘制棋子
				if (pthis->map[i][k] == White) {
					setfillcolor(WHITE);
				}
				else if (pthis->map[i][k] == Black) {
					setfillcolor(BLACK);
				}

				//绘制棋子
				solidcircle(x, y, 20);
			}
		}
	}
	//绘制当前鼠标所在的提示框
	if (pthis->row != -1 && pthis->col != -1) {
		setlinecolor(BLUE);//设置提示框线条颜色
		int x = pthis->col * GRID_SIZE + XOFFSET;
		int y = pthis->row * GRID_SIZE + YOFFSET;
		circle(x, y, 25);
	}
}
void update(Game* pthis) {

	//鼠标移动，判断鼠标指针位于哪个格子的区域
	if (pthis->msg.message == WM_MOUSEMOVE) {
		for (int i = 0; i < ROWS; i++) {
			for (int k = 0; k < COLS; k++) {
				int cx = k * GRID_SIZE + XOFFSET;
				int cy = i * GRID_SIZE + YOFFSET;
				//判断鼠标指针位于棋盘哪个格子的区域
				if (abs(pthis->msg.x - cx) < GRID_SIZE / 2 && abs(pthis->msg.y - cy) < GRID_SIZE / 2) {
					pthis->row = i;
					pthis->col = k;
					goto END_LOOP;
				}
			}
		}
	END_LOOP:;//跳转于此
	}

	//下出棋子，并在pthis->map上记录棋子位置和颜色
	else if (pthis->msg.message == WM_LBUTTONDOWN//鼠标左键点击
		&& pthis->row != -1 && pthis->col != -1 &&//点击了合法的位置
		pthis->map[pthis->row][pthis->col] == None)//当前位置没有棋子
	{
		pthis->map[pthis->row][pthis->col] = pthis->currentChessType;
		//记录本次下棋棋子的位置
		pthis->currentchess_row = pthis->row;
		pthis->currentchess_col = pthis->col;
		//切换棋手
		pthis->currentChessType = (ChessType)-pthis->currentChessType;
		shiftplayer(pthis);//人机切换

	}
}
//判断胜负
bool judge(Game* pthis,int num) {
	int who = -pthis->currentChessType;
	if (horizontal(pthis, who, num))return true;
	if (vertical(pthis, who,num))return true;
	if (leftOblique(pthis, who,num))return true;
	if (rightOblique(pthis, who,num))return true;
	return false;
}
//判断五子连珠
//未做完
bool horizontal(Game* pthis, int chess,int num) {
	int counter = 1; // 假设当前位置已经是该棋子的颜色
	int start = pthis->currentchess_col - 1; // 从当前列的前一列开始检查
	int end = pthis->currentchess_col + 1; // 从当前列的后一列开始检查
	
	// 向左检查
	for (int i = start; i >= 0 && pthis->map[pthis->currentchess_row][i] == chess; i--) {
		counter++;
		
		if (pthis->map[pthis->currentchess_row][i] == 0) {
			
			pthis->specialRow = pthis->currentchess_row;
			pthis->specialCol = i;
		}

	}
	// 向右检查
	for (int i = end; i < 15 && pthis->map[pthis->currentchess_row][i] == chess; i++) {
		counter++;

		if (pthis->map[pthis->currentchess_row][i] == 0) {
			
			pthis->specialRow = pthis->currentchess_row;
			pthis->specialCol = i;
		}
	}

	return counter >= num;
}

bool vertical(Game* pthis, int chess, int num) {
	int counter = 1; // 假设当前位置已经是该棋子的颜色
	int start = pthis->currentchess_row - 1; // 从当前行的前一行开始检查
	int end = pthis->currentchess_row + 1; // 从当前行的后一行开始检查

	// 向上检查
	for (int i = start; i >= 0 && pthis->map[i][pthis->currentchess_col] == chess; i--) {
		counter++;
		if (pthis->map[i][pthis->currentchess_col] == 0) {
			pthis->specialRow = i;
			pthis->specialCol = pthis->currentchess_col;
		}
	}
	// 向下检查
	for (int i = end; i < 15 && pthis->map[i][pthis->currentchess_col] == chess; i++) {
		counter++;
		if (pthis->map[i][pthis->currentchess_col] == 0) {
			pthis->specialRow = i;
			pthis->specialCol = pthis->currentchess_col;
		}
	}

	return counter >= num;
}

bool leftOblique(Game* pthis, int chess, int num) {
	int counter = 1; // 假设当前位置已经是该棋子的颜色
	int startRow = pthis->currentchess_row - 1;
	int startCol = pthis->currentchess_col - 1;

	// 向左上检查
	for (int i = startRow, j = startCol; i >= 0 && j >= 0 && pthis->map[i][j] == chess; i--, j--) {
		counter++;
		if (pthis->map[i][j] == 0) { 
			pthis->specialRow = i; 
			pthis->specialCol = j;
		}
	}
	
	// 向右下检查
	for (int i = pthis->currentchess_row + 1, j = pthis->currentchess_col + 1; i < 15 && j < 15 && pthis->map[i][j] == chess; i++, j++) {
		counter++;
		if (pthis->map[i][j] == 0) {
			pthis->specialRow = i;
			pthis->specialCol = j;
		}
	}

	return counter >= num;
}

bool rightOblique(Game* pthis, int chess, int num) {
	int counter = 1; // 假设当前位置已经是该棋子的颜色
	int startRow = pthis->currentchess_row - 1;
	int startCol = pthis->currentchess_col + 1;

	// 向右上检查
	for (int i = startRow, j = startCol; i >= 0 && j < 15 && pthis->map[i][j] == chess; i--, j++) {
		counter++;
		if (pthis->map[i][j] == 0) {
			pthis->specialRow = i;
			pthis->specialCol = j;
		}
	}
	// 向左下检查
	for (int i = pthis->currentchess_row + 1, j = pthis->currentchess_col - 1; i < 15 && j >= 0 && pthis->map[i][j] == chess; i++, j--) {
		counter++;
		if (pthis->map[i][j] == 0) {
			pthis->specialRow = i;
			pthis->specialCol = j;
		}
	}

	return counter >= num;
}

void shiftplayer(Game* pthis) {
	if (pthis->player == human) {
		pthis->player = robot;
	}
	else if (pthis->player == robot) {
		pthis->player = human;
	}
}
void robotplay(Game* pthis) {
	figure_coord(pthis);
	printf("(%d,%d)\n", pthis->robotRow, pthis->robotCol);
	pthis->map[pthis->robotRow][pthis->robotCol] = pthis->currentChessType;
	pthis->currentChessType = (ChessType)-pthis->currentChessType;

}
//创建、更新游戏界面
void creatUI(Game* pthis, IMAGE* theimage) {
	BeginBatchDraw();//开始批量绘图（双缓冲）
	cleardevice();//清屏
	putimage(0, 0, theimage);//放背景图
	render(pthis);//绘制棋子和提示框
	EndBatchDraw();//结束双缓冲绘图
}
//算法核心——计算电脑下棋的坐标
//未完善
void figure_coord(Game* pthis) {
	
	State* state =(State*)malloc(sizeof(State));
	memcpy(state->board, pthis->map, sizeof(int) * ROWS * COLS);
	Coordinate best_move= get_best_move(pthis,state, 5);
	pthis->robotRow = best_move.x;
	pthis->robotCol = best_move.y;
	pthis->currentchess_row = pthis->robotRow;
	pthis->currentchess_col = pthis->robotCol;

}

//搜索有棋子的邻居空位，只深搜这些空位
//判断(x,y)坐标是否为符合条件的位置。
//n为1，判断直接相邻的空位；n为2，判断两格以内的所有空位
bool isNextchess(State* state, int x, int y, int n) {
	int MAP[ROWS][COLS];
	memcpy(MAP, state->board, sizeof(int) * ROWS * COLS);
	int i, j=0;
	//printf("b1");
	if (MAP[x][y] == 0)
	{

		if (n == 1)
		{
			for (i = x - 1; i < x + 2; i++) {
				for (j = y - 1; j < y + 2; j++) {
					if ((i > 0 && j > 0 && i < ROWS && j < COLS) && (MAP[i][j] == 1 || MAP[i][j] == -1))
						return true;
				}
			}
		}
		else
		{
			for (i = x - 2; i < x + 3; i += 2) {
				for (j = y - 2; j < y + 3; j += 2) {
					if ((i > 0 && j > 0 && i < ROWS && j < COLS) && (MAP[i][j] == 1 || MAP[i][j] == -1))
						return true;
				}
			}
		}
	}
	return false;
}
//棋局分数评估
//活一10，活二100，活三1000，活四10000，活五100000。死二10，死三100，死四1000。
//如果连子两侧没有被堵死，则称为活，如果只堵死一侧，称为死，如果都被堵死，则没有分数。
int score(State* state, ChessType a) {
	int MAP[ROWS][COLS];
	memcpy(MAP, state->board, sizeof(int) * ROWS * COLS);
	DirectionMap directionMap[ROWS][COLS] = {};
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			if (MAP[i][j] == 0) {
				directionMap[i][j].horizontal = 2;
				directionMap[i][j].vertical = 2;
				directionMap[i][j].leftOblique = 2;
				directionMap[i][j].rightOblique = 2;//将没有棋子的位置标记，遍历时不经过这些点
			}
		}
	}
	
		int Point = countPoint(MAP, Black, directionMap)-countPoint(MAP,White,directionMap);
	
	
	return Point;

}

//活一10，活二100，活三1000，活四10000，活五100000。死二10，死三100，死四1000。
//如果连子两侧没有被堵死，则称为活，如果只堵死一侧，称为死，如果都被堵死，则没有分数。
Count detect_succession(int MAP[][COLS], ChessType a, DirectionMap directionMap[][COLS]) 
{   
	int point = 0;//记录得分
	int x, y;
	int NumOfSame, NumOfDifference,NumOfjump = 0;
	Count count = { 0 };
	

	//1.纵向分析
	for (int j = 0; j < COLS; j++) 
	{
		for (int i = 0; i < ROWS; i++)
		{
			x = i, y = j;
			NumOfSame, NumOfDifference = 0;
			//如果相应点不是棋子类型a，则直接跳过
			if (MAP[x][y] != a || directionMap[x][y].horizontal != 0) {
				continue;
			}

			while (MAP[x][y] == a && directionMap[x][y].horizontal == 0 && x < ROWS) {
				NumOfSame = 1;
				NumOfDifference = 0;

				directionMap[x][y].horizontal = 1;//标记，已经遍历过
				NumOfSame++;//连起来的棋子数+1
				x++;//继续分析下一个棋子
			}
			if (x<ROWS&&MAP[x][y] == -a) {
				NumOfDifference++;//记录往右方向遍历时撞上的第一个异色棋子
				
			}
			else {
				x++;
				if (x < ROWS && MAP[x][y] == a) {
					NumOfjump++;//记录遇到的第一个中间隔了一子的情况
				}
				x--;
			}
			x -= NumOfSame;//回到出发点
			//开始往左方向遍历
			while (MAP[x][y] == a && directionMap[x][y].horizontal == 0 && x >= 0) {
				directionMap[x][y].horizontal = 1;//标记，已经遍历过
				NumOfSame++;//连起来的棋子数+1
				x--;//继续分析下一个棋子

			}
			if (x>0&&MAP[x][y] == -a) {
				NumOfDifference++;//记录撞上的第二个异色棋子
				
			}
			else {
				x--;
				if (x >= 0 && MAP[x][y] == a) {
					NumOfjump++;
				}
				x++;
			}
			if (NumOfDifference == 0)count.NumOf_0dif[NumOfSame-1]++;
			if (NumOfDifference == 1)count.NumOf_1Dif[NumOfSame-1]++;
			if (NumOfDifference == 2) count.NumOf_2Dif[NumOfSame - 1]++;
			if (NumOfjump == 0)count.NumOf_0jump[NumOfSame - 1]++;
			if (NumOfjump == 1)count.NumOf_1jump[NumOfSame - 1]++;
			if (NumOfjump == 2)count.NumOf_2jump[NumOfSame - 1]++;
			if (a == White && NumOfSame >= 3)count.NumOf_warning+=NumOfSame;
			NumOfSame = 0;
		}
	}


	//2.横向分析
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			x = i, y = j;
			//如果相应点不是棋子类型a，则直接跳过
			if (MAP[x][y] != a || directionMap[x][y].vertical != 0)
			{
				continue;
			}

			while (MAP[x][y] == a && directionMap[x][y].vertical == 0 && y < ROWS)
			{
				NumOfSame = 1;
				NumOfDifference = 0;

				directionMap[x][y].horizontal = 1;//标记，已经遍历过
				NumOfSame++;//连起来的棋子数+1
				y++;//继续分析下一个棋子
			}
			if (y<COLS && MAP[x][y] == -a)
			{
				NumOfDifference++;//记录往下方向遍历时撞上的第一个异色棋子
				
			}
			else {
				y++;
				if (y < COLS && MAP[x][y] == a) {
					NumOfjump++;
				}
				y--;
			}
			y -= NumOfSame;//回到出发点
			//开始往上方向遍历
			while (MAP[x][y] == a && directionMap[x][y].vertical == 0 && x >= 0)
			{
				directionMap[x][y].vertical = 1;//标记，已经遍历过
				NumOfSame++;//连起来的棋子数+1
				y--;//继续分析下一个棋子

			}
			if (MAP[x][y] == -a)
			{
				NumOfDifference++;//记录撞上的第二个异色棋子
				
			}
			else {
				y--;
				if (y >= 0 && MAP[x][y] == a) {
					NumOfjump++;
				}
				y++;
			}
			if (NumOfDifference == 0)count.NumOf_0dif[NumOfSame - 1]++;
			if (NumOfDifference == 1)count.NumOf_1Dif[NumOfSame - 1]++;
			if (NumOfDifference == 2)count.NumOf_2Dif[NumOfSame - 1]++;
			if (NumOfjump == 0)count.NumOf_0jump[NumOfSame - 1]++;
			if (NumOfjump == 1)count.NumOf_1jump[NumOfSame - 1]++;
			if (NumOfjump == 2)count.NumOf_2jump[NumOfSame - 1]++;
			if (a == White && NumOfSame >= 3)count.NumOf_warning += NumOfSame;
			NumOfSame = 0;
		}
	}


	//3.斜向右下&&左上
	for (int j = 0; j < COLS; j++)
	{
		for (int i = 0; i < ROWS; i++)
		{
			x = i, y = j;
			//如果相应点不是棋子类型a，则直接跳过
			if (MAP[x][y] != a || directionMap[x][y].leftOblique != 0)
			{
				continue;
			}

			while (MAP[x][y] == a && directionMap[x][y].leftOblique == 0 && y < ROWS && x < ROWS)
			{
				NumOfSame = 1;
				NumOfDifference = 0;

				directionMap[x][y].leftOblique = 1;//标记，已经遍历过
				NumOfSame++;//连起来的棋子数+1
				x++;
				y++;//继续分析下一个棋子
			}
			if (MAP[x][y] == -a)
			{
				NumOfDifference++;//记录往右下方向遍历时撞上的第一个异色棋子
				
			}else {
				x++;
				y++;
				if (x < ROWS && y < COLS && MAP[x][y] == a) {
					NumOfjump++;
				}
				x--;
				y--;
			}
				x -= NumOfSame;
				y -= NumOfSame;//回到出发点
			
			//开始往左上方向遍历
			while (MAP[x][y] == a && directionMap[x][y].leftOblique == 0 && x >= 0 && y >= 0)
			{
				directionMap[x][y].leftOblique = 1;//标记，已经遍历过
				NumOfSame++;//连起来的棋子数+1
				x--;
				y--;//继续分析下一个棋子

			}
			if (MAP[x][y] == -a)
			{
				NumOfDifference++;//记录撞上的第二个异色棋子
				
			}
			else {
				x--;
				y--;
				if (x >= 0 && y >= 0 && MAP[x][y] == a) {
					NumOfjump++;
				}
				x++;
				y++;
			}
			if (NumOfDifference == 0)count.NumOf_0dif[NumOfSame - 1]++;
			if (NumOfDifference == 1)count.NumOf_1Dif[NumOfSame - 1]++;
			if (NumOfDifference == 2) count.NumOf_2Dif[NumOfSame - 1]++;
			if (NumOfjump == 0)count.NumOf_0jump[NumOfSame - 1]++;
			if (NumOfjump == 1)count.NumOf_1jump[NumOfSame - 1]++;
			if (NumOfjump == 2)count.NumOf_2jump[NumOfSame - 1]++;
			if (a == White && NumOfSame >= 3)count.NumOf_warning += NumOfSame;
			NumOfSame = 0;
		}
	}

	//4.斜向左下&右上
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = COLS - 1; j >= 0; j--)
		{
			x = i, y = j;
			//如果相应点不是棋子类型a，则直接跳过
			if (MAP[x][y] != a || directionMap[x][y].rightOblique != 0)
			{
				continue;
			}

			while (MAP[x][y] == a && directionMap[x][y].rightOblique == 0 && y < COLS && x >= 0)
			{
				NumOfSame = 1;
				NumOfDifference = 0;

				directionMap[x][y].rightOblique = 1;//标记，已经遍历过
				NumOfSame++;//连起来的棋子数+1
				x--;
				y++;//继续分析下一个棋子
			}
			if (MAP[x][y] == -a)
			{
				NumOfDifference++;//记录往右下方向遍历时撞上的第一个异色棋子

			}
			else {
				x--;
				y++;
				if (x >= 0 && y < COLS && MAP[x][y] == a) {
					NumOfjump++;
				}
				x++;
				y--;
			}
			x += NumOfSame;
			y -= NumOfSame;//回到出发点
			//开始往左上方向遍历
			while (MAP[x][y] == a && directionMap[x][y].rightOblique == 0 && y >= 0 && x < ROWS)
			{
				directionMap[x][y].rightOblique = 1;//标记，已经遍历过
				NumOfSame++;//连起来的棋子数+1
				x++;
				y--;//继续分析下一个棋子

			}
			if (MAP[x][y] == -a)
			{
				NumOfDifference++;//记录撞上的第二个异色棋子
				
			}
			else {
				x++;
				y--;
				if (x < ROWS && y >= 0 && MAP[x][y] == a) {
					NumOfjump++;
				}
				x--;
				y++;
			}
			if (NumOfDifference == 0)count.NumOf_0dif[NumOfSame - 1]++;
			if (NumOfDifference == 1)count.NumOf_1Dif[NumOfSame - 1]++;
			if (NumOfDifference == 2) count.NumOf_2Dif[NumOfSame - 1]++;
			if (NumOfjump == 0)count.NumOf_0jump[NumOfSame - 1]++;
			if (NumOfjump == 1)count.NumOf_1jump[NumOfSame - 1]++;
			if (NumOfjump == 2)count.NumOf_2jump[NumOfSame - 1]++;
			if (a == White && NumOfSame >= 3)count.NumOf_warning += NumOfSame;
			NumOfSame = 0;
		}
	}
	return count;
}
//单次搜索评估分数
//活一10，活二100，活三1000，活四10000，活五100000。死二10，死三100，死四1000。
int countPoint(int MAP[][COLS], ChessType a, DirectionMap directionMap[][COLS]) {
	int point = 0;
	Count count=detect_succession(MAP, a, directionMap);
	for (int i = 0; i < 5; i++) {
		point += count.NumOf_0dif[i] * pow(10, i) + count.NumOf_1Dif[i] * pow(9, i) + count.NumOf_2Dif[i] * 0 +
			count.NumOf_0jump[i] * pow(9, i) + count.NumOf_1jump[i] * pow(10, i)+count.NumOf_2jump[i]*(pow(10,i)+pow(8,i));
	}
	if (count.NumOf_warning >= 2)point += 1000000;
	return point;

}
