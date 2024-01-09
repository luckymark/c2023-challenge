//
// Created by 14212 on 2023/10/14.
//

#ifndef C2023_CHALLENGE_WAREHOUSE_H
#define C2023_CHALLENGE_WAREHOUSE_H
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#include<time.h>
void init_print(void);
void show_list(FILE *);
int warehouse(FILE *);
int research(FILE *,char *,int);
void print_time(FILE *);
int bring_out(FILE *);
#endif //C2023_CHALLENGE_WAREHOUSE_H
