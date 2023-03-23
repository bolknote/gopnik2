#include <cstdlib>

#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

int gamb() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const char *mess[] = {
            "Ты поднял бабла - %i руб\n",
            "Не фартануло - потерял %i руб\n",
    };

    main_hero = cur_game->main_hero;

    if (chance(1, 5)) {
        int money = getrandom(0, 100);
        main_hero->add_money(money);

        settextattr(GREEN);
        printf(mess[0], money);
    } else {
        int money = getrandom(0, 20);
        main_hero->add_money(-money);

        settextattr(RED);
        printf(mess[1], money);
    }

    return 0;
}
