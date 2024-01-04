#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <string>

#define _RAND_MAX 120
#define _RAND_MIN 1

using namespace std;

string s;

void encrypt(int key)
{
    for(int i=0;i<s.size();++i)
    {
        s[i]+=key;
        s[i]=~s[i];
        s[i]+=key;
    }
    printf("Encrypt:");
    cout<<s<<endl;
    return;
}
void decrypt(int key)
{
    for(int i=0;i<s.size();++i)
    {
        s[i]-=key;
        s[i]=~s[i];
        s[i]-=key;
    }
    printf("Decrypt:");
    cout<<s<<endl;
    return;
}
int main()
{
    int key;
    srand(time(0));
    key=rand()%(_RAND_MAX-_RAND_MIN+1)+_RAND_MIN;
    cin>>s;
    encrypt(key);
    decrypt(key);
    return 0;
}