#pragma once

#include <raylib.h>

// 定义按钮和菜单背景的颜色
#define BUTTON_COLOR      CLITERAL(Color){ 160, 82, 45, 255 }
#define MENU_COLOR      CLITERAL(Color){ 205, 133, 63, 255 }

//定义棋盘行数以及列数
#define BOARD_ROW 15
#define BOARD_COL 15
//声明一个最大值
#define INFINITY 999999999
//声明递归的最大深度
#define MAX_DEPTH 6
// 定义先手时进攻和防守的权重
#define LEAD_ATTACK_WEIGHT 5
#define LEAD_DEFENSE_WEIGHT 4
// 定义后手时进攻和防守的权重
#define FOLLOW_ATTACK_WEIGHT 4
#define FOLLOW_DEFENSE_WEIGHT 5
// 定义下棋的坐标余量（起始点）
#define START_CHESS_X 37
#define START_CHESS_Y 34
// 定义菜单界面的宽度和高度
#define MENU_WIDTH 500
#define MENU_HEIGHT 400
// 定义游戏界面的宽度和高度
#define SCREEN_WIDTH 1140
#define SCREEN_HEIGHT 960
// 定义菜单按钮的宽度和高度
#define MENU_BUTTON_WIDTH 160
#define MENU_BUTTON_HEIGHT 50
// 定义棋盘线的间隔
#define LINEAR_SPACING 60
// 定义棋盘开始的坐标
#define START_X 65
#define START_Y 64
// 定义按钮的x坐标，y坐标和按钮之间的间隔
#define BUTTON_X 940
#define BUTTON_Y 310
#define BUTTON_SPACING 90
// 定义按钮的宽度和高度
#define BUTTON_WIDTH 160
#define BUTTON_HEIGHT 50
// 定义结束按钮的宽度和高度
#define GAME_OVER_BUTTON_WIDTH 250
#define GAME_OVER_BUTTON_HEIGHT 70
// 定义游戏结束界面的宽度和高度
#define GAME_OVER_WIDTH 340
#define GAME_OVER_HEIGHT 430
// 连五，活四最大数量
#define MAX_FIR 10
// 四三，三三最大数量
#define MAX_SEC 10
// 活三，冲四最大数量
#define MAX_THI 20
// 活二，眠三最大数量
#define MAX_FOU 20

// 枚举类型，表示棋型
typedef enum ChessModel
{
	EMPTY,
	MIAN_1,
	HUO_1,
	HUO_2,
	HUO_2_101,
	MIAN_2,
	MIAN_2_101,
	MIAN_2_1001,
	MIAN_2_10001,
	MIAN_3,
	MIAN_3_102,
	MIAN_3_201,
	MIAN_3_1002,
	MIAN_3_2001,
	MIAN_3_10101,
	HUO_3,
	HUO_3_102,
	HUO_3_201,
	CHONG_4,
	CHONG_4_103,
	CHONG_4_301,
	CHONG_4_202,
	HUO_4,
	LIAN_5,
	HUN_10002,
	HUN_100101,
	HUN_1003,
	HUN_101001,
	HUN_10102,
	HUN_10201,
	HUN_104,
	HUN_20001,
	HUN_2002,
	HUN_20101,
	HUN_203,
	HUN_3001,
	HUN_302,
	HUN_401,
	LIAN_6,
} ChessModel;
//把所有定义好的棋型以及棋型对应的分数存入hash 表
typedef struct HashTable
{
	ChessModel chessModel;
	int score;
} HashTable;

// 定义游戏状态
typedef enum GameState
{
	MENU,
	SELECT_SIDE,
	PLAYING,
	GAME_OVER,
} GameState;

// 定义游戏模式
typedef enum
{
	PLAYER_VS_PLAYER,
	PLAYER_VS_AI
} GameMode;

// 定义棋子颜色
typedef enum ChessColor
{
	EMPTY_CHESS = 0,
	BLACK_CHESS = 1,
	WHITE_CHESS = 2,
	VIRTUAL_CHESS = 3,
	HIGHLIGHT_CHESS = 4,
	MIDDLE_LIGHT_CHESS = 5,
	LIGHT_CHESS = 6,
} ChessColor;

// 定义玩家
typedef struct Player
{
	ChessColor color;
} Player;

// 定义点
typedef struct Point
{
	int row;
	int col;
} Point;

// 定义游戏结果
typedef enum GameResult
{
	BLACK_WIN,
	WHITE_WIN,
	DRAW,
	UNFINISHED,
	PLAYER_WIN,
	PLAYER_LOSE
} GameResult;

// 定义游戏内的点击
typedef enum GameClick
{
	CHESS_BOARD,
	REGRET,
	GIVE_UP,
	RESTART,
	DO_EXIT_CLICK,
	CLICK_NONE,
	RETURN_MENU,
	REPLAY
} GameClick;

// 定义棋子
typedef struct Chess
{
	int x;
	int y;
	ChessColor color;
} Chess;

// 定义栈
typedef struct stack
{
	Chess* a;
	int size;
	int capacity;
} ST;

typedef int SLDataType;
// 定义顺序表
typedef struct SeqList
{
	SLDataType* a;
	int size;//表明数组中储存了多少个数据
	int capacity;//数组实际的空间容量
} SL;

// 定义全局变量
typedef struct Global
{
	GameState gameState;
	GameMode gameMode;
	GameResult gameResult;
	GameClick finalClick;
	Player AI, player, player1, player2, curPlayer, firstPlayer;
	Chess gameBoard[BOARD_ROW][BOARD_COL];
	Chess virtualBoard[BOARD_ROW][BOARD_COL];
	ChessColor prePlayerColor;
	Point bestPoint;
	ST stackChess;
	ST stackVirtualChess;
	Font fontChi;
	Font fontEng;
	Font fontFigures;
	int lastRow;
	int lastCol;
	int stepNumber;
	int pushVirtualChessQuantity[225];
	Texture2D imageChessBoard;
	Texture2D imageChessBoxWhite;
	Texture2D imageChessBoxBlack;
	Texture2D imageBlackChess;
	Texture2D imageWhiteChess;
} Global;

// 判断棋型优先级
typedef struct Judge
{
	bool inHFir;
	bool inHThi;
	bool inHFou;
	bool inVFir;
	bool inVThi;
	bool inVFou;
	bool inLSFir;
	bool inLSThi;
	bool inLSFou;
	bool inRSFir;
	bool inRSThi;
	bool inRSFou;
} JudgeModel;