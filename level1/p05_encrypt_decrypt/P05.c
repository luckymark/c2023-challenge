/*#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char * encryption(char * wait_to_encry){
    for (int i = 0; i < strlen(wait_to_encry); i ++){
        wait_to_encry[i] = wait_to_encry[i] + 3;
    }
    return wait_to_encry;
}

char * decryption(char * wait_to_decry){
    for (int i = 0; i < strlen(wait_to_decry); i ++){
        wait_to_decry[i] = wait_to_decry[i] - 3;
    }
    return wait_to_decry;
}

int main(){
    char * wait_to_encry = (char*)malloc(100 * sizeof(char)), *wait_to_decry = (char*)malloc(100 * sizeof(char));
    int input_num;
    printf("%s", "If you want to encrypt information,please input '1'\nIf you want to decrypt information,please input '2'\n");
    scanf("%d", &input_num);
    if (input_num == 1){
        printf("%s", "Please input the information\n");
        scanf("%s", wait_to_encry);
        printf("The result is %s", encryption(wait_to_encry));
        free(wait_to_encry);
    }
    else if (input_num == 2){
        printf("%s", "Please input the information\n");
        scanf("%s", wait_to_decry);
        printf("The result is %s", decryption(wait_to_decry));
        free(wait_to_decry);
    }
}*/