#include <stdio.h>
#include <string.h>
#include "head_push_box.h"

extern  int step[5];
extern  int level;
extern int now_step;
extern int sure_step;

int Min_step(int l)
{

    Read();
    if(sure_step < step[l - 1])
    {
        step[l - 1] = sure_step;
    }
    return step[l - 1];
}
