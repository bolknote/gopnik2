#include <cstdlib>
#include <algorithm>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/list.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>

extern game *cur_game;

int gamb() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const char *mess[] = {
            "Ты поднял бабла - %i руб\n",
            "Не фартануло - потерял %i руб\n",
            "Чтобы играть надо лавэ, натряси где-нибудь пять рэ.\n",
    };

    main_hero = cur_game->main_hero;

    if (main_hero->get_money() >= 5) {
        int luck = std::max(main_hero->get_luck() / 10, 2);

        if (CHANCE(1, 5 - luck)) {
            int money = GETRANDOM(0, 100);
            main_hero->add_money(money);

            settextattr(GREEN);
            PRINTF(mess[0], money);
        } else {
            int money = GETRANDOM(0, 25);
            main_hero->add_money(-money);

            settextattr(RED);
            PRINTF(mess[1], money);
        }
    } else {
        settextattr(YELLOW);
        PRINTF("%s", mess[2]);
    }

    return 0;
}
