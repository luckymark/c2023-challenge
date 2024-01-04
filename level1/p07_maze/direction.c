extern int now_x;
extern  int now_y;
extern int map[101][101];


int Up()
{
    if(1 == map[now_x - 1][now_y])
    {
        map[now_x][now_y] = 1;
        map[now_x - 1][now_y] = 3;
        return 1;
    }
    else if(4 == map[now_x - 1][now_y])
        return 2;
    else if(0 == map[now_x - 1][now_y])
        return 0;

}
int Down()
{
    if(1 == map[now_x + 1][now_y])
    {
        map[now_x][now_y] = 1;
        map[now_x + 1][now_y] = 3;
        return 1;
    }
    else if(4 == map[now_x + 1][now_y])
        return 2;
    else if(0 == map[now_x + 1][now_y])
        return 0;
}
int Left()
{
    if(1 == map[now_x][now_y - 1])
    {
        map[now_x][now_y] = 1;
        map[now_x][now_y - 1] = 3;
        return 1;
    }
    else if(4 == map[now_x][now_y - 1])
        return 2;
    else if(0 == map[now_x][now_y - 1])
        return 0;
}
int Right()
{
    if(1 == map[now_x][now_y + 1])
    {
        map[now_x][now_y] = 1;
        map[now_x][now_y + 1] = 3;
        return 1;
    }
    else if(4 == map[now_x][now_y + 1])
        return 2;
    else if(0 == map[now_x][now_y + 1])
        return 0;
}
