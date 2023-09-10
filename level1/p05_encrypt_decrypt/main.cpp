#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

char KeyMap[] = "Taylor Swift";

void Encrypt(string& str){
    int length=str.length();
    for(int i=0;i<length;i++){
        str[i]^=KeyMap[i%13];
    }
}
void Decrypt(string& str){
    int length=str.length();
    for(int i=0;i<length;i++){
        str[i]^=KeyMap[i%13];
    }
}

int main() {
    cout<<"Enter a string:"<<endl;
    string data;
    getline(cin,data);
    Encrypt(data);
    cout<<data<<endl;
    Decrypt(data);
    cout<<data<<endl;
    return 0;
}