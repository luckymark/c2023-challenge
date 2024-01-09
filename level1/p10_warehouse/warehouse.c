//
// Created by 14212 on 2023/10/14.
//
#include "warehouse.h"
void show_list(FILE * fp){
    fp=fopen("D:/c2023-challenge/level1/c2023-challenge/level1/p10_warehouse/Data.txt","rb");
    char line[101];
    fgets(line,100,fp);
    while(!feof(fp)){
        printf("%s",line);
        fgets(line,100,fp);
    }
    printf("\nPress the \"Enter\" to continue.\n");
}
void init_print(void){
    printf("Please press the key to choose your step:\n");
    printf("1: Show the goods list.\n");
    printf("2: Warehouse the goods.\n");
    printf("3: bring out the goods.\n");
    printf("4: bring the program to an end.\n\n");
    printf("What do you what to do :\n");
}
int warehouse(FILE * fp){
    char goods_mode[101];
    int num;
    double price;
    printf("Please input the mode of the good:\n");
    scanf("%s",goods_mode);
    int test=research(fp,goods_mode,1);
    if(test==0){
        fp=fopen("D:/c2023-challenge/level1/c2023-challenge/level1/p10_warehouse/Data.txt","ab+");
        print_time(fp);
        fprintf(fp,"%18s",goods_mode);
        printf("Please input the quantity of the goods:\n");
        while(!scanf("%d",&num)||num<=0){
            printf("Please input right number!\n");
            printf("Please input the quantity of the goods:\n");
            fflush(stdin);
        }
        fprintf(fp,"%25d",num);
        printf("Please input the price of the goods:\n");
        while(!scanf("%lf",&price)||price<=0){
            printf("Please input right number!\n");
            printf("Please input the quantity of the goods:\n");
            fflush(stdin);
        }
        fprintf(fp,"%22.2f\n",price);
        fclose(fp);
        printf("You have finished warehousing %d %s!\n",num,goods_mode);
        printf("Press the \"Enter\" to continue.\n");
        fflush(stdin);
        getchar();
    }
}
int research(FILE * fp,char * mode,int t){
    int q,ori_q,p,det=0;
    char n1[101]="D:/c2023-challenge/level1/c2023-challenge/level1/p10_warehouse/Data.txt";
    char n2[101]="D:/c2023-challenge/level1/c2023-challenge/level1/p10_warehouse/Data_Bucket.txt";
    char line[101],list_member[101];
    fp=fopen(n1,"rb+");
    while(!feof(fp)){
        fgets(line,99,fp);
        sscanf(line,"%*s %*s %s",list_member);
        if(strcmp(mode,list_member)==0) {
            p=1;
            printf("The goods has been there!\n");
            printf("Please input the quantity of the goods:\n");
            while(!scanf("%d",&q)||q<=0){
                printf("Please input right number!\n");
                printf("Please input the quantity of the goods:\n");
                fflush(stdin);
            }
            sscanf(line,"%*s %*s %*s %d",&ori_q);
            if(t==-1 && q>ori_q)
            {
                printf("The quantity is not enough!\n");
                printf("Do you bring out all the goods?\n");
                printf("1: Yes,I want to bring out all goods            2:No,I don't bring out the goods\n");
                while(!scanf("%d",&det)||det<1||det>2){
                    printf("Please input right number!\n");
                    printf("Please input your choice:\n");
                    fflush(stdin);
                }
                if(det==1){
                    printf("You have finished brought %d %s !\n",ori_q,mode);
                    printf("Press the \"Enter\" to continue.\n");
                    fflush(stdin);
                    getchar();
                    fseek(fp,0L,SEEK_SET);
                    FILE * fp_2=fopen(n2,"wb");
                    while(!feof(fp)) {
                        if(strlen(fp->_ptr)==0)
                            break;
                        fgets(line, 99, fp);
                        sscanf(line, "%*s %*s %s", list_member);
                        if(strcmp(mode,list_member)!=0)
                            fprintf(fp_2,"%s",line);
                    }
                    fclose(fp_2);
                    fclose(fp);
                    CopyFile(n2,n1,FALSE);
                    break;
                }
                else
                    break;
            }
            else{
                fseek(fp,-85L,SEEK_CUR);//注意\r\n
                print_time(fp);
                fseek(fp,18L,SEEK_CUR);
                int i=q;
                q=q*t+ori_q;
                fprintf(fp,"%25d",q);
                fseek(fp,24L,SEEK_CUR);
                if(t==1)
                    printf("You have finished warehousing %d %s!\n",i,mode);
                else
                    printf("You have finished brought out %d %s!\n",i,mode);
                printf("Press the \"Enter\" to continue.\n");
                fflush(stdin);
                getchar();
                break;
            }
        }
    }
    fclose(fp);
    return p;
}
void print_time(FILE * fp){
    time_t now=time(0);
    struct tm *t= localtime(&now);
    fprintf(fp,"%d/%0d/%0d %02d:%02d:%02d",t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
}
int bring_out(FILE * fp){
    char goods_mode[101];
    int num;
    printf("Please input the mode of the good:\n");
    scanf("%s",goods_mode);
    int test=research(fp,goods_mode,-1);
    if(test==0) {
        printf("There is no the goods!\n");
        printf("Press the \"Enter\" to continue.\n");
        fflush(stdin);
        getchar();
    }
}
