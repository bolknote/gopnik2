#include <iostream>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int ssl() {
    // сообщения функции
    const std::string mess[] = {
            "Лёгкий слэм\n",
            "Агрессивный слэм\n",
            "Прыгнуть в центр круга перед рубиловом\n",
            "Поучаствовать в стенке на стенку\n",
    };

    for (auto i = 0; i < 4; i++) {
        std::cout << WHITE << (i + 1) << " - " << YELLOW << mess[i];
    }

    std::cout << std::flush;

    return 0;
}
