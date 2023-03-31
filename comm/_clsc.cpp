#include <stdio.h>

int _clsc() {
    printf("\033[2J\033[0;0H\033[00m");
    return 0;
}