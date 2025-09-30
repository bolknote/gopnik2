#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>

extern game *cur_game;

int _sv() {
    hero *main_hero = cur_game->main_hero;
    
    cur_game->enemy_desc = 1;

    s();

    cur_game->enemy_desc = 0;

    // Даём шокер игроку
    int inv_index = game::search_inv(main_hero, "Шокер");
    if (!main_hero->inv[inv_index].have) {
        main_hero->inv[inv_index].have = 1;
        cur_game->supple_inv_run_over(inv_index);
    }

    return 0;
}
