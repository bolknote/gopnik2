#include <iostream>

#include <comm/comm.h>
#include <main.h>
#include <list.h>
#include <hero.h>
#include <game.h>

extern game *cur_game;

int lar() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const std::string mess[] = {
            "Чё брать будешь?\n",
    };

    main_hero = cur_game->main_hero;

    if (main_hero->station != 5) {
        return 0;
    }

    std::cout << WHITE << mess[0] << std::flush;

    // переход к новой локации
    cur_game->set_loc(14);

    return 0;
}
