#include <stdio.h>

int Count=0;
void Move(int n, char From, char To, char Help)
{
    if (n==1)
        printf("%c -> %c\r\n", From, To);
    else
    {
        Move(n - 1, From,Help,To);
        printf("%c -> %c\r\n", From, To);
        Move(n - 1, Help,To,From);
    }
    //printf("-----------------\r\n");
    Count++;
}
int main()
{
    int n = 0;
    printf("Hanoi Level n=");
    scanf("%d", &n);
    Move(n, 'A', 'B', 'C');
    printf("Finished within %d steps.",Count);
    return 0;
}
