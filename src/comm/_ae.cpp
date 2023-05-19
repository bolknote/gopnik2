#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>

extern game *cur_game;

int _ae() {
    hero *main_hero;
    main_hero = cur_game->main_hero;
    main_hero->add_exp(
            game::get_min_exp_for_level(main_hero->get_level() + 1) -
            game::get_min_exp_for_level(main_hero->get_level()));
    return 0;
}
