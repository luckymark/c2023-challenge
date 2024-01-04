#include "head_push_box.h"

extern int min_step[5];
//记录最小步数
void Note()
{
    FILE *score = fopen("C:\\Users\\81201\\CLionProjects\\c2023-challenge\\level1\\p08_push_boxes\\score.txt", "w");
    if(score == NULL)
    {
        perror("open failed:");
    }
    fprintf(score,"%d %d %d %d %d\n",min_step[0],min_step[1],min_step[2],min_step[3],min_step[4]);
    fclose(score);
}