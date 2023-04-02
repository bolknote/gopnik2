#include <stdio.h>

int _clsc() {
    printf("\033[0;40m\033[H\033[J");
    return 0;
}
