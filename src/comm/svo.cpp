#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/list.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>

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
