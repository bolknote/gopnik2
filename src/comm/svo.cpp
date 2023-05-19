#include <iostream>

#include <fmt/format.h>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int svo() {
    int i;

    for (i = 0; i < STR_AMOUNT; i++) {
        if (cur_game->str_enemy[i] == cur_game->enemy) {
            continue;
        }

        std::cout
            << RED
            << fmt::format(
                "{} {}",
                cur_game->str_enemy[i]->get_type(),
                cur_game->str_enemy[i]->get_level()
            )
            << fmt::format(
                " ({}/{})\n",
                cur_game->str_enemy[i]->get_health(),
                cur_game->str_enemy[i]->get_max_health()
            )
            << std::flush;
    }

    return 0;
}
