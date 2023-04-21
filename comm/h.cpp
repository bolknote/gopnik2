#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"

extern game *cur_game;

int h(
        // индекс прайс-листа
        int pl_index,
        // индекс элемента прайс-листа
        int plm_index,
        // флаг на покупку товара
        int *flag) {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const char *mess[] = {
            "Здоровье %i/%i\n",
            "Твои переломы залечены\n",
            "С этим у тебя всё в порядке\n"};

    main_hero = cur_game->main_hero;

    settextattr(GREEN);

    switch (plm_index) {
        case 0:
            if (main_hero->get_health() < main_hero->get_max_health()) {
                main_hero->add_health(5);

                PRINTF(mess[0], main_hero->get_health(), main_hero->get_max_health());

                if (main_hero->get_max_health() == main_hero->get_health()) {
                    cur_game->pl[pl_index].members[plm_index].buy_phrase_print_mode = 0;
                }

                *flag = 1;
            } else {
                PRINTF("%s", mess[2]);
            }
            break;

        case 1:
            if (
                    (main_hero->broken_jaw) ||
                    (main_hero->broken_foot)) {
                main_hero->broken_jaw = false;
                main_hero->broken_foot = false;

                PRINTF("%s", mess[1]);

                cur_game->pl[pl_index].members[plm_index].buy_phrase_print_mode = 0;

                *flag = 1;
            } else {
                PRINTF("%s", mess[2]);
            }
            break;
    }

    if (
            (main_hero->get_health() == main_hero->get_max_health()) &&
            (main_hero->broken_jaw == 0) &&
            (main_hero->broken_foot == 0)) {
        rep();
    }

    return 0;
}
