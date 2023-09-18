#include <stdio.h>
int main(){
    system("chcp 65001");
    int w=1,q=2,i=4,j=0,n[25]={2,3,5,7,11,13,17,19,23,29,
                           31,37,41,43,47,53,59,61,67,71,
                           73,79,83,89,97};
    for (i = 4; i < 101; i=i+2) {
        for (j = 0; j <= 24; j++) {
            int c = i - n[j];
            for (int k = 0; k <= 24; k++) {
                if(c==n[k])
                {
                    q=1;
                    break;
                }

            }
            if(q==1)
                break;

            }
        if(j==25)
        {
            q=0;
            break;
        }

    }
    if(q==1)
        printf("哥德巴赫猜想100以内正确。\n");
    if(q==0)
        printf("哥德巴赫猜想100以内错误。\n");
    return 0;
}