#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
int main(void)
{
    char map[50][50]={
                        "######",
                        "#O #  ",
                        "# ## #",
                        "#  # #",
                        "##   #",
                        "######",
                        };
    int i,x,y,p,q;
    int ch;
    x=1;y=1;p=1;q=5;
    printf("\t\t\t\t迷宫游戏\n");
    printf("操作方式:\n\tw为往上走\n\ts为往下走\n\ta为往左走\n\td为往右走\n");
   	printf("\n\n");
    for (i=0;i<6;i++){
    	printf("\t\t\t\t");
        puts(map[i]);
    }
    while(x!=p||y!=q)
    {
        ch=getch();
        switch(ch)
        {
        	case 's':
            {
                if(map[x+1][y]!='#')
                {                       
                    map[x][y]=' ';
                    x++;
                    map[x][y]='O';
                }
            }
            break;
            case 'w':
            {
                if(map[x-1][y]!='#')
                {                       
                    map[x][y]=' ';
                    x--;
                    map[x][y]='O';
                }
            }
            break;
            case 'a':
            {
                if(map[x][y-1]!='#')
                {                       
                    map[x][y]=' ';
                    y--;
                    map[x][y]='O';
                }
            }
            break;
            case 'd':
            {
                if(map[x][y+1]!='#')
                {                       
                    map[x][y]=' ';
                    y++;
                    map[x][y]='O';
                }
            }
		}
        system("cls");
        printf("\t\t\t\t迷宫游戏\n");
	    printf("操作方式:\n\tw为往上走\n\ts为往下走\n\ta为往左走\n\td为往右走\n");
	    printf("\n\n");
	    for (i=0;i<6;i++){
    		printf("\t\t\t\t");
        	puts(map[i]);
    	}
    }
    system("cls");
    printf("恭喜你，成功了！");
    return 0;
}
