#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"

extern game *cur_game;

int _sv() {
    cur_game->enemy_desc = 1;

    s();

    cur_game->enemy_desc = 0;

    return 0;
}
