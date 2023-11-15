#include <stdio.h>
#include <time.h>
#include <math.h>
#include <windows.h>

int main()
{
	system("chcp 65001");
	//定义素数判断的变量
	int prime;
	//定义时间计算的变量
	clock_t start, end;
	printf("2 ");
	//计时开始
	start = clock();
	//判断3-1000之间的某些数字是否是素数
	for (int n = 3; n < 1001; n++)
	{
		prime = 1;
		//定义中间变量减少运算次数
		double b = pow(n, 0.5);
		for (int i = 2; i <= b; i++)
		{
			if (n % i == 0)
			{
				prime = 0;
				break;
			}
		}
		if (prime == 1)
			printf("%d ", n);
	}
	end = clock();
	printf("\n");
	printf("计算时间为：%f 秒\n", (double)(end - start) / CLOCKS_PER_SEC);
	return 0;
}