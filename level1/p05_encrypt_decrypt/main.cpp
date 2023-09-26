#include "Crypter.h"
using namespace std;
char pswMap[]={'T','W','L','M'};

int main() {
    string str;
    cout<<"Enter a text to be encrypted:"<<endl;
    cin>>str;
    string en=Encrypt(str);
    cout<<en<<endl;
    cout<<"Decryption:"<<Decrypt(en)<<endl;
}