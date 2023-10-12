
#include <stdio.h>
extern int step[5];

void Read()
{
    FILE *score = fopen("C:\\Users\\81201\\CLionProjects\\c2023-challenge\\level1\\p08_push_boxes\\score.txt", "r");
    if(score == NULL)
    {
        perror("open failed:");
    }
    fscanf_s(score,"%d %d %d %d %d\n",&step[0],&step[1],&step[2],&step[3],&step[4]);
    fclose(score);
}