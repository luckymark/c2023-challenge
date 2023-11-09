#include "GA.h"
int main(){
    int maze[26][26]={0};//暂时是从左上角走到右下角，尝试输入任意地址形成路径
    int num=15;//最后再改成输入一个数得到结果。
    const int GENE_LENGTH=num*num;
    static ind chromosome[GROUP_SIZE+1];
    srand(time(0));
    init_maze(maze,num);
    init_group(chromosome,GENE_LENGTH);
    print_maze(maze,num);
    printf("\n");
    count_fitness(chromosome,maze,num,GENE_LENGTH);//子代的count_fitness可以优化
    all_percent_(chromosome);
    //print_group(chromosome,GENE_LENGTH,0);
    for(int i=1;i<=CIRCLE_TIME;i++){
        roulette(chromosome,GENE_LENGTH);
        count_fitness(chromosome,maze,num,GENE_LENGTH);//子代的count_fitness可以优化
        all_percent_(chromosome);
        //if(i==1)
           // print_group(chromosome,GENE_LENGTH,i);
    }
    //print_group(chromosome,GENE_LENGTH,0);
    print_result(&chromosome[1],maze,num,GENE_LENGTH);
    system("pause");
    return 0;
}
