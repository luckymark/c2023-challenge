#include <stdio.h>
#include <windows.h>


int main() {

    char str[2 * (2 + 1) * (2 + 1)] = {'\0'};
    printf("%d ", str[1]);

    return 0;
}
