# C语言学习笔记

# 记录你学习过程中的所见所思！酸甜苦辣！

# 看什么看！ 赶紧填坑啊！ 

首先，我想出了大概的框架，就是三步走——初始化、绘制内容、更新界面。
接着，我细化了所要完成的内容，先再用户图形界面里放上我选好的棋盘图作为背景图，然后仔细调整，保证每个落子点的位置与绘制棋子的坐标点尽可能地吻合。
然后，我还要考虑鼠标的问题，我查询了相关资料，发现message函数使可以获取鼠标信息的，于是我在此基础上，通过确认鼠标指针位于哪个格子的范围内，进而确认此时如果点击鼠标，棋子该在哪个坐标点落下。为了使游戏界面更加美观，我还添加了鼠标提示框。
为了满足多次的参数调用时代码的简洁性，避免出现大量的参数，扰乱思路，也为了方便函数灵活地更改棋局信息，我定义了一个名为Game的结构体，存放关于棋局的各种信息。（根据需求随时添加变量）
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
};
以下是我设计游戏界面的具体思路和代码。
（1）先初始化游戏界面
void init(Game* pthis, int w, int h) {
	srand(time(NULL));
	//创建一个窗口
	initgraph(w, h, EX_SHOWCONSOLE);
	pthis->isRunning = true;
	pthis->row = -1;
	pthis->col = -1;
	pthis->currentChessType = White;
	//创建棋盘
	//0表示没有棋子，1表示黑棋，-1表示白棋
	int map[ROWS][COLS] = {  };
	memcpy(pthis->map, map, sizeof(int) * ROWS * COLS);
}


