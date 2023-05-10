#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/list.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>

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
