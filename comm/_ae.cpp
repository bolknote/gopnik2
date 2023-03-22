#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"

extern game *cur_game;

int _ae() {
    hero *main_hero;
    main_hero = cur_game->main_hero;
    main_hero->add_exp(
            cur_game->get_min_exp_for_level(main_hero->get_level() + 1) -
            cur_game->get_min_exp_for_level(main_hero->get_level()));
    return 0;
}
