
#include "head_push_box.h"

char str[(15) * (15)] = { '\0' };//输出地图用的数组
int now_x, now_y;//储存当前所在位置
int level = 0;//游戏等级
int min_step[5] = { 0 }, now_step = 0;//记录移动次数即得分
//-1-空地，0-墙，1-路，2-箱子，3-人，4-目标，5-达成目标
int map[10][10] = { 0 };
//用数组存六个Goal类型的结构体
Goal goal[5];
//每个关卡的目标数量
int goal_num[5] = { 4, 3, 4, 5, 3, };
int main()
{
	int flag = 0;
	system("chcp 65001");
loopMenu:
	Menu();
loop:
	while (1)
	{
		//等级5完成就通关
		if (6 == level)
		{
			MessageBoxW(NULL, L"恭喜您已经通关所有关卡", L"恭喜！", MB_OK);
			Note();
			return 0;
		}
		//读取最小步数
		Read();
		Print();
		while (1)
		{
			flag = Push();
			//1->成功一个关卡且不再进行  -1 ->本次运行结束
			if (1 == flag || -1 == flag)
			{
				Note();
				return 0;
			}
				//2->成功一个关卡且继续进行  3->重玩关卡
			else if (2 == flag || 3 == flag)
			{
				Map(level);
				break;
			}
				//4->跳过关卡
			else if (4 == flag)
			{
				level++;
				Map(level);
				break;
			}
				//5->返回主菜单
			else if (5 == flag)
			{
				goto loopMenu;
			}
				//6->退出游戏
			else if (6 == flag)
			{
				Note();
				return 0;
			}
				//7->返回上一个关卡
			else if (7 == flag)
			{
				level--;
				Map(level);
				goto loop;
			}
			else
			{
				continue;
			}
		}
	}
}