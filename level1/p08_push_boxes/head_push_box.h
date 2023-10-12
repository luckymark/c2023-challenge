
void Map();//读取文件中地图
void Print();//打印更改后的地图
void Menu();//菜单
int Push();//推动箱子或者移动
int Up();
int Down();
int Left();
int Right();
int Finish();//判断是否结束
void Note();//记录得分
void Read();
int Min_step(int l);//暂未实现的设想
//想用结构体存目标位置失败了
typedef struct {
    int x;
    int y;
}Goal;