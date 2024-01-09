//
// Created by 14212 on 2023/9/25.
//
int Prime(int n){
    if(n==1)
        return 0;
    else
    {
        for(int i=2;i*i<=n;i++)
            if(n%i==0)
                return 0;
    }
    return 1;
}
