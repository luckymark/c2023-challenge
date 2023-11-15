#include <stdio.h>
#include <stdlib.h>

//验证100以内的哥德巴赫猜想

int main()
{
	system("chcp 65001");
	//标记是否验证成功
	int test = 0;
	//100以内的素数
	int prime[25] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
					  31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
					  73, 79, 83, 89, 97 };
	//从4开始 自增2
	for (int i = 4; i < 101; i = i + 2)
	{
		//从0开始遍历素数数组
		for (int j = 0; j <= 24; j++)
		{
			int c = i - prime[j];
			//判断某个数减去一个素数后差是否为素数
			for (int k = 0; k <= 24; k++)
			{
				if (c == prime[k])
				{
					test = 1;
					break;
				}
			}
			//当q以1传出说明验证成立跳出换一个数验证
			if (test == 1)
				break;
		}
		//若以0传出说明对比完仍不成立,跳出循环
		if (test == 0)
			break;
	}
	if (test == 1)
		printf("哥德巴赫猜想100以内正确。\n");
	if (test == 0)
		printf("哥德巴赫猜想100以内错误。\n");
	return 0;
}