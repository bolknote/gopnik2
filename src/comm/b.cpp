#include <iostream>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int b(
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
            "Чё-то не охота жрать\n",
            "Ты не можешь есть из-за сломанной челюсти\n"};

    main_hero = cur_game->main_hero;

    if (main_hero->station != 0) {
        return 0;
    }

    switch (plm_index) {
        case 0:
            if (
                    (main_hero->get_health() < main_hero->get_max_health()) &&
                    (!main_hero->broken_jaw)) {
                main_hero->add_health(3);

                *flag = 1;
            } else {
                if (main_hero->broken_jaw) {
                    std::cout << RED << mess[1] << std::flush;
                } else {
                    std::cout << GREEN << mess[0] << std::flush;
                }
            }
            break;

        case 1:
            main_hero->add_beer(1);

            *flag = 1;
            break;
    }

    // доп. условия

    if (
            (main_hero->get_health() == main_hero->get_max_health()) ||
            (main_hero->broken_jaw)) {
        cur_game->pl[pl_index].members[0].buy_phrase_print_mode = 0;
    }

    return 0;
}
