#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main()
{
	//输出中文
	system("chcp 65001");
	int n;
	printf("请输入一个数字n:\n");
	scanf("%d", &n);
	//计算中间量减少运算次数
	float b = pow(n, 0.5);
	//判断素数
	for (int i = 2; i < b; i++)
	{
		if (n % i == 0)
		{
			printf("这个数不是素数。");
			return 0;
		}
	}
	//所有的数都不能整除，那么这个数就是素数
	printf("这个数是素数。");
	return 0;
}