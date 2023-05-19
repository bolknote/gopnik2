#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>

extern game *cur_game;

int _w() {
    // переход к новой локации
    cur_game->set_loc(0);

    return 0;
}
