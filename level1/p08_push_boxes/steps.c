//未能实现的设想
//#include <stdio.h>
//
//
//extern  int step[5][5];
//
//int Min_step(int l)
//{
//    int now_step[5] = { 0 };
//    now_step[l -1] = 100;
//    FILE *score = fopen("C:\\Users\\81201\\CLionProjects\\c2023-challenge\\level1\\p08_push_boxes\\score.txt", "r");
//    if(score == NULL)
//    {
//        perror("open failed:");
//        return 0;
//    }
//    int n = 0;
//    while (!feof(score))
//    {
//        fscanf(score, "%d %d %d %d %d", &step[n][0], &step[n][1], &step[n][2], &step[n][3], &step[n][4]);
//        n++;
//    }
//    step[l - 1][0] = step[l - 1][1];
//    step[l - 1][1] = step[l - 1][2];
//    step[l - 1][2] = step[l - 1][3];
//    step[l - 1][3] = step[l - 1][4];
//    step[l - 1][4] = now_step[l - 1];
//    fclose(score);
//
//    FILE *score1 = fopen("C:\\Users\\81201\\CLionProjects\\c2023-challenge\\level1\\p08_push_boxes\\score.txt", "w");
//    if(score == NULL)
//    {
//        perror("open failed:");
//        return 0;
//    }
//    n = 0;
//    fprintf(score, "%d %d %d %d %d\n", step[n][0], step[n][1], step[n][2], step[n][3], step[n][4]);
//    n++;
//    fprintf(score, "%d %d %d %d %d\n", step[n][0], step[n][1], step[n][2], step[n][3], step[n][4]);
//    n++;
//    fprintf(score, "%d %d %d %d %d\n", step[n][0], step[n][1], step[n][2], step[n][3], step[n][4]);
//    n++;
//    fprintf(score, "%d %d %d %d %d\n", step[n][0], step[n][1], step[n][2], step[n][3], step[n][4]);
//    n++;
//    fprintf(score, "%d %d %d %d %d\n", step[n][0], step[n][1], step[n][2], step[n][3], step[n][4]);
//    fclose(score1);
//
//    int min[5] = {99999999,99999999,99999999,99999999,99999999};
//    for(int i = 0;i < 5;i++)
//    {
//        for(int j = 0;j < 5;j++)
//        {
//            if(min[i] > step[i][j])
//            {
//                min[i] = step[i][j];
//            }
//        }
//    }
//    return min[l - 1];
//}
