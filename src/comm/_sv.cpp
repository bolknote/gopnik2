#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>

extern game *cur_game;

int _sv() {
    cur_game->enemy_desc = 1;

    s();

    cur_game->enemy_desc = 0;

    return 0;
}
