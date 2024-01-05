#include<stdio.h>
int main(){
    char a[26];
    a[0]='a';
    int i,x;
    i=1;
    while(i<26){
        a[i]=a[i-1]+1;
    }
    for(i=0;i<26;i++)
    printf("%c",a[i]);
    return 0;
}
