#include "search_function.h"
#include "judge_function.h"
#include<stdlib.h>
extern FILE * fp_2;
extern int computer_next_i;//用静态变量来存储第一层电脑的要下棋的位置
extern int computer_next_j;
extern FILE * fp;
extern int step;
int loc[16][2]={{-1,-1},{-2,-2},{1,1},{2,2},
                {1,-1},{2,-2},{-1,1},{-2,2},
                {1,0},{2,0},{-1,0},{-2,0},
                {0,1},{0,2},{0,-1},{0,-2}};//分别是x，y坐标的变化
int direct_check[9][2]={{0,0},{0,1},{0,-1},//横向
                        {1,0},{-1,0},//纵向
                        {1,1},{-1,-1},//左上到右下
                        {1,-1},{-1,1}//右上到左下
                        };
void quick_sort(blank * test_blank,int start,int end){
    if(start>=end)
        return;
    blank standard=test_blank[start];
    int sta_location=start;
    int i=start+1;
    int j=end;
    while(i<=j){
        while(j>=i&&j>=start){
            if(standard.delta_score>test_blank[j].delta_score){
                test_blank[sta_location]=test_blank[j];
                test_blank[j]=standard;
                sta_location=j;
                j--;
                break;
            }
            j--;
        }
        while(j>=i&&i<=end){
            if(standard.delta_score<test_blank[i].delta_score){
                test_blank[sta_location]=test_blank[i];
                test_blank[i]=standard;
                sta_location=i;
                i++;
                break;
            }
            i++;
        }
    }
    quick_sort(test_blank,start,sta_location-1);
    quick_sort(test_blank,sta_location+1,end);
}
int get_score(int p){
    if(p==1)
        return scores[1];
    else{
        if(p==2)
            return scores[2];
        else{
                if (p >= 3 && p <= 5)
                    return scores[3];
                else {
                    if (p >= 6 && p <= 7)
                        return scores[4];
                    else {
                        if (p >= 8 && p <= 13)
                            return scores[5];
                        else {
                            if (p >= 14 && p <= 18)
                                return scores[6];
                            else {
                                if (p >= 19 && p <= 22)
                                    return scores[7];
                                else {
                                    if (p == 23)
                                        return scores[8];
                                    else
                                        return scores[9];
                                }
                            }
                        }
                    }
                }
        }
    }
}
int judge_search(Board * board_main,int y,int x){
    int test=0;
    if(board_main->lattice_extinct[y][x]!=0)
        return test;
    for(int i=0;i<=15;i+=2){
        int c_x=x+loc[i][0];
        int c_y=y+loc[i][1];
            if(c_x<1||c_y<1||c_x>15||c_y>15)
                continue;
            else{
                if(board_main->lattice_extinct[c_y][c_x]!=0){
                    test=1;
                    break;
                }
            }
    }
    return test;
}
void evaluate(Board * board_main,int i,int j){//估值函数的主体思路：for循环每行从左到右寻找第一个子，以这个子的前一个子为开端，往后记录六个值，如果不满六个值，则有几个就记录几个，存在一个test数组里。
    //用这个数组和每一个已知序列匹配，找到一个则跳出，同时向后搜索找到第一个间断点之前的棋，从后向前存储六个数据再次匹配，取两次匹配值的最大值作为最终结果。
    every_value(board_main,i,j,2,1);
    every_value(board_main,i,j,4,1);
    every_value(board_main,i,j,6,1);
    every_value(board_main,i,j,8,1);
}
void clear_value(Board * board_main,int i,int j){
    int i_3,j_3,i_4,j_4;
    if(i>j){
        i_3=i-j+1;
        j_3=1;
    }
    else{
        i_3=1;
        j_3=j-i+1;
    }
    if(i+j<16){
        i_4=1;
        j_4=i+j-1;
    }
    else{
        i_4=i+j-15;
        j_4=15;
    }
    board_main->station_all_scores-=board_main->station_scores[1][i][1];
    board_main->station_all_scores-=board_main->station_scores[2][1][j];
    board_main->station_all_scores-=board_main->station_scores[3][i_3][j_3];
    board_main->station_all_scores-=board_main->station_scores[4][i_4][j_4];
    board_main->station_scores[1][i][1]=0;
    board_main->station_scores[2][1][j]=0;
    board_main->station_scores[3][i_3][j_3]=0;
    board_main->station_scores[4][i_4][j_4]=0;
}
int every_value(Board * board_main,int do_i,int do_j,int num,int control){//当遍历到下一行的时候，前一层的垃圾就会留下！！！！
    //注意设置的三维计分数组，1表示横向，2表示纵向，3表示左上到右下，4表示右上到左下
    //可以添加一个control变量，由于控制
    int control_score=0;
    int layer_num=num/2;
    //int score=0;
    int circle_number=0;
    int i,j,first_place_i,first_place_j;//两个first——place用于记录上次的起点，以判断下次的起点,但是改变策略之后first_place的两个量就没有用了,circle_number也没啥用了
    int i_add,j_add;
    if(num==6&&(do_j-do_i>=11||do_j-do_i<=-11)||num==8&&(do_i+do_j<=5||do_i+do_j>=27))
        return 0;
    switch(num){
        case 6://从左上到右下，沿斜线向左上移到第一个位置
            if(do_i>do_j){
                i=do_i-do_j+1;
                j=1;
            }
            else{
                i=1;
                j=do_j-do_i+1;
            }
            break;
        case 8://从右上到左下，沿斜线移到右上第一个位置
            if(do_i+do_j<16){
                i=1;
                j=do_i+do_j-1;
            }
            else{
                i=do_i+do_j-15;
                j=15;
            }
            break;
        case 2://每下一个子，对该行进行操作，将位置移到该行的第一个位置
            i=do_i;
            j=1;
            break;
        case 4://每下一个子，对该列进行操作，将位置移到该列的第一个位置
            i=1;
            j=do_j;
    }
    i_add=direct_check[num-1][0];
    j_add=direct_check[num-1][1];
    int clear_i=i;
    int clear_j=j;
        do
        {
            if(board_main->lattice_extinct[i][j]==0||(board_main->lattice_extinct[i][j]==-1 && control==-1)){
                i+=i_add;
                j+=j_add;
                continue;
            }
            else{
                int test_number=0;
                int state=board_main->lattice_extinct[i][j];
                int start_i=i-direct_check[num-1][0];
                int start_j=j-direct_check[num-1][1];//恰好可以控制在固定方向上的运动
                int end_j=-1;
                int end_i=-1;//-1为不可能出现的数，所以可以用-1来代表未被检测**
                int test_1[7]={0};//test数组应当从检测到的前一位开始计算**
                int check_block=0;//如果出现两个及以上的堵塞则必然为死棋，如果遇到死棋则直接停止存储！！！
                int point;
                int test_between=0;//检测是夹在中间的死棋还是在一个己方棋子后面的死棋。
                int test_k=-1;//记录遇到第一个死棋时的k。
                for(int k=1;k<=6;k++){//如何处理超额问题？超额则拿出来单独讨论，向后加一位,超额问题解决**
                    int p=num-1;//最多循环6次，直接跳出可能不足6次
                    int c_i=start_i+(k-1)*direct_check[p][0];//根据行走方向巧妙地控制i和j的变化
                    int c_j=start_j+(k-1)*direct_check[p][1];
                    if((num==2&&c_j>15)||(num==4&&c_i>15)||(num==6&&(c_j>15||c_i>15))||(num==8&&(c_j<1||c_i>15))){
                        test_number=k;//若超额则多比较一位，也就是最后的墙壁是被记入的，避免类似活一这种东西的错误使用，在循环后面有一个部分是在后面加了一个封死。。
                        break;
                    }
                    test_1[k]=(board_main->lattice_extinct[c_i][c_j])*state;//将所有己方都转化成1，将所有对方对转化成-1；
                    if(k>1&&test_1[k]!=1&&end_j==-1&&end_i==-1){
                        end_j=c_j;
                        end_i=c_i;//这两个变量必须存在，有可能存在空位的情况，要靠这两个变量反向循环
                    }//用end_j和end_i是否等于-1判断是否是第一次遇到，修改了死棋机制之后，end_j和end_i还是需要保留的
                    if(test_1[k]==-1){//因为遇到一次即可宣判死棋但是这一次不能是搜索的第一个，所以可以
                        //外加判断，第一个死棋则不需要跳出，但累计。非第一个死棋，则累计并跳出，循环外判断如果test_number!=0,则有意外跳出，
                        //判断check_block的数值，如果为==0，则说明一定是碰墙死棋，碰墙死棋还是有概率可以匹配的，可进行统一匹配。
                        //如果==1，1.第一个存储的是-1并且碰墙死棋，这个时候直接continue，因为不可能有分；
                        //2.第一个存储的不是-1而遇到了一个-1，这个时候统一匹配，问题是：如何区分以上两种情况？？
                        //最简单的方法是设置一个变量，test_wall......暂时解决,NO NO NO,test_wall不用设置，用test_between就行
                        //如果check_block==2，则一定是夹住了，直接continue。
                        if(k==1){
                            check_block++;
                            test_between=1;
                        }
                        else{
                            check_block++;
                            test_number=k;
                            break;
                        }
                    }
                }
                if(test_number==0)//录入6个
                    test_number=6;
                else{
                    if(check_block==2){
                        i=end_i;
                        j=end_j;
                        continue;
                    }
                    else{
                        if(check_block==1){
                            if(test_between==1){
                                i=end_i;
                                j=end_j;
                                continue;
                            }
                        }
                        else{
                            test_1[test_number]=3;//碰墙死棋需要改变最后的一个值
                        }
                    }
                }
                for(int k=1;k<=MODE_NUMBER;k++){//匹配的时候有一个优化，就是，如果test数组的个数小于匹配串的个数则直接continue，因为不可能匹配出来。
                    if(test_number<judge[k][0])
                        continue;
                    point=0;
                    for(int p=1;p<=judge[k][0]&&p<=test_number;p++){
                        if(judge[k][p]==2)
                            continue;
                        if(judge[k][p]==-1&&(test_1[p]==3||test_1[p]==-3))
                            continue;
                        else{
                            if(judge[k][p]!=test_1[p]){
                                point=-1;
                                break;
                            }
                        }
                    }
                    if(point==0&&test_number>=judge[k][0]){
                        point=k;//找到合适的匹配模型
                        break;
                    }
                    else{
                        point=-1;
                    }
                }
                int get_score_1;
                if(point==-1)//如果没有找到匹配的模型，则认为是无效模型。
                    get_score_1=0;
                else
                    get_score_1=get_score(point);//算分
                //以上是正向算分，接下来是反向算分：
                test_between=0;
                test_number=0;
                check_block=0;
                test_k=-1;
                int test_2[7]={0};
                for(int k=1;k<=6;k++){
                    int p=num;
                    int c_i=end_i+(k-1)*direct_check[p][0];
                    int c_j=end_j+(k-1)*direct_check[p][1];
                    if((num==2&&c_j<1)||(num==4&&c_i<1)||(num==6&&(c_i<1||c_j<1))||(num==8&&(c_j>15||c_i<1))){
                        test_number=k;//多比对一位
                        break;
                    }
                    test_2[k]=(board_main->lattice_extinct[c_i][c_j])*state;
                    if(test_2[k]==-1){
                        if(k==1){
                            check_block++;
                            test_between=1;
                        }
                        else{
                            check_block++;
                            test_number=k;
                            break;
                        }
                    }
                }
                if(test_number==0)//录入6个
                    test_number=6;
                else{
                    if(check_block==2){
                        i=end_i;
                        j=end_j;
                        continue;
                    }
                    else{
                        if(check_block==1){
                            if(test_between==1){
                                i=end_i;
                                j=end_j;
                                continue;
                            }
                        }
                        else{
                            test_2[test_number]=3;//碰墙死棋需要改变最后的一个值
                        }
                    }
                }
                for(int k=1;k<=MODE_NUMBER;k++){
                    if(test_number<judge[k][0])
                        continue;
                    point=0;
                    for(int p=1;p<=judge[k][0]&&p<=test_number;p++){
                        if(judge[k][p]==2)
                            continue;
                        if(judge[k][p]==-1&&(test_2[p]==3||test_2[p]==-3))
                            continue;
                        else{
                            if(judge[k][p]!=test_2[p]){
                                point=-1;
                                break;
                            }
                        }
                    }
                    if(point==0&&test_number>=judge[k][0]){
                        point=k;//找到合适的匹配模型
                        break;
                    }
                    else{
                        point=-1;
                    }
                }
                int get_score_2;
                if(point==-1)//如果没有找到匹配的模型，则认为是无效模型。
                    get_score_2=0;
                else
                    get_score_2=get_score(point);//算分
                if(control==-1){
                    control_score+=get_score_1>get_score_2?get_score_1:get_score_2;
                }
                else {
                    if (get_score_1 > get_score_2) {
                        board_main->station_scores[layer_num][clear_i][clear_j] += get_score_1 * (-1) * state;
                        board_main->station_all_scores += get_score_1 * (-1) * state;
                    }
                    else {
                        board_main->station_scores[layer_num][clear_i][clear_j] +=get_score_2 * (-1) * state;//这个存储每一列或行的得分的位置可以固定一下
                        board_main->station_all_scores += get_score_2 * (-1) * state;
                    }
                }
                i=end_i;
                j=end_j;
            }
        }while(board_main->lattice_extinct[i][j]!=3);
        if(control==-1)
            return control_score;
}
void Heuristically_evaluate(Board board_main,int i,int j,int state,blank * test_blank,int capacity){
    int pre_all_score=board_main.station_all_scores;
    int p_i;
    int p_j;
    test_blank[capacity].blank_i=i;
    test_blank[capacity].blank_j=j;//用来标记某个点已经被访问过
    board_main.lattice_extinct[i][j]=state;
    every_value(&board_main,i,j,2,1);//形式还可以优化
    test_blank[capacity].layer[1]=board_main.station_scores[1][i][1];
    test_blank[capacity].start_location_i[1]=i;
    test_blank[capacity].start_location_j[1]=1;
    every_value(&board_main,i,j,4,1);
    test_blank[capacity].layer[2]=board_main.station_scores[2][1][j];
    test_blank[capacity].start_location_i[2]=1;
    test_blank[capacity].start_location_j[2]=j;
    every_value(&board_main,i,j,6,1);
    p_i=i>j?(i-j+1):1;
    p_j=i>j?1:(j-i+1);
    test_blank[capacity].layer[3]=board_main.station_scores[3][p_i][p_j];
    test_blank[capacity].start_location_i[3]=p_i;
    test_blank[capacity].start_location_j[3]=p_j;
    every_value(&board_main,i,j,8,1);
    p_i=i+j<16?1:i+j-15;
    p_j=i+j<16?i+j-1:15;
    test_blank[capacity].layer[4]=board_main.station_scores[4][p_i][p_j];
    test_blank[capacity].start_location_i[4]=p_i;
    test_blank[capacity].start_location_j[4]=p_j;
    test_blank[capacity].delta_score=board_main.station_all_scores-pre_all_score;
}
void change(Board * board,blank test,int state){
    board->station_all_scores+=test.delta_score;
    board->lattice_extinct[test.blank_i][test.blank_j]=state;
    for(int i=1;i<=4;i++){
        board->station_scores[i][test.start_location_i[i]][test.start_location_j[i]]=test.layer[i];
    }
}
//修改最后摆烂的问题。
//1、要把挨着一个棋子的连五删去，仅留一个连五就可**
//2、要把录入个数改成6**
//3、发现特点：如果是电脑下棋，电脑会遍历所有可能的落子点，这就意味着电脑的落子可能不是最优解，所以对于电脑一方，一般不会存在必胜局面，
//比如说电脑有一个双活三，电脑落子的时候如果成一个活四，那么电脑必胜，如果电脑没有成一个双活四，则电脑不会必胜；
//然而在电脑预测玩家的时候并不会这样，如果检测出玩家有一个双活三，那么minimax的计算结果是玩家必胜，这样电脑就会检测出一个电脑必输的局面，那么电脑会选择一个最利于自己的必输局面，可能会走一些不符合逻辑的局面
//而如果是电脑必胜，那么电脑必然会选择一个最有利于自己的必胜局面，这非常符合逻辑
//4、问题点：仅仅需要修改电脑落子且电脑必输的情况。这个时候通过minimax的返回值必然小于某个数，就说明必输，这个时候就需要使用另外一种算分方法——仅仅计算对方的分数，让对方的得分绝对值最小即可，达到抑制对方的效果。
//5、解决方式：修改every_value函数，设置一个control，并且将every_value函数改为有返回值，如果control==-1，则返回将分数累计并返回，在act数组中循环遍历所有可能的节点，并将落点坐标改为对方分数绝对值最小的地方。
int minimax_search(Board board_main,int layer,int c_alpha,int c_beta) {//极大极小值搜索,改为传入结构的值而不是结构本身
    if (layer == 0) {
        if (board_main.station_all_scores < c_beta)
            return board_main.station_all_scores;
        else
            return c_beta;
    }
    if((board_main.station_all_scores<-30000000||board_main.station_all_scores>30000000)){
        if(board_main.station_all_scores>30000000&&layer==LAYER-1)
            return INT_MAX;
        return board_main.station_all_scores;
    }
    else {
        //首先建立一个函数，进行初步估值，这个估值必须通过函数传值完成，因为传参可以不必clear
        int capacity = 0;
        blank test_blank[230];
        for (int i = 1; i <= 15; i++) {
            for (int j = 1; j <= 15; j++) {
                if (judge_search(&board_main, i, j)) {
                    capacity++;
                    if (layer % 2 == 0) {
                        Heuristically_evaluate(board_main, i, j, -1, test_blank,capacity);//i和j的存在是为了确定位置，在博弈树中的所有数据都是传值操作，因为当回溯的时候数据全部清空，这样的话就不需要clear了
                        //传入board_main,这样就不需要清理函数了，需要调用的变量以及参数：
                        //1、board_main中的总分，计算delta_score，传到函数之后，立马记录下board_main的总分，然后对改变lattice_extinct[][]的值。
                        //2、every_value（传址）计算出每个方向的分数，并且存在test_blank结构数组（定义在本函数中，这意味这传入board_main的同时需要传入test_blank）中，需要一个数组存储每个方向的值，还需要变量存储每个方向起始的i和j值。
                        //3、every_value四遍之后，可以求delta_score，记录在test_blank。
                    }
                    else {
                        Heuristically_evaluate(board_main, i, j, 1, test_blank, capacity);
                    }
                }
                else
                    continue;
            }
        }
        quick_sort(test_blank, 1, capacity);
        if (layer % 2 == 0) {
            for (int i = capacity; i >= 1; i--) {
                Board copy_board = board_main;
                change(&copy_board, test_blank[i], -1);//改变copy_board,尤其注意lattice_extinction
                int guess_max = minimax_search(copy_board, layer - 1, c_alpha, c_beta);
                if (guess_max > c_alpha) {
                    c_alpha = guess_max;
                    if (layer == LAYER) {
                        computer_next_i = test_blank[i].blank_i;
                        computer_next_j = test_blank[i].blank_j;//存储第一层max要下的位置。
                    }
                }
                if(layer==LAYER){
                }
                if (c_beta < c_alpha)
                    return c_alpha;
            }
            return c_alpha;
        } else {
            for (int i = 1; i<=capacity; i++) {
                Board copy_board = board_main;
                change(&copy_board, test_blank[i], 1);
                int guess_min = minimax_search(copy_board, layer - 1, c_alpha, c_beta);
                if (guess_min < c_beta)
                    c_beta = guess_min;
                if (c_beta < c_alpha) {
                    return c_beta;
                }
            }
            return c_beta;
        }
    }
}
int judge_win(Board * board_main){
    for(int i=1;i<=4;i++){
        for(int j=1;j<=15;j++){
            if(board_main->station_scores[i][1][j]>40000000||board_main->station_scores[i][1][j]<-40000000||board_main->station_scores[i][j][1]>40000000||board_main->station_scores[i][j][1]<-40000000
            ||board_main->station_scores[i][j][15]>40000000||board_main->station_scores[i][j][15]<-40000000){
                return 1;
            }
        }
    }
    return -1;
}