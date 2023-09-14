#include <cstdio>
#include <iostream>
#include <string>
#define 🥓 string
#define 💀 0;
using namespace std;

using 👌=char;
using 🗡=int;
using 🍄=void;

👌 🗺️[] = "Taylor Swift";

🍄 🤔(🥓& 👻){
    🗡 😊=👻.length();
    for(int i=0;i<😊;i++){
        👻[i]^=🗺️[i%13];
    }
}
🍄 😊(🥓& 👻){
    🗡 😊=👻.length();
    for(int i=0;i<😊;i++){
        👻[i]^=🗺️[i%13];
    }
}

🗡 main() {
    cout<<"Enter a string:"<<endl;
    🥓 🌟;
    getline(cin,🌟);
    🤔(🌟);
    cout<<🌟<<endl;
    😊(🌟);
    cout<<🌟<<endl;
    return 💀;
}