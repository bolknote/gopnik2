#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"

extern game *cur_game;

int rep() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const char *mess[3] = {
            "Ты пришёл к ветеринару\n",
            "Док: Вали отсюда, ты здоров\n",
            "Ты пока не знаешь, где находиться больница\n"};

    int
    // индекс прайс-листа
    pl_index;

    main_hero = cur_game->main_hero;

    if (main_hero->station != 0) {
        return 0;
    }

    if (cur_game->open_rep == 0) {
        settextattr(RED);
        PRINTF("%s", mess[2]);

        return 0;
    }

    if (
            (main_hero->get_health() < main_hero->get_max_health()) ||
            (main_hero->broken_jaw) ||
            (main_hero->broken_foot)) {
        settextattr(WHITE);
        PRINTF("%s", mess[0]);

        // переход к новой локации
        cur_game->set_loc(2);

        pl_index = cur_game->search_pl(cur_game->active_loc);

        if (main_hero->get_health() == main_hero->get_max_health()) {
            cur_game->pl[pl_index].members[0].buy_phrase_print_mode = 0;
        } else {
            cur_game->pl[pl_index].members[0].buy_phrase_print_mode = 1;
        }

        if (
                (main_hero->broken_jaw == 0) &&
                (main_hero->broken_foot == 0)) {
            cur_game->pl[pl_index].members[1].buy_phrase_print_mode = 0;
        } else {
            cur_game->pl[pl_index].members[1].buy_phrase_print_mode = 1;
        }
    } else {
        settextattr(YELLOW);
        PRINTF("%s", mess[1]);

        // переход к новой локации
        cur_game->set_loc(0);
    }

    return 0;
}
