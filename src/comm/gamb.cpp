#include <algorithm>
#include <iostream>

#include <fmt/format.h>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int gamb() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const std::string mess[] = {
            "Ты поднял бабла - {} руб\n",
            "Не фартануло - потерял {} руб\n",
            "Чтобы играть надо лавэ, натряси где-нибудь пять рэ.\n",
    };

    main_hero = cur_game->main_hero;

    if (main_hero->get_money() >= 5) {
        int luck = std::max(main_hero->get_luck() / 10, 2);

        if (CHANCE(1, 5 - luck)) {
            int money = getRandom(0, 100);
            main_hero->add_money(money);

            std::cout << GREEN << fmt::format(mess[0], money);
        } else {
            int money = getRandom(0, 25);
            main_hero->add_money(-money);

            std::cout << RED << fmt::format(mess[1], money);
        }
    } else {
        std::cout << YELLOW << mess[2];
    }

    std::cout << std::flush;

    return 0;
}
