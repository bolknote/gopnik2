#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

int svo() {
    int i;

    for (i = 0; i < STR_AMOUNT; i++) {
        if (cur_game->str_enemy[i] == cur_game->enemy) {
            continue;
        }

        settextattr(RED);
        PRINTF(
                "%s %i",
                cur_game->str_enemy[i]->get_type(),
                cur_game->str_enemy[i]->get_level());
        PRINTF(
                " (%i/%i)\n",
                cur_game->str_enemy[i]->get_health(),
                cur_game->str_enemy[i]->get_max_health());
    }

    return 0;
}
