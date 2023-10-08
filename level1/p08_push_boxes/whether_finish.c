
extern int level;
extern int map[10][10];
int extern goal1_x,goal1_y,goal2_x,goal2_y,goal3_x,goal3_y,goal4_x,goal4_y,goal5_x,goal5_y;

//目标点全完成则关卡成功
int Finish()
{

    if(1 == level)
    {
        if(5 == map[goal1_x][goal1_y] && 5 == map[goal2_x][goal2_y] && 5 == map[goal3_x][goal3_y] && 5 == map[goal4_x][goal4_y])
        {
            return 1;
        } else
            return 0;
    }
    if(2 == level)
    {
        if(5 == map[goal1_x][goal1_y] && 5 == map[goal2_x][goal2_y] && 5 == map[goal3_x][goal3_y])
        {
            return 1;
        } else
            return 0;
    }
    if(3 == level)
    {
        if(5 == map[goal1_x][goal1_y] && 5 == map[goal2_x][goal2_y] && 5 == map[goal3_x][goal3_y] && 5 == map[goal4_x][goal4_y])
        {
            return 1;
        } else
            return 0;
    }
    if(4 == level)
    {
        if(5 == map[goal1_x][goal1_y] && 5 == map[goal2_x][goal2_y] && 5 == map[goal3_x][goal3_y] && 5 == map[goal4_x][goal4_y] && 5 == map[goal5_x][goal5_y])
        {
            return 1;
        } else
            return 0;
    }
    if(5 == level)
    {
        if(5 == map[goal1_x][goal1_y] && 5 == map[goal2_x][goal2_y] && 5 == map[goal3_x][goal3_y])
        {
            return 1;
        } else
            return 0;
    }
}