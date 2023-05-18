#include <iostream>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int bmar() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const std::string mess[] = {
            "Ты пока не знаешь, где находятся барыги\n",
            "Ты пришёл к барыгам\n"};

    main_hero = cur_game->main_hero;

    if (
            (main_hero->station != 0) &&
            (main_hero->station != 3)) {
        return 0;
    }

    if (cur_game->get_open_bmar() == 0) {
        std::cout << RED << mess[0] << std::flush;

        return 0;
    }

    std::cout << WHITE << mess[1] << std::flush;

    // переход к новой локации
    cur_game->set_loc(5);

    return 0;
}
