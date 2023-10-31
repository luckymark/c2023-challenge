#include "maze.h"

#define P 400           // 群体中包含的假设数量
#define DNA_BIT 512    // 最高允许行动128步, 每步2bit, 00: 向上, 01: 向下, 10: 向左, 11: 向右
#define DNA_NUM 15
#define Generate_Num 500

#define UP1 72
#define DOWN1 80
#define LEFT1 75
#define RIGHT1 77


const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;

const double R = 0.75;   // 每一步中通过交叉取代群体成员的比例
const double M = 0.1; // 变异率
int now_generate_num = 1;

const int successful_match = 5; // 地图嗅探正确, 加五分
const int successful_move = 5;  // 成功移动, 加五分

typedef struct {
    int *dna_bit[DNA_NUM];   // 总共有16种状态, 故设计16条DNA
} DNA;

typedef struct {
    int id;
    DNA* dna;    // 操作步骤的二进制编码
    int score;  // 适应度
    int *dna_res[DNA_NUM];   // dna解码后的数据
} Animal;

Animal **animals; // 群体

int fitness(Maze* maze, int index);  // 适应度评估函数
void crossover(Animal *father, Animal *mother);    // 交叉算子
void mutation(Animal *animal);  // 变异算子
DNA* generate_DNA(Animal *animal);  // 编码DNA, 随机生成步骤
int** DNA_decode(Animal*);    // 解码DNA,通过DNA的二进制值来生成步骤
void init_population();
void print_animal(int index);
void select();
void sort();
int select_max_index();

int getKeyboardEvent(Maze *maze);

int length = 7;
int width = 7;
int **access_table;
int max_fitness[Generate_Num][2] = {0};

int move_mode4dna[15][5] = {
        // 对于每种地图状态所能拿到的通过方式, 由于编码方式的定义, 通过方式即为状态的二进制的反码
        {1, 1, 1, 1, 4},
        {1, 1, 1, 0, 3},
        {1, 1, 0, 1, 3},
        {1, 1, 0, 0, 2},
        {1, 0, 1, 1, 3},
        {1, 0, 1, 0, 2},
        {1, 0, 0, 1, 2},
        {1, 0, 0, 0, 1},
        {0, 1, 1, 1, 3},
        {0, 1, 1, 0, 2},
        {0, 1, 0, 1, 2},
        {0, 1, 0, 0, 1},
        {0, 0, 1, 1, 2},
        {0, 0, 1, 0, 1},
        {0, 0, 0, 1, 1}
        //{0, 0, 0, 0, 0}
};

int main(){
    /*
     * 不考虑什么解耦了, 能跑就行
     */

    Maze *maze = create_maze(length, width);
    putchar('\n');
    init_population();  // 初始化种群
    print_maze(maze);
    access_table = (int **) malloc(sizeof(int *) * (length * 2 + 1));
    for(int i = 0; i < length * 2 + 1; i ++){
        access_table[i] = (int *)malloc(sizeof(int) * (width * 2 + 1));
    }
    for(int i = 0; i < maze -> length * 2 + 1; i ++){
        for(int j = 0; j < maze -> width * 2 + 1; j ++){
            if(maze->maze[i][j] != '#'){
                // 计算每一个点的状态
                maze->player[0] = i;
                maze->player[1] = j;
                access_table[i][j] = maze->get_access_num(maze);
            }
        }
    }


    do {
        // 评估适应度
        for(int i = 0; i < P; i ++){
            animals[i]->score = fitness(maze, i);
        }
        int m_index = select_max_index();
        max_fitness[now_generate_num - 1][0] = animals[m_index]->score;
        max_fitness[now_generate_num - 1][1] = animals[m_index]->id;
        // printf("123123123");
        select();
        printf("count: %d\n", now_generate_num);
    } while (now_generate_num++ < Generate_Num);

    // 最后评估一次适应度
    for(int i = 0; i < P; i ++){
        animals[i]->score = fitness(maze, i);
    }
    // 输出地图
    system("cls");
    print_maze(maze);
    // 输出得分前十的个体
    sort();
    for(int i = 0; i < P; i ++){
        printf("第 %d 名得分: %d\n", i + 1, animals[i]->score);
    }
    for(int i = 0; i < 10; i ++){
        printf("排名: %d 的个体数据如下: \n", i + 1);
        print_animal(i);
        putchar('\n');
    }
    printf("每百代代最优如下: \n");
    for(int i = 0; i < Generate_Num; i += 100){
        printf("%d: %d.\n", max_fitness[i][1], max_fitness[i][0]);
    }

    /*for(int i = 0; i < P; i ++){
        if(animals[i]->id == 734){
            printf("734 号个体得分: %d\n", animals[i]->score);
            break;
        }
    }*/

    while(1){
        printf("选择需要演示的个体: ");
        int choose_num;
        scanf("%d", &choose_num);
        if(choose_num == -1){
            break;
        }
        int **move_mode = DNA_decode(animals[choose_num - 1]);
        int access;
        int move_num[DNA_NUM] = {0};
        for(int i = 0; i < DNA_BIT / 2; i ++){
            system("cls");
            access = access_table[maze->player[0]][maze->player[1]];
            int mode = move_mode[access][move_num[access] ++ ];
            if(maze->player_move(maze, mode) == 1){
                printf("到达终点");
                break;
            }
            print_maze(maze);
            printf("按下任意键继续");
            getchar();
        }
        maze -> reset(maze);
    }
    getchar();
    return 0;
}

