#include <cstring>
#include <cstdlib>

#include "pltl.h"
#include "../main.h"
#include "../hero.h"
#include "../list.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

int pltl2(
        // индекс сюжетной линии
        int pltl_index) {
    // объект героя
    hero *main_hero;
    // объект врага
    //  hero *enemy;

    const char *mess[7] = {
            "Бродя по окрестностям с самыми грязными намерениями...\r\n",
            "Ты увидел, как злой маньяк развращал клёвую чиксу.\r\n",
            "Хочешь вмешаться? (y/n)\r\n",
            "Ну и правильно! Нечего лезть не в своё дело! Ты пошёл дальше...\r\n",
            "Ты: Хули ты творишь, урод!\r\n",
            "Маньяк: Не твоё дело, мудак!\r\n",
            "Ты подсобил девчонке - она этого не забудет. Теперь можешь у неё вписываться\r\n"};

    int
    // индекс генерируемого типа героя
    ht_index,
    // индекс инвентаря
    inv_index;

    int
    // уровень генерируемого героя
    level;

    // возвращаемое значение
    int ret = 0;

    main_hero = cur_game->main_hero;

    if (cur_game->open_girl) {
        cur_game->pltl[pltl_index].active = -1;
    }

    switch (cur_game->pltl[pltl_index].active) {
        case 0:
            if (
                    (strcmp(cur_game->active_cmd, "w") != 0) ||
                    (cur_game->active_loc != 0) ||
                    (cur_game->num_empty_w < 3)) {
                return 0;
            }

            if (chance(1, 50)) {
                settextattr(WHITE);
                PRINTF("%s", mess[0]);

                get_key();

                PRINTF("%s", mess[1]);

                get_key();

                settextattr(YELLOW);
                PRINTF("%s", mess[2]);

                if (game::wait_answ()) {
                    settextattr(GREEN);
                    PRINTF("%s", mess[4]);

                    get_key();

                    settextattr(RED);
                    PRINTF("%s", mess[5]);

                    get_key();

                    ht_index = cur_game->search_ht("Маньяк");
                    level = getrandom(main_hero->get_level() + 1, main_hero->get_level() + 5);

                    cur_game->gen_enemy_obj(ht_index, level);

                    inv_index = game::search_inv(main_hero, "Тесак");

                    game::add_inventory(
                            cur_game->enemy,
                            main_hero->inv[inv_index].name,
                            main_hero->inv[inv_index].district,
                            main_hero->inv[inv_index].events,
                            1,
                            main_hero->inv[inv_index].force,
                            main_hero->inv[inv_index].smart,
                            main_hero->inv[inv_index].vita,
                            main_hero->inv[inv_index].luck,
                            main_hero->inv[inv_index].armo,
                            main_hero->inv[inv_index].loss);

                    // переход к новой локации
                    cur_game->set_loc(1);

                    cur_game->pltl[pltl_index].active++;
                    cur_game->active_pltl = pltl_index;

                    ret = 2;
                } else {
                    settextattr(WHITE);
                    PRINTF("%s", mess[3]);
                }
            }
            break;

        case 1:
            if (
                    (!cur_game->enemy_init) &&
                    (main_hero->get_health() > 0)) {
                cur_game->open_girl = main_hero->station + 1;
                cur_game->pltl[pltl_index].active = -1;

                settextattr(YELLOW);
                PRINTF("%s", mess[6]);
            }
            break;
    }

    return ret;
}
