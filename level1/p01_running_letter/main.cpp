#include <cstdio>
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

void Refresh(string str, int sleepTime= 5){
    cout << str << endl;
    Sleep(sleepTime);
    system("cls");
}

int main() {
    setbuf(stdout,NULL);

    string str="t";
    string space="";
    for(;;) {
        HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO info;
        GetConsoleScreenBufferInfo(outputHandle, &info);

        for (int i = 0; i < info.dwSize.X; i++) {
            Refresh(space + str);
            space += " ";
        }

        for (int i = info.dwSize.X; i > 0; i--) {
            for (int n = 0; n < i; n++)
                space += " ";
            Refresh(space + str);
            space = "";
        }
    }
    return 0;
}