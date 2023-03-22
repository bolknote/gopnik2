#include <stdio.h>

int _clsc() {
    //    clear();
    printf("\033[2J");
    printf("\033[0;0H");
    printf("\033[00m");
    return 0;
}