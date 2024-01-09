#include <stdio.h>
#include<string.h>
char c[1000001]={0};
void encrypt(){
    for(int i=0;i<strlen(c);i++)
        c[i]=c[i]-5;
    printf("%s\n",c);
}
void decrypt(){
    for(int i=0;i<strlen(c);i++)
    {
        c[i]=c[i]+5;
    }
    printf("%s\n",c);
}
int main() {
    int length;
    gets(c);
    encrypt();
    decrypt();
    return 0;
}