#include <windows.h>
#include <stdio.h>

extern char str[(102) * (102)];
extern int large;
extern int map[101][101];

void Print(){
    int i = 0,j = 0;
    //将str初始化为空
    str[0] = '\0';
    system("cls");
    for(i = 0;i < large;i++){
        for (j = 0; j < large; j++) {
            if(map[i][j] == 0){
                strcat(str,"■");
            }
            if(map[i][j] == 1){
                strcat(str," ");
            }
            if(map[i][j] == 3){
                strcat(str,"⊙");
            }
            if(map[i][j] == 4){
                strcat(str,"☆");
            }
            //调试时测试用的值
            if(map[i][j] == 5){
                strcat(str,"◇");
            }
            if(map[i][j] == -1)
                break;
        }
        if(-1 != map[i][0]){
            strcat(str,"\n");
        }
    }
    printf("%s ",str);
}