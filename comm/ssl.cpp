#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"

extern game *cur_game;

int ssl() {
    // сообщения функции
    const char *mess[] = {
            "Лёгкий слэм\n",
            "Агрессивный слэм\n",
            "Прыгнуть в центр круга перед рубиловом\n",
            "Поучаствовать в стенке на стенку\n"};

    int i;

    for (i = 0; i < 4; i++) {
        settextattr(WHITE);
        PRINTF("%i - ", i + 1);

        settextattr(YELLOW);
        PRINTF("%s", mess[i]);
    }

    return 0;
}