void init_population(){
    system("chcp 65001");
    system("cls");
    //printf("init start\n");
    // srand(time(0));
    srand(0);
    animals = (Animal **) malloc(sizeof(Animal *) * P);    // 创建种群
    for(int i = 0; i < P; i ++){
        animals[i] = (Animal *) malloc(sizeof(Animal));
        memset(animals[i], 0, sizeof(Animal));     // 初始化
    }
    //printf("set value start\n");
    for(int i = 0; i < P; i ++){
        animals[i] -> id = i;
        animals[i]->dna = (DNA *)malloc(sizeof(DNA));
        for(int j = 0; j < DNA_NUM; j ++){
            animals[i]->dna -> dna_bit[j] = (int *)malloc(sizeof(int) * DNA_BIT);
        }
        //printf("generate start\n");
        generate_DNA(animals[i]);             // 创建DNA
        //printf("generate end\n");
        for(int j = 0; j  < DNA_NUM; j ++){
            animals[i]->dna_res[j] = (int *) malloc(sizeof(int) * DNA_BIT );   // 创建DNA解码结果
        }
        //printf("animal: %d end\n", i);
    }
    //("init end\n");
}

int fitness(Maze* maze, int index){
    int score = 256;   // 每移动一次少一分

    // 往回走扣大分
    int prev_x, prev_y, n_x, n_y;

    int** move = DNA_decode(animals[index]);
    int res = 0;
    int move_num[DNA_NUM] = {0};
    int access, ret;
    for(int i = 0; i < DNA_BIT / 2; i ++ ){
        n_x = maze->player[0];
        n_y = maze->player[1];
        access = access_table[maze->player[0]][maze->player[1]];
        int mode = move[access][move_num[access] ++ ];
        ret = maze->player_move(maze, mode);
        if(prev_x == maze->player[0] && prev_y == maze->player[1]){
            // 往回走, 扣大分
            score -= 13;
        }
        prev_x = n_x;
        prev_y = n_y;
        if(ret == 1){
            score += 5000;
            break;
        } else if (ret == 0){
            //score ++;
        } else {
            score -= 2;
        }
    }

    if(score < 0){
        score = 0;
    }

    // 依据曼哈顿距离算分
    int m_score = (maze -> destination[0] - maze -> player[0]) + (maze -> destination[1] - maze -> player[1]);
    res = score * 1 + ((length + width) * 2 + 2 - m_score) * 6;  // 曼哈顿距离越小, 分数越高
    maze -> reset(maze);

    return res;
}



DNA* generate_DNA(Animal* animal){
    /*
     * 通过观察环境来设计DNA
     * 一共16种状态, 每种状态对应一条DNA
     */
    DNA * res = animal->dna;
    int count;
    int rand_int;
    int index;
    for (int i = 0; i < DNA_NUM; ++i) {
        count = move_mode4dna[i][4];
        for(int j = 0; j < DNA_BIT; j += 2){
            //printf("i: %d, j: %d\n", i, j);
            rand_int = rand() % count;
            //index = 0;
            //to_index = rand_int;
            for(index = 0; index < 4; index ++){
                if(move_mode4dna[i][index] == 1 && rand_int == 0){
                    break;
                } else if (move_mode4dna[i][index] == 1 && rand_int != 0) {
                    rand_int--;
                }
            }
            res -> dna_bit[i][j] = index / 2;    // 生成的DNA只会是不撞墙的
            res -> dna_bit[i][j + 1] = index & 0x1;
        }
        /*printf("DNA %d: \n", i);
        for(int j = 0; j < DNA_BIT; j ++){
            printf("%d", animal -> dna -> dna_bit[i][j]);
        }
        printf("\n");*/
    }
    return res;
}

int** DNA_decode(Animal *animal){
    // 返回一个记录操作的数组
    DNA dna = *animal->dna;
    int mode;
    for(int i = 0; i < DNA_NUM; i++){
        for(int j = 0; j < DNA_BIT; j += 2){
            mode = animal->dna->dna_bit[i][j] * 2 + animal->dna->dna_bit[i][j + 1];
            animal->dna_res[i][j / 2] = mode;
        }
    }
    return animal->dna_res;
}

void print_animal(int index){
    char operators[] = "UDLR";
    printf("分数 %d \n", animals[index] -> score);
    /*printf("步骤如下: \n");
    for(int i = 1; i < DNA_BIT / 6 * 2; i += 2){
        putchar(operators[animals[index] -> dna_res[i]]);
    }*/
}

int select_max_index(){
    int max = animals[0]->score;
    int max_index = 0;
    for(int i = 0; i < P; i ++){
        if(max < animals[i]->score){
            max_index = i;
            max = animals[i]->score;
        }
    }
    return max_index;
}

