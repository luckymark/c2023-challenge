//
// Created by Cz_13 on 2023/10/26.
//

#ifndef LEVEL2_MAZE_H
#define LEVEL2_MAZE_H

#include "conio.h"
#include "time.h"
#include "stack.h"
#include "string.h"

typedef struct Maze{
    char **maze;
    int length;
    int width;
    int *player;
    int *destination;
    int (*player_move)(struct Maze *maze, int mode);
    int (*get_access_num)(struct Maze *maze);
    void (*reset)(struct Maze *maze);
} Maze;

extern Maze *create_maze(int length, int width);
extern void print_maze(Maze *);

#endif //LEVEL2_MAZE_H
