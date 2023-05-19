#include <iostream>

#include <fmt/format.h>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

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
    const std::string mess[] = {
            "Здоровье {}/{}\n",
            "Твои переломы залечены\n",
            "С этим у тебя всё в порядке\n",
    };

    main_hero = cur_game->main_hero;

    std::cout << GREEN;

    switch (plm_index) {
        case 0:
            if (main_hero->get_health() < main_hero->get_max_health()) {
                main_hero->add_health(5);

                std::cout << fmt::format(
                    mess[0], main_hero->get_health(), main_hero->get_max_health()
                );

                if (main_hero->get_max_health() == main_hero->get_health()) {
                    cur_game->pl[pl_index].members[plm_index].buy_phrase_print_mode = 0;
                }

                *flag = 1;
            } else {
                std::cout << mess[2];
            }
            break;

        case 1:
            if (
                    (main_hero->broken_jaw) ||
                    (main_hero->broken_foot)) {
                main_hero->broken_jaw = false;
                main_hero->broken_foot = false;

                std::cout << mess[1];

                cur_game->pl[pl_index].members[plm_index].buy_phrase_print_mode = 0;

                *flag = 1;
            } else {
                std::cout << mess[2];
            }
            break;
    }

    std::cout << std::flush;

    if (
            (main_hero->get_health() == main_hero->get_max_health()) &&
            (main_hero->broken_jaw == 0) &&
            (main_hero->broken_foot == 0)) {
        rep();
    }

    return 0;
}
