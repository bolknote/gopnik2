#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>

extern game *cur_game;

int bb(
        // индекс прайс-листа
        int pl_index,
        // индекс элемента прайс-листа
        int plm_index,
        // флаг на покупку товара
        int *flag) {
    // объект героя
    hero *main_hero;

    main_hero = cur_game->main_hero;

    switch (plm_index) {
        case 0:
            main_hero->add_ciga(1);

            *flag = 1;
            break;

        case 7:
            main_hero->inv[game::search_inv(main_hero, cur_game->pl[pl_index].members[7].name)].have += 4;

            *flag = 1;
            break;
    }

    return 0;
}
