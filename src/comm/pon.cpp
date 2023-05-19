#include <iostream>

#include <fmt/format.h>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int pon() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const std::string mess[] = {
            "Твоя понтовость {}\n",
            "Если какие проблемы, то за тебя впрягутся\n",
            "За тебя никто не хочет впрягаться\n",
    };

    main_hero = cur_game->main_hero;

    std::cout << YELLOW << fmt::format(mess[0], main_hero->get_att());

    if (main_hero->get_att() > 0) {
        std::cout << GREEN << mess[1];
    } else {
        std::cout << RED << mess[2] << std::flush;
    }

    return 0;
}
