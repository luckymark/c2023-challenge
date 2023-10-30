//
// Created by 14212 on 2023/9/22.
//

#ifndef C2023_CHALLENGE_GAME_H
#define C2023_CHALLENGE_GAME_H
void init_maze(char ch[][30]);
int sum(int down,int up,int left,int right);
void change(char (*ch)[30],int mm,int * a,int * b,int m,int n);
#endif //C2023_CHALLENGE_GAME_H 
