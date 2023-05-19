#include <iostream>

#include <fmt/format.h>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int stat() {
    // объект героя
    hero *main_hero;

    int i;

    main_hero = cur_game->main_hero;

    for (i = 0; i < cur_game->stn_amount; i++) {
        std::cout << WHITE << fmt::format("{:2} - ", i + 1);

        if (main_hero->station == i) {
            std::cout << BLACK;
        } else {
            if (cur_game->stn[i].avail) {
                std::cout << YELLOW;
            } else {
                std::cout << RED;
            }
        }

        std::cout << cur_game->stn[i].name << "\n";
    }

    std::cout << std::flush;

    return 0;
}
