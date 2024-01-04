#include <stdio.h>
#include <string.h>



int main(int l)
{
    int steps[][5] = { 0 };
    int min = 0,i = 0;
    FILE *score = fopen("C:\\Users\\81201\\CLionProjects\\c2023-challenge\\level1\\p08_push_boxes\\score.txt", "r");
    if(score == NULL)
    {
        perror("open failed:");
        return 0;
    }
    while (!feof(score))
    {
        fscanf(score,"%d %d %d %d %d",&steps[i][0],&steps[i][1],&steps[i][2],&steps[i][3],&steps[i][4]);
        i++;
    }

    fclose(score);
    for (int j = 0; j < 5; j++)
    {
        printf("%d %d %d %d %d\n",steps[j][0],steps[j][1],steps[j][2],steps[j][3],steps[j][4]);
        if(0 == steps[j + 1][0] && 0 == steps[j + 1][1] && 0 == steps[j + 1][2] && 0 == steps[j + 1][3] && 0 == steps[j + 1][4])
            break;
    }
    system("pause");
    return 0;
}
