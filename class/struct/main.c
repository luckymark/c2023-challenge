
#include <stdio.h>
#include <string.h>

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
    char  * a = &ZhangSan.dir;//
    char b[20] = "网络安全";
 //   ZhangSan.dir = "bbbb";//这里为啥修改。失败？
    ZhangSan.age =  20;//这里也失败？
    strcpy(ZhangSan.name, "小红");
    printf("%s ",computer.a.a.name);
    printf("%s ",a);
}