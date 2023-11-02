#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

//定义货物类型
typedef struct {
    char* ID;
    int number;
}Ware;

void show_wares();
void enter_warehouse(Ware* ware);
void out_warehouse(char* ID);

int main(){
    system("chcp 65001");
    //输出语句以提示用户输入
    printf("%s", "请输入一个数字以选择操作\n1：查看库存列表\n2：入库\n3：出库\n4：退出程序\n");
    Ware* ware = (Ware*)malloc(sizeof(Ware));
    ware->ID=(char*) malloc(sizeof(char)*8);;

    //定义变量获取用户输入
    int choice;
    scanf("%d", &choice);

    //根据用户输入决定执行内容
    switch (choice) {
    case 1:
        show_wares();
        break;
    case 2:
        printf("%s", "请输入你想入库的货物的编号和数量，两个数据中间用空格键分隔\n");
        scanf("%s %d", ware->ID, &ware->number);
            enter_warehouse(ware);
            break;
    case 3:
        printf("%s", "请输入你想出库的货物的编号\n");
        scanf("%s", ware->ID);
        out_warehouse(ware->ID);
        break;
    case 4:
        exit(0);
    default:
        printf("%s", "选择失败，请重试！\n");
    }

}


void show_wares(){
    FILE *file=fopen("C:\\Users\\30744\\Desktop\\C-Homework pre\\Warehouse.txt", "r");  //打开文件
    if (file == NULL){  //如果文件打开失败，打印错误信息
        printf("%s", "FileOpenError!\n");
        exit(-1);
    } else{
        char* line=(char* ) malloc(20 * sizeof(char));
        int count=0;  //定义变量确定是否输出数据
        while (1) {
            if (fgets(line, 20, file)) {  //输出库存数据
                printf("%s", line);
                ++ count;
            }
            else if (count == 0){  //如果没有输出任何数据，打印“输出失败”信息
                printf("%s", "FgetsError!");
                break;
            } else{  //输出完毕后退出while循环
                break;
            }
        }
    }
    fclose(file);//关闭文件
}

void enter_warehouse(Ware* ware){
    FILE *file=fopen("./Warehouse.txt", "a");
    if (file == NULL){  //如果文件打开失败，打印错误信息
        printf("%s", "FileOpenError!\n");
        exit(-1);
    } else{  //根据用户输入写入数据
        fprintf(file, "%s\t\t\t%d", ware->ID, ware->number);
    }
    fclose(file);//关闭文件
}

void out_warehouse(char* ID){
    FILE *file=fopen("./Warehouse.txt", "a"), *tmp_file=fopen("temp_file", "w");//定义一个新文件，准备覆盖原本文件
    int found=0;  //定义一个变量found，确定是否有对应编号的数据
    if (file == NULL){
        printf("%s", "FileOpenError!\n");
        exit(-1);
    } else{  //如果文件打开失败，打印错误信息
        char* line=(char* ) malloc(20 * sizeof(char));
        if (fgets(line, 20, file)){
            if (!strstr(line, ID)){  //把非输入编号的数据写入到文件tmp中
                fputs(line, tmp_file);
            } else{
                found=1;  //如果有对应编号的货物，使found=1
            }
        }
        fclose(file);
        fclose(tmp_file);

        if (found) {
            remove("Warehouse");//如果找到了对应编号的货物，将原本的文件名移除，并且将文件temp命名为warehouse以覆盖原本的文件名
            rename("temp_file", "Warehouse");
        } else{
            printf("%s", "No such ware is found!\n");
        }
    }
}