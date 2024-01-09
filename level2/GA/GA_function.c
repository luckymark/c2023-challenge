//
// Created by 14212 on 2023/10/31.
//
#include "GA.h"
void init_maze(int (* maze)[26],int num){
    for(int i=1;i<=num;i++){
        for(int j=1;j<=num;j++){
            double percent=(rand()%1000)*0.001;
            if(percent<=0.7)
                maze[i][j]=0;
            else
                maze[i][j]=1;
        }
    }
    maze[1][1]=1;
    maze[num][num]=0;
}
void init_group(ind * chromosome,const int GENE_LENGTH){
    for(int i=1;i<=GROUP_SIZE;i++){
        for(int j=1;j<=GENE_LENGTH;j++){
            chromosome[i].data[j]=rand()%4;
            chromosome[i].vary_percent[j]=0;
        }
        chromosome[i].now_bit=0;
        chromosome[i].now_x=1;
        chromosome[i].now_y=1;
        chromosome[i].fitness=0;
        chromosome[i].ifsuccess=0;
        chromosome[i].two_time=0;
    }
}
void print_maze(int (* maze)[26],int num){
    for(int i=1;i<=num;i++){
        for(int j=1;j<=num;j++){
            printf("%d ",maze[i][j]);
        }
        printf("\n");
    }
}
void print_group(ind * chromosome,const int GENE_LENGTH,int num){
    printf("\n");
    printf("The %d :\n",num);
    for(int i=1;i<=GROUP_SIZE;i++){
        for(int j=1;j<=GENE_LENGTH;j++){
            printf("%d",chromosome[i].data[j]);
        }
        printf("%5d%5d%10.5f%10.5f",chromosome[i].fitness,chromosome[i].ifsuccess,chromosome[i].start_percent,chromosome[i].end_percent);
        printf("\n");
        for(int j=1;j<=GENE_LENGTH;j++){
            printf("%d",chromosome[i].vary_percent[j]);
        }
        printf("\n");
    }
}
void count_fitness(ind * chromosome,int (* maze)[26],int num,const int GENE_LENGTH){
    for(int i=1;i<=GROUP_SIZE;i++){
        int maze_copy[26][26];
        for(int k=1;k<=num;k++){
            for(int p=1;p<=num;p++){
                maze_copy[k][p]=maze[k][p];
            }
        }
        move(&chromosome[i],maze_copy,GENE_LENGTH,num);
        if(chromosome[i].ifsuccess==1)
            move_again(&chromosome[i],maze_copy,GENE_LENGTH,num);
        fitness(&chromosome[i],num);
    }
    Select_Sort(chromosome);
}
void move(ind * chromosome,int (* maze_copy)[26],const int GENE_LENGTH,int num){
    for(int i=1;i<=GENE_LENGTH;i++){//chromosome在这里是染色体的一条
        if(chromosome->ifsuccess==1)
            return;
        switch(chromosome->data[i]){
            case 0:check(chromosome,maze_copy,-1,0,num);
                    break;
            case 1:check(chromosome,maze_copy,1,0,num);
                    break;
            case 2:check(chromosome,maze_copy,0,-1,num);
                    break;
            case 3:check(chromosome,maze_copy,0,1,num);
                    break;
            //default:理论上应该不会有
        }
    }
}
void check(ind * chromosome,int (* maze_copy)[26],int move_y,int move_x,int num){
    if(chromosome->now_x+move_x<1||chromosome->now_y+move_y<1||chromosome->now_x+move_x>num||chromosome->now_y+move_y>num||
            maze_copy[chromosome->now_y+move_y][chromosome->now_x+move_x]==1||maze_copy[chromosome->now_y+move_y][chromosome->now_x+move_x]==8){
        chromosome->now_bit++;
        return;
    }
    chromosome->now_y+=move_y;
    chromosome->now_x+=move_x;
    maze_copy[chromosome->now_y][chromosome->now_x]=8;
    chromosome->now_bit++;
    chromosome->vary_percent[chromosome->now_bit]=1;
    if(chromosome->now_x==num&&chromosome->now_y==num)
        chromosome->ifsuccess=1;
}
void fitness(ind * chromosome,int num){
    if(chromosome->ifsuccess==1){
        chromosome->fitness=num*num+2*num-1-chromosome->now_bit+50-chromosome->two_time;
    }
    else{
        chromosome->fitness=2*num-2-(num-(chromosome->now_x)+num-(chromosome->now_y))+1;
    }
}
void Select_Sort(ind * chromosome){
    for(int i=1;i<GROUP_SIZE;i++){
        int temp=i;
        for(int j=i+1;j<=GROUP_SIZE;j++){
            if(chromosome[j].fitness>chromosome[temp].fitness){
                temp=j;
            }
        }
        if(temp!=i){
            ind p=chromosome[temp];
            chromosome[temp]=chromosome[i];
            chromosome[i]=p;
        }
    }
}
void all_percent_(ind * chromosome){
    long long all_fitness=0;
    for(int i=1;i<=GROUP_SIZE;i++){
        all_fitness+=chromosome[i].fitness;
    }
    long long before_fitness=0;
    for(int i=1;i<=GROUP_SIZE;i++){
        chromosome[i].start_percent=(double)before_fitness/(double)all_fitness;
        before_fitness+=chromosome[i].fitness;
        chromosome[i].end_percent=(double)before_fitness/(double)all_fitness;
    }
}
void roulette(ind * chromosome,const int GENE_LENGTH){
    ind son_gen[GROUP_SIZE+1];
    for(int i=1;i<=ELITE;i++){
        son_gen[i]=chromosome[i];
    }
    for(int o=ELITE+1;o<=GROUP_SIZE;o+=4) {
        double p = (rand() % 1000) * 0.001;
        ind s_1, s_2;
        int l,i;
        for (l = 1; l <= GENE_LENGTH; l++) {
            if ((l != 1 && p > chromosome[l].start_percent && p <= chromosome[l].end_percent) ||
                (l == 1 && p >= chromosome[l].start_percent && p <= chromosome[l].end_percent)) {
                s_1 = chromosome[l];
                break;
            }
        }
        do {
            p = (rand() % 1000) * 0.001;
            for (i = 1; i <= GENE_LENGTH; i++) {
                if ((i != 1 && p > chromosome[i].start_percent && p <= chromosome[i].end_percent) ||
                    (i == 1 && p >= chromosome[i].start_percent && p <= chromosome[i].end_percent)) {
                    s_2 = chromosome[i];
                    break;
                }
            }
        }while(l==i);
        son_gen[o]=s_1;
        son_gen[o+1]=s_2;
        exchange(&s_1,&s_2,GENE_LENGTH);
        vary(&s_1,GENE_LENGTH);
        vary(&s_2,GENE_LENGTH);
        son_gen[o+2]=s_1;
        son_gen[o+3]=s_2;
    }
    for(int o=1;o<=GROUP_SIZE;o++){
        chromosome[o]=son_gen[o];
        chromosome[o].now_x=1;
        chromosome[o].now_y=1;
        chromosome[o].now_bit=0;
        chromosome[o].ifsuccess=0;
        chromosome[o].two_time=0;
        for(int j=1;j<=GENE_LENGTH;j++){
            chromosome[o].vary_percent[j]=0;
        }
    }
}
void exchange(ind * s_1,ind * s_2,const int GENE_LENGTH){
    int start_1=rand()%(GENE_LENGTH/2)+1;
    int length_1=rand()%(GENE_LENGTH/4)+1;
    int i;
    for(i=start_1;i<start_1+length_1;i++){
        int temp=s_1->data[i];
        s_2->data[i]=s_1->data[i];
        s_1->data[i]=temp;
    }
    int start_2=rand()%(GENE_LENGTH/2)+1;
    i=i+start_2-1;
    int end_2=rand()%(GENE_LENGTH/4)+i+1;
    for(;i<end_2&&i<=GENE_LENGTH;i++){
        int temp=s_1->data[i];
        s_2->data[i]=s_1->data[i];
        s_1->data[i]=temp;
    }
}
void vary(ind * s,const int GENE_LENGTH){
    for(int i=1;i<=GENE_LENGTH;i++){
        double p=(rand()%1000)*0.001;
        if(p>=0&&p<=0.5||s->vary_percent[i]==2){
            int y=s->data[i];
            while(y!=s->data[i])
                s->data[i]=rand()%4;
        }
    }
}
void print_result(ind * chromosome,int (* maze)[26],int num,const int GENE_LENGTH){
    if(chromosome->ifsuccess==0)
        printf("There is no way!\n");
    else{
        chromosome->now_y=1;
        chromosome->now_x=1;
        chromosome->now_bit=1;
        maze[1][1]=8;
        while(chromosome->now_x!=num||chromosome->now_y!=num){
            switch(chromosome->data[chromosome->now_bit]){
                case 0:check_result(chromosome,maze,-1,0,num);
                        break;
                case 1:check_result(chromosome,maze,1,0,num);
                    break;
                case 2:check_result(chromosome,maze,0,-1,num);
                    break;
                case 3:check_result(chromosome,maze,0,1,num);
                    break;
            }
            maze[chromosome->now_y][chromosome->now_x]=8;
        }
        for(int i=1;i<=num;i++){
            for(int j=1;j<=num;j++){
                printf("%d ",maze[i][j]);
            }
            printf("\n");
        }
    }
}
void check_result(ind * chromosome,int (* maze)[26],int move_y,int move_x,int num){
    if(chromosome->now_x+move_x<1||chromosome->now_y+move_y<1||chromosome->now_x+move_x>num||chromosome->now_y+move_y>num||
       maze[chromosome->now_y+move_y][chromosome->now_x+move_x]==1||maze[chromosome->now_y+move_y][chromosome->now_x+move_x]==8){
        chromosome->now_bit++;
        return;
    }
    chromosome->now_y+=move_y;
    chromosome->now_x+=move_x;
    chromosome->now_bit++;
}
void move_again(ind * chromosome,int (* maze_copy)[26],const int GENE_LENGTH,int num){
    int copy_x=1;
    int copy_y=1;
    for(int i=1;i<=chromosome->now_bit;i++){
        if(chromosome->vary_percent[i]!=1)
            continue;
        else{
            switch(chromosome->data[i]){
                case 0:if(copy_y-1>=1)
                    copy_y--;
                    break;
                case 1:
                    if(copy_y+1<=num)
                    copy_y++;
                    break;
                case 2:
                    if(copy_x-1>=1)
                    copy_x--;
                    break;
                case 3:
                    if(copy_x+1<=num)
                    copy_x++;
                    break;
            }
        }
        int k=0;
        if(copy_y-1>=1&&maze_copy[copy_y-1][copy_x]==8)
            k++;
        if(copy_y+1<=num&&maze_copy[copy_y+1][copy_x]==8)
            k++;
        if(copy_x-1>=1&&maze_copy[copy_y][copy_x-1]==8)
            k++;
        if(copy_x+1<=num&&maze_copy[copy_y][copy_x+1]==8)
            k++;
        if(k>=3) {
            chromosome->two_time++;
            chromosome->vary_percent[i]=2;
        }
    }
}