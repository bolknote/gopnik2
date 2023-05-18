#include <iostream>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int rep() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const std::string mess[] = {
            "Ты пришёл к ветеринару\n",
            "Док: Вали отсюда, ты здоров\n",
            "Ты пока не знаешь, где находиться больница\n"
    };

    int
    // индекс прайс-листа
    pl_index;

    main_hero = cur_game->main_hero;

    if (main_hero->station != 0) {
        return 0;
    }

    if (cur_game->open_rep == 0) {
        std::cout << RED << mess[2] << std::flush;

        return 0;
    }

    if (
            (main_hero->get_health() < main_hero->get_max_health()) ||
            (main_hero->broken_jaw) ||
            (main_hero->broken_foot)) {
        std::cout << WHITE << mess[0] << std::flush;

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
        std::cout << YELLOW << mess[1] << std::flush;

        // переход к новой локации
        cur_game->set_loc(0);
    }

    return 0;
}
