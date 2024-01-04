#ifndef PUSHBOX_H
#define PUSHBOX_H

#include <stdio.h>
#include <windows.h>

#define SP_SIGN  224
#define UP       72
#define DOWN     80
#define LEFT     75
#define RIGHT    77
#define BARRIER  0
#define PATH     1
#define BOX      2
#define TARGET   3
#define PLAYER   4
#define FINISHED_TARGET 5

typedef struct Pos
{
    int x;
    int y;
}pos;

extern HANDLE HdOut;
extern bool   WIN;
extern FILE*  file;
extern int    mp[20][20];

void MoveCursor(int x,int y);
void InitMap(char *path,int width,int highth);
void move(int op);
void win(char *FileName);
void over();

#endif