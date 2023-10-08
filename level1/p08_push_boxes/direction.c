#include "head_push_box.h"

extern int now_x;
extern  int now_y;
extern int level;
extern int map[10][10];
int extern goal1_x,goal1_y,goal2_x,goal2_y,goal3_x,goal3_y,goal4_x,goal4_y,goal5_x,goal5_y;
int Up() {
    // 3 1 -> 1 3当人在空地
    if(3 == map[now_x][now_y])
    {
        if(1 == map[now_x - 1][now_y])
        {
            map[now_x - 1][now_y] = 3;
            map[now_x][now_y] = 1;
            return 1;
        } //3 4 -> 1 6
        else if(4 == map[now_x - 1][now_y])
        {
            map[now_x - 1][now_y] = 6;
            map[now_x][now_y] = 1;
            return 1;
        } //3 0 -> 3 0
        else if(0 == map[now_x - 1][now_y])
        {
            return 0;
        }
        else if(2 == map[now_x - 1][now_y])
        {
            //3 2 1 -> 1 3 2
            if(1 == map[now_x - 2][now_y])
            {
                map[now_x - 1][now_y] = 3;
                map[now_x][now_y] = 1;
                map[now_x - 2][now_y] =2;
                return 1;
            } // 3 2 4 -> 1 3 5
            else if(4 == map[now_x - 2][now_y])
            {
                map[now_x - 1][now_y] = 3;
                map[now_x][now_y] = 1;
                map[now_x - 2][now_y] =5;
                if(Finish())
                    return  2;
                return 1;
            } else
                return 0;
        }
        else if(5 == map[now_x - 1][now_y])
        {   //3 5 1->1 6 2
            if(1 == map[now_x - 2][now_y])
            {
                map[now_x - 1][now_y] = 6;
                map[now_x][now_y] = 1;
                map[now_x - 2][now_y] =2;
                return 1;
            } //3 5 4 -> 1 6 5
            else if(4 == map[now_x - 2][now_y])
            {
                map[now_x - 1][now_y] = 6;
                map[now_x][now_y] = 1;
                map[now_x - 2][now_y] =5;
                return 1;
            } else
                return 0;
        }
    }
    else if (6 == map[now_x][now_y])
    {
        //6 1 -> 4 3当人在目标点
        if(1 == map[now_x - 1][now_y])
        {
            map[now_x - 1][now_y] = 3;
            map[now_x][now_y] = 4;
            return 1;
        }//6 4 -> 4 6
        else if(4 == map[now_x - 1][now_y])
        {
            map[now_x - 1][now_y] = 6;
            map[now_x][now_y] = 4;
            return 1;
        }
        else if(0 == map[now_x - 1][now_y])
        {
            return 0;
        }
        else if(2 == map[now_x - 1][now_y])
        {
            //6 2 1 -> 4 3 2
            if(1 == map[now_x - 2][now_y])
            {
                map[now_x - 1][now_y] = 3;
                map[now_x][now_y] = 4;
                map[now_x - 2][now_y] =2;
                return 1;
            } // 6 2 4 -> 4 3 5
            else if(4 == map[now_x - 2][now_y])
            {
                map[now_x - 1][now_y] = 3;
                map[now_x][now_y] = 4;
                map[now_x - 2][now_y] =5;
                if(Finish())
                    return  2;
                return 1;
            } else
                return 0;
        }
        else if(5 == map[now_x - 1][now_y])
        {   //6 5 1->4 6 2
            if(1 == map[now_x - 2][now_y])
            {
                map[now_x - 1][now_y] = 6;
                map[now_x][now_y] = 4;
                map[now_x - 2][now_y] =2;
                return 1;
            } //6 5 4 -> 4 6 5
            else if(4 == map[now_x - 2][now_y])
            {
                map[now_x - 1][now_y] = 6;
                map[now_x][now_y] = 4;
                map[now_x - 2][now_y] =5;
                return 1;
            } else
                return 0;
        }
    }
}

