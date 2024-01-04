#include <stdio.h>


//输出一次移动的过程
void move(char A, char B)
{
	printf("%c -> %c\n", A, B);
}
//把A通过B移动到C
void hano(int n, char A, char B, char C)
{
	if (n == 1)
	{
		move(A, C);
	}
	else
	{
		hano(n - 1, A, C, B);
		move(A, C);
		hano(n - 1, B, A, C);
	}
}

int main()
{
	//输入盘子的个数
	printf("请输入盘子的个数：");
	int n;
	scanf("%d", &n);
	hano(n, 'A', 'B', 'C');
	return 0;
}