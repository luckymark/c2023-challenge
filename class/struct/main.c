
#include <stdio.h>

int main(){
    system("chcp 65001");
    typedef struct {
        char name[10];
        int age;
        char dir[20];
    }People;
    typedef struct {
        People a ;
        People b ;
    }Project;
    typedef struct {
        Project a ;
        Project b ;
    }college;

    People ZhangSan = {"张三", 30,"人工智能"};
    People LiSi ={"李四", 40,"数据库"};
    Project soft = {ZhangSan,LiSi};
    Project data = {};
    college computer ={soft,data};
    char  * a = &ZhangSan;//怎么同时输出三个量;怎么使用指针修改里面的量
    char b[20] = "网络安全";
    ZhangSan.dir = b;//这里为啥修改失败？
    ZhangSan.age =  20;//这里也失败？
    printf("%d ",computer.a.a.age);
    printf("%s ",a);
}