void select(){
    // 排序
    sort();
    // 前 0.5% 直接继承
    int elite_num = P / 200;
    int all_scores = 0;
    // RAND_MAX = 32767
    int elimination_num = 0;
    int end = 0;
    for(int i = elite_num; i < P / 2; i ++){
        all_scores += animals[i]->score; // 轮盘赌总份数
        if(animals[i]->score < 50){
            end = i;
            break;
        }
    }
    // 淘汰的再随机生成
    for(int i = (P / 2 > end ? P / 2 : end ); i < P; i ++){
        /*for(int j = 0; j < DNA_NUM; j ++){
            free(animals[i]->dna->dna_bit[j]);
        }
        free(animals[i]->dna);*/
        animals[i]->dna = generate_DNA(animals[i]);
        animals[i]->score = 1;
    }

    // printf("123456");

    // 轮盘赌选择
    int couple_num = (int)(R * (P - elimination_num - elite_num) / 2); // 交叉遗传对数
    int father_index, mother_index;
    int is_selected[P] = {0};   // 记录是否已经被选择
    int count = 0;
    while (couple_num <=  count){
        // 随机产生N对亲代
        father_index = -1;
        mother_index = -1;
        // memset(is_selected, 0, sizeof(is_selected));
        int random_num1 = ((rand() << 15)  + rand()) % all_scores;   // 产生一个2 ^ 30 内的随机数, 限制在all_scores范围内
        int random_num2 = ((rand() << 15)  + rand()) % all_scores;
        for(int i = elite_num; i < P; i ++){
            if((random_num1 -= animals[i]->score) < 0 && father_index == -1){
                father_index = i;
                is_selected[father_index] = 1;
            }
            if((random_num2 -= animals[i]->score) < 0 && mother_index == -1){
                mother_index = i;
                is_selected[mother_index] = 1;
            }
        }
        if(is_selected[father_index] == 1 || is_selected[mother_index] == 1){
            continue;
        }
        crossover(animals[father_index], animals[mother_index]);
        count ++;
    }

    // 未被直接遗传的和未被交叉遗传的, 直接淘汰, 变成全新的
    /*for(int i = elite_num; i < P; i ++){
        if(is_selected[i] == 0){
            free(animals[i]->dna->dna_bit);
            free(animals[i]->dna);
            animals[i]->dna = generate_DNA();
        }
    }*/
    // 变异, 大大增加变异概率, 精英不作改变
    for(int i = elite_num + 1; i < P; i ++){
        mutation(animals[i]);
    }

}

void sort(){
    /*
     * 考虑到第一次排序后, 大部分原本优秀的仍是优秀, 故可以说是基本有序
     * 所以采用插入排序
     */
    for(int i = 1; i < P; i ++){
        int j = i - 1;
        Animal *animal_temp = animals[i];
        while(j >= 0 && animals[j] ->score < animal_temp->score){
            animals[j + 1] = animals[j];
            j --;
        }
        animals[j + 1] = animal_temp;
    }
}

void crossover(Animal *father, Animal *mother){
    // 随机交叉遗传
    for(int index = 0; index < DNA_NUM; index ++){
        int dot = rand() % (DNA_BIT - 1) + 1;   // 不会存在不交换的情况
        int temp;
        for(int i = dot ^ 0x1; i < DNA_BIT; i ++){
            // 从交换位置开始逐个交换, 暂不采用掩码位运算
            temp = father->dna -> dna_bit[index][i];
            father->dna -> dna_bit[index][i] = mother->dna -> dna_bit[index][i];
            mother->dna -> dna_bit[index][i] = temp;
        }
    }

}

void mutation(Animal *animal){
    double r;
    int index;
    for(int i = 0; i < DNA_NUM; i ++){
        int count =move_mode4dna[i][4];
        for(int j = 0; j < DNA_BIT; j += 2){
            r = rand() / 32767;
            if(r < M){
                // 在可解范围内变异
                int rand_int = rand() % count;
                for(index = 0; index < 4; index ++){
                    if(move_mode4dna[i][index] == 1 && rand_int == 0){
                        break;
                    } else if (move_mode4dna[i][index] == 1 && rand_int != 0) {
                        rand_int--;
                    }
                }
                animal -> dna -> dna_bit[i][j] = index / 2;    // 生成的DNA只会是不撞墙的
                animal -> dna -> dna_bit[i][j + 1] = index & 0x1;
            }
        }
    }
}

int getKeyboardEvent(Maze *maze){
    /*
     * 获取键盘事件, 得到玩家的运动方向
     * */
    int input = getch();
    // int none = getch();
    switch (input) {
        case 224:
            break;
        case UP1:
            return maze->player_move(maze, 0);
        case DOWN1:
            return maze->player_move(maze, 1);
        case LEFT1:
            return maze->player_move(maze, 2);
        case RIGHT1:
            return maze->player_move(maze, 3);
        default:
            return -1;
    }
    return -1;
}