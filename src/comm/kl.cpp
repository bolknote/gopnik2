#include <cstring>
#include <iostream>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int kl() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const std::string mess[] = {
            "Ты не знаешь, где находится клуб\n",
            "Ты пришёл в клуб\n",
            "В клуб лучше пока не соваться - может отпинать охрана\n",
            "Проходка в клуб стоит 20 руб. Хочешь раскошелится? (y/n)\n",
            "Чувак, у тебя слишком мало бабла для такого понтового клуба\n",
            "Ты пришёл в клуб \"Пятница\"\n",
            "Ты пришёл в клуб \"Порт\"\n",
            "Надпись на стене: \"Под забой и ширнуться в кайф\"\n",
            "Ты чё! Ты же нефор! Неужели ты попрёшься в клуб, где включают одну попсу?!\n",
    };

    int
    // индекс прайс-листа
    pl_index;

    main_hero = cur_game->main_hero;

    if (
            (main_hero->station != 0) &&
            (main_hero->station != 2)) {
        return 0;
    }

    if (cur_game->get_open_kl() == 0) {
        std::cout << RED << mess[0] << std::flush;

        return 0;
    }

    if (cur_game->get_stay_kl() > 0) {
        std::cout << YELLOW << mess[2] << std::flush;

        return 0;
    }

    if (
            (main_hero->station != 0) &&
            (strcmp(main_hero->get_type(), HeroTypes::NEFOR) != 0)) {
        if (main_hero->get_money() >= 20) {
            std::cout << YELLOW << mess[3] << std::flush;

            if (!game::wait_answ()) {
                return 0;
            } else {
                main_hero->sub_money(20);
            }
        } else {
            std::cout << RED << mess[4] << std::flush;

            return 0;
        }
    }

    if (strcmp(main_hero->get_type(), HeroTypes::NEFOR) == 0) {
        if (main_hero->station) {
            std::cout
                << WHITE << mess[6]
                << BLUE << mess[7]
                << std::flush;
        } else {
            std::cout << YELLOW << mess[8] << std::flush;

            return 0;
        }
    } else {
        std::cout << WHITE << (main_hero->station ? mess[5] : mess[1]) << std::flush;
    }

    // переход к новой локации
    cur_game->set_loc(8);

    // доп. условия

    pl_index = cur_game->search_pl(cur_game->active_loc);

    if (
            (main_hero->get_health() == main_hero->get_max_health()) ||
            (main_hero->broken_jaw)) {
        cur_game->pl[pl_index].members[0].buy_phrase_print_mode = 0;
        cur_game->pl[pl_index].members[1].buy_phrase_print_mode = 0;
        cur_game->pl[pl_index].members[2].buy_phrase_print_mode = 0;
        cur_game->pl[pl_index].members[3].buy_phrase_print_mode = 0;
    } else {
        cur_game->pl[pl_index].members[0].buy_phrase_print_mode = 1;
        cur_game->pl[pl_index].members[1].buy_phrase_print_mode = 1;
        cur_game->pl[pl_index].members[2].buy_phrase_print_mode = 1;
        cur_game->pl[pl_index].members[3].buy_phrase_print_mode = 1;
    }

    return 0;
}