int Down() {
    if(3 == map[now_x][now_y])
    {
        // 3 1 -> 1 3
        if(1 == map[now_x + 1][now_y])
        {
            map[now_x + 1][now_y] = 3;
            map[now_x][now_y] = 1;
            return 1;
        } //3 4 -> 1 6
        else if(4 == map[now_x + 1][now_y])
        {
            map[now_x + 1][now_y] = 6;
            map[now_x][now_y] = 1;
            return 1;
        } //3 0 -> 3 0
        else if(0 == map[now_x + 1][now_y])
        {
            return 0;
        }
        else if(2 == map[now_x + 1][now_y])
        {
            //3 2 1 -> 1 3 2
            if(1 == map[now_x + 2][now_y])
            {
                map[now_x + 1][now_y] = 3;
                map[now_x][now_y] = 1;
                map[now_x + 2][now_y] =2;
                return 1;
            } // 3 2 4 -> 1 3 5
            else if(4 == map[now_x + 2][now_y])
            {
                map[now_x + 1][now_y] = 3;
                map[now_x][now_y] = 1;
                map[now_x + 2][now_y] =5;
                if(Finish())
                    return  2;
                return 1;
            } else
                return 0;
        }
        else if(5 == map[now_x + 1][now_y])
        {   //3 5 1->1 6 2
            if(1 == map[now_x + 2][now_y])
            {
                map[now_x + 1][now_y] = 6;
                map[now_x][now_y] = 1;
                map[now_x + 2][now_y] =2;
                return 1;
            } //3 5 4 -> 1 6 5
            else if(4 == map[now_x + 2][now_y])
            {
                map[now_x + 1][now_y] = 6;
                map[now_x][now_y] = 1;
                map[now_x + 2][now_y] =5;
                return 1;
            } else
                return 0;
        }
        if(Finish())
            return  2;
    }
    else if(6 == map[now_x][now_y])
    {
        // 6 1 -> 4 3
        if(1 == map[now_x + 1][now_y])
        {
            map[now_x + 1][now_y] = 3;
            map[now_x][now_y] = 4;
            return 1;
        } //6 4 -> 4 6
        else if(4 == map[now_x + 1][now_y])
        {
            map[now_x + 1][now_y] = 6;
            map[now_x][now_y] = 4;
            return 1;
        } //6 0 -> 6 0
        else if(0 == map[now_x + 1][now_y])
        {
            return 0;
        }
        else if(2 == map[now_x + 1][now_y])
        {
            //6 2 1 -> 4 3 2
            if(1 == map[now_x + 2][now_y])
            {
                map[now_x + 1][now_y] = 3;
                map[now_x][now_y] = 4;
                map[now_x + 2][now_y] =2;
                return 1;
            } // 6 2 4 -> 4 3 5
            else if(4 == map[now_x + 2][now_y])
            {
                map[now_x + 1][now_y] = 3;
                map[now_x][now_y] = 4;
                map[now_x + 2][now_y] =5;
                if(Finish())
                    return  2;
                return 1;
            } else
                return 0;
        }
        else if(5 == map[now_x + 1][now_y])
        {   //6 5 1->4 6 2
            if(1 == map[now_x + 2][now_y])
            {
                map[now_x + 1][now_y] = 6;
                map[now_x][now_y] = 4;
                map[now_x + 2][now_y] =2;
                return 1;
            } //6 5 4 -> 4 6 5
            else if(4 == map[now_x + 2][now_y])
            {
                map[now_x + 1][now_y] = 6;
                map[now_x][now_y] = 4;
                map[now_x + 2][now_y] =5;
                return 1;
            } else
                return 0;
        }
        if(Finish())
            return  2;
    }
}

int Left() {
    if(3 == map[now_x][now_y])
    {
        // 3 1 -> 1 3
        if(1 == map[now_x][now_y - 1])
        {
            map[now_x][now_y - 1] = 3;
            map[now_x][now_y] = 1;
            return 1;
        } //3 4 -> 1 6
        else if(4 == map[now_x][now_y - 1])
        {
            map[now_x][now_y - 1] = 6;
            map[now_x][now_y] = 1;
            return 1;
        } //3 0 -> 3 0
        else if(0 == map[now_x][now_y - 1])
        {
            return 0;
        }
        else if(2 == map[now_x][now_y - 1])
        {
            //3 2 1 -> 1 3 2
            if(1 == map[now_x][now_y - 2])
            {
                map[now_x][now_y - 1] = 3;
                map[now_x][now_y] = 1;
                map[now_x ][now_y- 2] =2;
                return 1;
            } // 3 2 4 -> 1 3 5
            else if(4 == map[now_x][now_y - 2])
            {
                map[now_x][now_y - 1] = 3;
                map[now_x][now_y] = 1;
                map[now_x][now_y - 2] =5;
                if(Finish())
                    return  2;
                return 1;
            } else
                return 0;
        } else if(5 == map[now_x][now_y - 1])
        {   //3 5 1->1 6 2
            if(1 == map[now_x][now_y - 2])
            {
                map[now_x][now_y - 1] = 6;
                map[now_x][now_y] = 1;
                map[now_x][now_y - 2] =2;
                return 1;
            } //3 5 4 -> 1 6 5
            else if(4 == map[now_x][now_y] - 2)
            {
                map[now_x][now_y - 1] = 6;
                map[now_x][now_y] = 1;
                map[now_x][now_y - 2] =5;
                return 1;
            } else
                return 0;
        }
        if(Finish())
            return  2;
    }
    else if(6 == map[now_x][now_y])
    {
        // 6 1 -> 4 3
        if(1 == map[now_x][now_y - 1])
        {
            map[now_x][now_y - 1] = 3;
            map[now_x][now_y] = 4;
            return 1;
        } //6 4 -> 4 6
        else if(4 == map[now_x][now_y - 1])
        {
            map[now_x][now_y - 1] = 6;
            map[now_x][now_y] = 4;
            return 1;
        } //6 0 -> 6 0
        else if(0 == map[now_x][now_y - 1])
        {
            return 0;
        }
        else if(2 == map[now_x][now_y - 1])
        {
            //6 2 1 -> 4 3 2
            if(1 == map[now_x][now_y - 2])
            {
                map[now_x][now_y - 1] = 3;
                map[now_x][now_y] = 4;
                map[now_x ][now_y- 2] =2;
                return 1;
            } // 6 2 4 -> 4 3 5
            else if(4 == map[now_x][now_y - 2])
            {
                map[now_x][now_y - 1] = 3;
                map[now_x][now_y] = 4;
                map[now_x][now_y - 2] =5;
                if(Finish())
                    return  2;
                return 1;
            } else
                return 0;
        } else if(5 == map[now_x][now_y - 1])
        {   //6 5 1->4 6 2
            if(1 == map[now_x][now_y - 2])
            {
                map[now_x][now_y - 1] = 6;
                map[now_x][now_y] = 4;
                map[now_x][now_y - 2] =2;
                return 1;
            } //6 5 4 -> 4 6 5
            else if(4 == map[now_x][now_y] - 2)
            {
                map[now_x][now_y - 1] = 6;
                map[now_x][now_y] = 4;
                map[now_x][now_y - 2] =5;
                return 1;
            } else
                return 0;
        }
        if(Finish())
            return  2;
    }
}

