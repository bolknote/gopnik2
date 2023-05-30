#include <iostream>
#include <iomanip>

#include <cstring>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int i() {
    // старый видеоатрибут
    Colors old_attr;
    // длина команды, состоящей из
    // максимального количества символов
    size_t max_len;
    // длина текущей команды

    cur_game->supple_loc_run_over();

    max_len = strlen(cur_game->loc[cur_game->active_loc].command[0]);

    for (int i = 1; i < cur_game->loc[cur_game->active_loc].comm_amount; i++) {
        if (cur_game->loc[cur_game->active_loc].command_active[i]) {
            auto len = strlen(cur_game->loc[cur_game->active_loc].command[i]);

            if (len > max_len) {
                max_len = len;
            }
        }
    }

    max_len++;

    old_attr = RESET;

    for (int i = 0; i < cur_game->loc[cur_game->active_loc].comm_amount; i++) {
        if (cur_game->loc[cur_game->active_loc].command_active[i]) {
            std::cout << YELLOW << cur_game->loc[cur_game->active_loc].command[i];

            auto len = max_len - strlen(cur_game->loc[cur_game->active_loc].command[i]);
            std::cout
                << std::setw((int) len) << " "
                << WHITE << cur_game->loc[cur_game->active_loc].command_desc[i] << "\n";
        }
    }

    std::cout << old_attr << std::flush;

    return 0;
}
