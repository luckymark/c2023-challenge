#include "warehouse.h"
int main() {
    FILE * fp;
    int step=0;
    char goods_mode[100];
    while(1){
       init_print();
        while((!scanf("%d",&step))||step>4||step<1){//这里要分析一下缓冲区
            printf("Please choose the right number!\n");
            printf("Press the \"Enter\" to continue.\n");
            fflush(stdin);
            getchar();
            system("cls");
            init_print();
        }
        switch(step){
            case 1:
                show_list(fp);//显示存货列表
                fflush(stdin);
                getchar();
                break;
            case 2:
                warehouse(fp);
                break;
            case 3:
                bring_out(fp);
                break;
            case 4:
                printf("The program is over!");
                system("pause");
                return 0;
            default:
                printf("unknown mistake!");
                break;
        }
        system("cls");
    }
}