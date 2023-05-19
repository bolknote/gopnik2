#include <iostream>

#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int bar(
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
            "Да не охота жрать\n",
            "Да чё-то не охота пить\n",
            "Ты не можешь есть из-за сломанной челюсти\n",
            "Ты не можешь пить из-за сломанной челюсти\n",
    };

    int
    // добавляемое здоровье
    health;

    main_hero = cur_game->main_hero;

    switch (plm_index) {
        case 0:
            health = 6;
            break;

        case 1:
            health = 15;
            break;

        case 2:
            health = 20;
            break;

        case 3:
            health = (int) main_hero->get_max_health() / 2;

            // делаем героя бухим
            cur_game->stay_mh = 10;
            main_hero->drunk = true;
            break;
    }

    if (
            (main_hero->get_health() < main_hero->get_max_health()) &&
            (!main_hero->broken_jaw)) {
        main_hero->add_health(health);

        *flag = 1;
    } else {
        if (main_hero->broken_jaw) {
            std::cout << RED << (plm_index ? mess[3] : mess[2]) << std::flush;
        } else {
            std::cout << GREEN << (plm_index ? mess[1] : mess[0]) << std::flush;
        }
    }

    // доп. условия
    if (
            (main_hero->get_health() == main_hero->get_max_health()) ||
            (main_hero->broken_jaw)) {
        cur_game->pl[pl_index].members[0].buy_phrase_print_mode = 0;
        cur_game->pl[pl_index].members[1].buy_phrase_print_mode = 0;
        cur_game->pl[pl_index].members[2].buy_phrase_print_mode = 0;
        cur_game->pl[pl_index].members[3].buy_phrase_print_mode = 0;
    }

    return 0;
}
