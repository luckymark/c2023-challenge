#include <stdbool.h>
extern int map[101][101];
extern int large;
bool HaveNeighbor(int x,int y)
{
    //有“邻居”则返回1，否则返回0
    if((x >= 3 && map[x - 2][y] == 1) || (x < large - 3 && map[x + 2][y] == 1) || (y >= 3 && map[x][y - 2] == 1) || (y <= large - 2 && map[x][y + 2] == 1))
        return 1;
    return 0;
}