（2）根据棋盘（map）绘制棋子，根据换算后的鼠标坐标绘制鼠标所在提示框
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
(3)更新界面
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
为了保证代码的简洁性，我把若干操作打包在了一个函数里：
//创建、更新游戏界面
void creatUI(Game* pthis, IMAGE* theimage) {
	BeginBatchDraw();//开始批量绘图（双缓冲）
	cleardevice();//清屏
	putimage(0, 0, theimage);//放背景图
	render(pthis);//绘制棋子和提示框
	EndBatchDraw();//结束双缓冲绘图
}
2.	实现游戏规则：定义五子棋的游戏规则，如如何判断胜负、如何轮流落子等。
（1）判断胜负，需要横向纵向斜向分析是否有五子连珠。
以下代码是负责分析横向是否五子连珠，其他方向的分析同理。
bool horizontal(Game* pthis, int chess) {
	int counter = 1; // 假设当前位置已经是该棋子的颜色
	int start = pthis->currentchess_col - 1; // 从当前列的前一列开始检查
	int end = pthis->currentchess_col + 1; // 从当前列的后一列开始检查

	// 向左检查
	for (int i = start; i >= 0 && pthis->map[pthis->currentchess_row][i] == chess; i--) {
		counter++;
	}
	// 向右检查
	for (int i = end; i < 15 && pthis->map[pthis->currentchess_row][i] == chess; i++) {
		counter++;
	}

	return counter >= 5;




3.构建博弈树：实现一个用于生成博弈树的函数，该函数应能递归地生成所有可能的走法。
这一步的代码构建已经具有一定的挑战性，我经历了多次的试错与尝试，不断的对其进行改进。先附上我最初行不通的代码，之所以放弃这种思路是因为实在难以插入剪枝算法。
//失败的方案
void generate_moves(State* state, int depth, bool maximizing_player, State* best_move) {
	if (depth == 0 || is_game_over(state)) {
		best_move->x = state->x;
		best_move->y = state->y;
		return;
	}

	if (maximizing_player) {
		int max_eval = -10000;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (state->board[i][j] == 0) {
					state->board[i][j] = 1;
					state->x = i;
					state->y = j;
					generate_moves(state, depth - 1, false, best_move);
					int eval = evaluate(state);
					if (eval > max_eval) {
						max_eval = eval;
						best_move->x = state->x;
						best_move->y = state->y;
					}
					state->board[i][j] = 0;
				}
			}
		}
	}
	else {
		int min_eval = 10000;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (state->board[i][j] == 0) {
					state->board[i][j] = -1;
					state->x = i;
					state->y = j;
					generate_moves(state, depth - 1, true, best_move);
					int eval = evaluate(state);
					if (eval < min_eval) {
						min_eval = eval;
						best_move->x = state->x;
						best_move->y = state->y;
					}
					state->board[i][j] = 0;
				}
			}
		}
	}
}
设计评分函数是很重要的一步，经过优化，我把evaluate（state）函数改为int score(State* state, ChessType a)，以便区分我方和对方的棋子。
经过改进，我把评分函数拆分成了多个函数，分别具有不同的功能：
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
	int Point = detect_succession(MAP, Black, directionMap);
	
	return Point;

}
//棋子阵型分为活、死、冲
//如果连子两侧没有被堵死，则称为活，如果只堵死一侧，称为死，如果都被堵死，则没有分数。
int detect_succession(int MAP[][COLS], ChessType a, DirectionMap directionMap[][COLS]) {
	int point = 0;//记录得分
	int x, y;
	int NumOfSame, NumOfDifference,NumOfjump = 0;


	//1.纵向分析
	for (int j = 0; j < COLS; j++) {
		for (int i = 0; i < ROWS; i++) {
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
			x++;
			if (x < ROWS && MAP[x][y] == a) {
				NumOfjump++;//记录遇到的第一个中间隔了一子的情况
			}
			x--;
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
			x--;
			if (x >= 0 && MAP[x][y] == a) {
				NumOfjump++;
			}
			x++;
			point += countPoint(NumOfSame, NumOfDifference);
		}
	}

	//2.横向分析
(…)
	//3.斜向右下&&左上
(…)
	//4.斜向左下&右上
	(…)
	return point;
}
但是，经过多次测试，发现这个评分机制还不够完善，不能很明确的区分特定的棋型，比如：1个连4和1个连2，以及2个连3，这两种情况无法通过这个算法区分开来，于是我对此进行了优化，采用数组的方法，明确了每种特定的棋型。优化后的代码如下：
typedef struct {
//记录每种棋形出现的次数
	int NumOf_2Dif[5], NumOf_1Dif[5], NumOf_0dif[5],NumOf_0jump[5],NumOf_1jump[5], NumOf_2jump[5];
}Count;
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
	//棋局得分为双方得分的差值
	
	return Point;

}
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
			NumOfSame = 0;
		}
	}
	return count;
}
//单次搜索评估分数
//采用指数函数来拟合权重
int countPoint(int MAP[][COLS], ChessType a, DirectionMap directionMap[][COLS]) {
	int point;
	Count count=detect_succession(MAP, a, directionMap);
	for (int i = 0; i < 5; i++) {
	point += count.NumOf_0dif[i] * pow(10, i) + count.NumOf_1Dif[i] * pow(9, i) + count.NumOf_2Dif[i] * 0 +
		count.NumOf_0jump[i] * pow(9, i) + count.NumOf_1jump[i] * pow(10,i)+ count.NumOf_2jump[i]*(pow(10,i)+pow(8,i));
}	return point;

}
完善了评分算法后，我又苦恼于如何用代码实现博弈树。我意识到棋局的数据需要经过层与层之间的传递，因此必须要想办法把数据暂存下来，起初我的想法是定义若干数组，但与大神交流后，我认为这样实现起来过于复杂和冗余，于是觉得采用类似于链表的树状结构来实现数据的传递。
我定义了一个新的结构体，记录预想中的棋局信息，（不在Game结构体里定义是为了区分开现在的局面和预测的局面，防止混淆），使用结构指针prev，采用类似于链表的数据结构，方便存储相关数据，也方便回溯和遍历。
我先把可能会用得上的变量都在结构体State里面定义一下，不管这些结构体里的定义的变量是否真的能用得上，方便后续设计出更高效的算法。
typedef struct {
	int board[ROWS][COLS];//这一步的棋盘
	int val;//这一步的评分
	ChessType chesstype;//这一步的棋子类型
	int x, y;//下棋的坐标
	State* prev;//上一步棋局
} State;
博弈树的代码构建要与极大极小值算法紧密结合在一起，这是下一步我需要做的内容。
4.实现极大极小值算法：使用极大极小值算法评估博弈树的每个节点，并选择一个最优的走法。
当位于max层时（即电脑一方出棋时），需要记录该层所有节点得分的最大值，以获得最有利于自己的出棋策略，代码如下
		int max_eval = -10000;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (state->board[i][j] == 0) {
					state->board[i][j] = 1;
					state->x = i;
					state->y = j;
					generate_moves(state, depth - 1, false, best_move);
					int eval = evaluate(state);
					if (eval > max_eval) {
						max_eval = eval;
						best_move->x = state->x;
						best_move->y = state->y;
					}
					state->board[i][j] = 0;
				}
同理，当位于min层时（即人类一方出棋时），需要记录该层所有节点得分的最小值，以尽可能使人类一方的利益最小，代码略。
5.实现α-β剪枝算法：在极大极小值算法的基础上，加入α-β剪枝以提高搜索效率。
结合之前的博弈树的大致结构，我设计出以下的思路，代码如下：
成功的方案：
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

Coordinate get_best_move(State* state, int depth) {
	Coordinate best_move = { -1, -1 }; // 初始化最佳坐标为无效值
	int best_score = -INFINITY; // 初始化最佳得分为负无穷

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
6.游戏逻辑整合：将以上步骤整合到一个主循环中，实现游戏的完整逻辑。

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
		if (judge(&game)) {
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
