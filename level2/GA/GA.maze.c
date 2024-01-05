#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include"maze.c"

#define ROWS 10
#define COLS 10
#define POP_SIZE 100
#define MAX_GEN 500
#define MUTATION_RATE 0.01

// 迷宫地图
int maze[ROWS][COLS] = {};  //进行初始化
maze[ROWS][COLS]=Maze[][10];
typedef struct {
    int x, y;
} Point;

typedef struct {
    Point path[ROWS*COLS];
    int length;
    double fitness;
} Individual;

Individual population[POP_SIZE];

// 计算适应度
double calculate_fitness(Individual* ind) {
    return 1.0 / (ind->length + 1);  // 加1是为了避免除数为0的情况
}

// 初始化种群
void initialize_population() {
    for (int i = 0; i < POP_SIZE; i++) {
        population[i].length = 0;
        population[i].fitness = 0;
    }
}

// 选择操作
int select_index() {
    double total_fitness = 0;
    for (int i = 0; i < POP_SIZE; i++) {
        total_fitness += population[i].fitness;
    }
    double r = (double)rand() / RAND_MAX * total_fitness;
    double sum = 0;
    for (int i = 0; i < POP_SIZE; i++) {
        sum += population[i].fitness;
        if (sum >= r) return i;
    }
    return POP_SIZE - 1;  // 为了确保返回一个有效的索引
}

// 交叉操作
void crossover(Individual* parent1, Individual* parent2, Individual* child1, Individual* child2) {
    int index1 = rand() % (parent1->length - 1) + 1;  // 保证至少有一个点被交叉
    int index2 = rand() % (parent1->length - index1) + index1;  // 保证index2 > index1
    for (int i = 0; i < index1; i++) {
        child1->path[i] = parent1->path[i];
        child2->path[i] = parent2->path[i];
    }
    for (int i = index1; i < index2; i++) {
        child1->path[i] = parent2->path[i];
        child2->path[i] = parent1->path[i];
    }
    for (int i = index2; i < parent1->length; i++) {
        child1->path[i] = parent1->path[i];
        child2->path[i] = parent2->path[i];
    }
    child1->length = child2->length = parent1->length;
    child1->fitness = calculate_fitness(child1);
    child2->fitness = calculate_fitness(child2);
}

// 变异操作
void mutate(Individual* ind) {
    if (rand() / (double)RAND_MAX < MUTATION_RATE) {
        int index = rand() % ind->length;
        // 未完待续
    }
}

int main() {
    srand(time(NULL));  // 设置随机种子
    initialize_population();  // 初始化种群，可以将起点加入每个个体的路径中，并计算适应度等。
    for (int gen = 0; gen<1000;gen++){
     crossover(parent1,  parent2, child1, child2);
      mutate(ind)
     calculate_fitness(Individual* ind);
      select_index() ;
}//未完善route的换算
return 0;
      }
