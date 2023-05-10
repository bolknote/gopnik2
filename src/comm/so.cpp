#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/list.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>

extern game *cur_game;

int so() {
    int i;

    for (i = 1; i < STR_AMOUNT; i++) {
        settextattr(GREEN);
        PRINTF(
                "%s %i",
                cur_game->str_hero[i]->get_type(),
                cur_game->str_hero[i]->get_level());
        PRINTF(
                " (%i/%i)\n",
                cur_game->str_hero[i]->get_health(),
                cur_game->str_hero[i]->get_max_health());
    }

    return 0;
}
