#include<stdio.h>
#include<string.h>
#include<time.h>
#define ACCURACY 1000000
#define SAFETY 10
void multiply(int * cx,int * cx_copy,int num,int times,int * cx_len,int * cx_len_copy){
    if(times!=1)
        num=num*num;
    for(int i=0;i<*cx_len;i++){
        cx[i]=cx[i]*num;
    }
    int j=1;
    while(j<=*cx_len){
        if(cx[j-1]>9){
            cx[j]+=cx[j-1]/10;
            cx[j-1]=cx[j-1]%10;
            if(j==*cx_len)
                (*cx_len)++;
        }
        j++;
    }
    memcpy(cx_copy,cx,(*cx_len)*sizeof(int));
    (*cx_len_copy)=(*cx_len);
    for(int i=0;i<*cx_len_copy;i++){
        cx_copy[i]=cx_copy[i]*times;
    }
    j=1;
    while(j<=*cx_len_copy){
        if(cx_copy[j-1]>9){
            cx_copy[j]+=cx_copy[j-1]/10;
            cx_copy[j-1]=cx_copy[j-1]%10;
            if(j==*cx_len_copy)
                (*cx_len_copy)++;
        }
        j++;
    }
}
int judge_division(int * dividend,int * cx_copy,int * cx_len_copy,int * start,int * end){
    if(*cx_len_copy<*end-*start+1)
        return 1;
    else{
        if(*cx_len_copy>*end-*start+1)
            return 0;
        else{
            for(int i=*start;i<=*end;i++){
                if(cx_copy[*cx_len_copy-(i-*start)-1]>dividend[i])
                    return 0;
                if(dividend[i]>cx_copy[*cx_len_copy-(i-*start)-1])
                    return 1;
            }
            return 1;
        }
    }
}
int substract(int * dividend,int * cx_copy,int * cx_len_copy,int * start,int * end){
    int times=0;
    while(judge_division(dividend,cx_copy,cx_len_copy,start,end)){
        times++;
        for(int i=*end;i>=*end-*cx_len_copy+1;i--){
            int p=dividend[i]-cx_copy[*end-i];
            if(p<0){
                p+=10;
                dividend[i-1]--;
            }
            dividend[i]=p;
        }
        while(dividend[*start]==0)
            (*start)++;
    }
    return times;
}
void divide(int * dividend,int * cx_copy,int * result,int * cx_len_copy){
    int start=0;
    int end=*cx_len_copy-1;
    while(end<ACCURACY+SAFETY){
        if(!judge_division(dividend,cx_copy,cx_len_copy,&start,&end)){
            end++;
        }
        else{
            result[end]=substract(dividend,cx_copy,cx_len_copy,&start,&end);
        }
    }
}
int main(){
    clock_t start,end;
    start=clock();
    int cx_239[ACCURACY*2]={1};
    int cx_5[ACCURACY*2]={1};
    int all_result[ACCURACY*2]={0};
    int cx_len_5=1;
    int cx_len_239=1;
    int times=1;
    while(cx_len_5<=ACCURACY+SAFETY){
        int result[ACCURACY*2]={0};
        int dividend[ACCURACY*2]={0};
        int cx_5_copy[ACCURACY*2]={0};
        int cx_len_copy=1;
        dividend[0]=1;
        dividend[1]=6;
        multiply(cx_5,cx_5_copy,5,times,&cx_len_5,&cx_len_copy);
        divide(dividend,cx_5_copy,result,&cx_len_copy);
        if(times%4==1){
            for(int i=0;i<ACCURACY+SAFETY;i++){
                all_result[i]+=result[i+1];
            }
            for(int i=ACCURACY+SAFETY-1;i>=0;i--){
                if(all_result[i]>9){
                    all_result[i-1]+=all_result[i]/10;
                    all_result[i]%=10;
                }
            }
        }
        else{
            for(int i=0;i<ACCURACY+SAFETY;i++){
                all_result[i]-=result[i+1];
            }
            for(int i=ACCURACY+SAFETY-1;i>0;i--){
                if(all_result[i]<0){
                    all_result[i-1]--;
                    all_result[i]+=10;
                }
            }
        }
        times+=2;
    }
    times=1;
    while(cx_len_239<=ACCURACY+SAFETY){
        int result[ACCURACY*2]={0};
        int dividend[ACCURACY*2]={0};
        int cx_239_copy[ACCURACY*2]={0};
        int cx_len_copy=1;
        dividend[0]=4;
        multiply(cx_239,cx_239_copy,239,times,&cx_len_239,&cx_len_copy);
        divide(dividend,cx_239_copy,result,&cx_len_copy);
        if(times%4==3){
            for(int i=0;i<ACCURACY+SAFETY;i++){
                all_result[i]+=result[i];
            }
            for(int i=ACCURACY+SAFETY-1;i>=0;i--){
                if(all_result[i]>9){
                    all_result[i-1]+=all_result[i]/10;
                    all_result[i]%=10;
                }
            }
        }
        else{
            for(int i=0;i<ACCURACY+SAFETY;i++){
                all_result[i]-=result[i];
            }
            for(int i=ACCURACY+SAFETY-1;i>0;i--){
                if(all_result[i]<0){
                    all_result[i-1]--;
                    all_result[i]+=10;
                }
            }
        }
        times+=2;
    }
    end=clock();
    printf("time=%lf\n",(double)(end-start)/CLOCKS_PER_SEC);
    printf("%d.",all_result[0]);
    for(int i=1;i<=ACCURACY;i++){
        printf("%d",all_result[i]);
    }
}