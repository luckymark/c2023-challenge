#include <stdio.h>
#include <string.h>
#include <stdlib.h>
static const char b64[] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
        'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
        'R', 'S', 'T', 'U', 'V', 'W', 'X','Y',
        'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g',
        'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
        'p', 'q', 'r', 's', 't', 'u', 'v', 'w',
        'x','y', 'z', '0', '1', '2', '3', '4',
        '5', '6', '7', '8', '9', '+', '/'
};
// K L M N O P Q R A B C D E F G H I J k l m n o p q r s t u v w x y z 0 1 2 3 4 5 6 7 8 9 + / S T U V W X Y Z a b c d e f g h i j
static unsigned char de_b64[256] = {
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 253, 255,
        255, 253, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 253, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255,  62, 255, 255, 255,  63,
        52,  53,  54,  55,  56,  57,  58,  59,  60,  61, 255, 255,
        255, 254, 255, 255, 255,   0,   1,   2,   3,   4,   5,   6,
        7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,
        19,  20,  21,  22,  23,  24,  25, 255, 255, 255, 255, 255,
        255,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,
        37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,
        49,  50,  51, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
        255, 255, 255, 255 };

static char cmoveBits(unsigned char c, int left, int right){
    c <<= left;
    c >>= right;
    return c;
}

int base64_encrypt(const char *str, int len, char *res, int *outlen){
    /*
     * base64
     * 将每三个字符二进制处理
     * */
    char *p = res;
    int r = len % 3;
    int pad = (3 - r == 3 ? 0 : 3 - r);
    int p1 = len - r;   // 直接处理
    int nlen = p1 * 4 / 3 + (r > 0 ? r + 1 : r)+ pad;
    if(outlen != NULL){
        *outlen = nlen;
    }
    int tempArr[4] = {};
    int i = 0;
    /*
    printf("arr: %p", tempArr);
    printf("p  : %p\n", p);
    printf("res: %p\n", res);
    printf("p1 : %p\n", &p1);
     */
    for(int j = 0; i < p1; i += 3, j += 4){
        // 前面能直接处理的部分
        // printf("%d", i);
        tempArr[0] = str[i] >> 2;            // 舍弃后两位拿到前六位作为第一位
        tempArr[1] = ((str[i] & 0x3) << 4) + (str[i + 1] >> 4); // 第一位的后两位和第二位的前四位
        tempArr[2] = ((str[i + 1] & 0xf) << 2) + (str[i + 2] >> 6); // 第二位的后四位和第三位的前两位
        tempArr[3] = (str[i + 2]) & 0x3f;
        p[j] = b64[tempArr[0]];
        p[j + 1] = b64[tempArr[1]];
        p[j + 2] = b64[tempArr[2]];
        p[j + 3] = b64[tempArr[3]];
    }
    if(pad != 0){
        // 如果整体不能被3整除
        // 追加 =
        int end = p1 * 4 / 3;
        if(pad == 2){
            p[end] = b64[str[p1] >> 2];
            p[end + 1] = b64[(str[p1] & 0x3) << 4];
            p[end + 2] = '=';
            p[end + 3] = '=';
        }else{  // pad == 1
            p[end] = b64[str[p1] >> 2];
            p[end + 1] = b64[((str[p1] & 0x3) << 4) + (str[p1 + 1] >> 4)];
            p[end + 2] = b64[(str[p1 + 1] & 0xf) << 2];
            p[end + 3] = '=';
        }
    }
    return 0;
}

int decode(const char *str, int len, char *res, int *reLen){
    /*
     * 解码
     * */
    if(len % 4 != 0)
        return -1;
    char *p = res;
    int pad = 0;
    int nLen = len;
    if(str[len - 1] == '='){
        pad = 1;
        if(str[len - 2] == '=')
            pad = 2;
        nLen -= 4;
    }
    int re_len = nLen * 3 / 4;
    for(int i = 0, j = 0; i < nLen; i += 4, j += 3){
        p[j] = (de_b64[str[i]] << 2) + (de_b64[str[i + 1]] >> 4);
        p[j + 1] = (de_b64[str[i + 1]] << 4) + (de_b64[str[i + 2]] >> 2);
        p[j + 2] = (de_b64[str[i + 2]] << 6) + de_b64[str[i + 3]];
    }
    if(pad > 0){
        if(pad == 1){
            p[re_len] = (de_b64[str[nLen]] << 2) + (de_b64[str[nLen + 1]] >> 4);
            p[re_len + 1] = (de_b64[str[nLen + 1]] << 4) + (de_b64[str[nLen + 2]] >> 2);
            re_len += 2;
        }else{
            p[re_len] = (de_b64[str[nLen]] << 2) + (de_b64[str[nLen + 1]] >> 4);
            re_len += 1;
        }
    }
    *reLen = re_len;
    return 0;
}

int en_de(){
    printf("pls input command: \n1: encrypt\n2: decrypt\n3: exit\n");
    int cmd = 0;
    if (scanf("%d", &cmd) != 1) {
        printf("pls input an integer\n");
        while (getchar() != '\n'); // 清空输入缓冲区
        return 1;
    }
    while (getchar() != '\n'); // 清空输入缓冲区
    if(cmd == 1){
        char s[1024] = "";
        printf("pls input string: \n");
        gets(s);
        int len = 0;
        char *res = (char *)malloc(1024 * sizeof(char));
        base64_encrypt(s, (int) strlen(s), res, &len);
        printf("res: %s\n", res);
        //printf("\n");
        free(res);
        /*
        for(int i = 0; i < len; i ++){
            printf("%c", res[i]);
        }
         */
    }else if(cmd == 2){
        char s[1024 * 4 / 3  + 1] = "";
        printf("pls input string (in 1 line): \n");
        scanf("%1023s", s);
        char str2[1024] = {};
        int len2 = 0;
        decode(s, (int) strlen(s), str2, &len2);
        for(int i = 0; i < len2; i++){
            printf("%d, ", str2[i] + 128);
        }
        printf("\n");
        // printf("res: %s\n", str2);
    }else if(cmd == 3){
        return 0;
    }
    /*
    char s[1024] = "";
    printf("pls input string: \n");
    scanf("%1023s", s);
    int len = 0;
    char *res = (char *)malloc(1024 * sizeof(char));
    base64_encrypt(s, (int) strlen(s), res, &len);
    for(int i = 0; i < len; i ++){
        printf("%c", res[i]);
    }
    printf("\n");
    char str2[1024] = {};
    int len2 = 0;
    decode(res, len, str2, &len2);
    for(int i = 0; i < len2; i ++){
        printf("%c", str2[i]);
    }
    free(res);
    return 1;
     */
    return 1;
}

int main() {
    // setbuf(stdout, NULL);
    // char s[] = "Man is distinguished, not only by his reason, but by this singular passion from other animals, which is a lust of the mind, that by a perseverance of delight in the continued and indefatigable generation of knowledge, exceeds the short vehemence of any carnal pleasure.";
    // char s[] = "help";
    char s[] = "CDEFGHIJKLMNOPQRAB23456789+/STUVWXYZabcdefghijklmnopqrstuvwxyz01";
    for(int i = 0; i < 64; i ++){
        de_b64[s[i]] = i;
    }
    while (en_de());
    return 0;
}
