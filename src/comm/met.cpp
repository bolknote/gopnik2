#include <iostream>

#include <fmt/format.h>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int met() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const std::string mess[] = {
            "Ты пришёл на станцию \"{}\"\n",
            "В метро пока идти нельзя - могут загрести\n",
    };

    main_hero = cur_game->main_hero;

    if (cur_game->stay_met > 0) {
        std::cout << YELLOW << mess[1] << std::flush;

        return 0;
    }

    std::cout << WHITE << fmt::format(mess[0], cur_game->stn[main_hero->station].name) << std::flush;

    // переход к новой локации
    cur_game->set_loc(9);

    return 0;
}