int Right() {
    if(3 == map[now_x][now_y])
    {
        // 3 1 -> 1 3
        if(1 == map[now_x][now_y + 1])
        {
            map[now_x][now_y + 1] = 3;
            map[now_x][now_y] = 1;
            return 1;
        } //3 4 -> 1 6
        else if(4 == map[now_x][now_y + 1])
        {
            map[now_x][now_y + 1] = 6;
            map[now_x][now_y] = 1;
            return 1;
        } //3 0 -> 3 0
        else if(0 == map[now_x][now_y + 1])
        {
            return 0;
        }
        else if(2 == map[now_x][now_y + 1])
        {
            //3 2 1 -> 1 3 2
            if(1 == map[now_x][now_y + 2])
            {
                map[now_x][now_y + 1] = 3;
                map[now_x][now_y] = 1;
                map[now_x][now_y + 2] =2;
                return 1;
            } // 3 2 4 -> 1 3 5
            else if(4 == map[now_x][now_y + 2])
            {
                map[now_x][now_y + 1] = 3;
                map[now_x][now_y] = 1;
                map[now_x][now_y + 2] =5;
                if(Finish())
                    return  2;
                return 1;
            } else
                return 0;
        } else if(5 == map[now_x][now_y + 1])
        {   //3 5 1->1 6 2
            if(1 == map[now_x][now_y + 2])
            {
                map[now_x][now_y + 1] = 6;
                map[now_x][now_y] = 1;
                map[now_x][now_y + 2] =2;
                return 1;
            } //3 5 4 -> 1 6 5
            else if(4 == map[now_x][now_y + 2])
            {
                map[now_x][now_y + 1] = 6;
                map[now_x][now_y] = 1;
                map[now_x][now_y + 2] =5;
                return 1;
            } else
                return 0;
        }
        if(Finish())
            return  2;
    }
    else if(6 == map[now_x][now_y])
    {
        // 6 1 -> 4 3
        if(1 == map[now_x][now_y + 1])
        {
            map[now_x][now_y + 1] = 3;
            map[now_x][now_y] = 4;
            return 1;
        } //6 4 -> 4 6
        else if(4 == map[now_x][now_y + 1])
        {
            map[now_x][now_y + 1] = 6;
            map[now_x][now_y] = 4;
            return 1;
        } //6 0 -> 6 0
        else if(0 == map[now_x][now_y + 1])
        {
            return 0;
        }
        else if(2 == map[now_x][now_y + 1])
        {
            //6 2 1 -> 4 3 2
            if(1 == map[now_x][now_y + 2])
            {
                map[now_x][now_y + 1] = 3;
                map[now_x][now_y] = 4;
                map[now_x][now_y + 2] =2;
                return 1;
            } // 6 2 4 -> 4 3 5
            else if(4 == map[now_x][now_y + 2])
            {
                map[now_x][now_y + 1] = 3;
                map[now_x][now_y] = 4;
                map[now_x][now_y + 2] =5;
                if(Finish())
                    return  2;
                return 1;
            } else
                return 0;
        } else if(5 == map[now_x][now_y + 1])
        {   //6 5 1->4 6 2
            if(1 == map[now_x][now_y + 2])
            {
                map[now_x][now_y + 1] = 6;
                map[now_x][now_y] = 4;
                map[now_x][now_y + 2] =2;
                return 1;
            } //6 5 4 -> 4 6 5
            else if(4 == map[now_x][now_y + 2])
            {
                map[now_x][now_y + 1] = 6;
                map[now_x][now_y] = 4;
                map[now_x][now_y + 2] =5;
                return 1;
            } else
                return 0;
        }
        if(Finish())
            return  2;
    }
}
