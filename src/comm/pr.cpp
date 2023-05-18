#include <iostream>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int pr() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const std::string mess[] = {
            "Всякого распиздяя с улицы в притон не пустят. Отпинай сначала побольше мудаков\n",
            "Ты пришёл в притон\n",
            "-Тут на одного нашего один мудак наехал.\n",
            "-Ты пацан нормальный. Есть дело.\n",
            "-Мы тут знаем пару хороших мест\n",
            "Ты пришёл в притон - общагу ИТМО\nХотел было уже пройти, но тут тебя окрикнул охранник:\n",
            "-Э! А где пропуск? Если без пропуска, то давай пиздуй отсюда!\n",
            "Пропуска у тебя не было - тебе пришлось уйти, что б не возникло лишних проблем\n",
            "Ты пришёл в притон - общагу ИТМО\n",
            "-На нас по-крупному наехали\n"
    };

    main_hero = cur_game->main_hero;

    if (
            (main_hero->station != 0) &&
            (main_hero->station != 4)) {
        return 0;
    }

    if (
            (cur_game->get_open_pr() == 0) &&
            (main_hero->station == 0)) {
        std::cout << RED << mess[0] << std::flush;

        return 0;
    }

    if (main_hero->station) {
        if (main_hero->inv[game::search_inv(main_hero, "Пропуск в общагу")].have == 0) {
            std::cout
                << YELLOW << mess[5]
                << RED << mess[6]
                << YELLOW << mess[7]
                << std::flush;

            cur_game->set_open_pr(0);

            return 0;
        } else {
            cur_game->set_open_pr();
        }
    }

    std::cout << WHITE << (main_hero->station ? mess[8] : mess[1]);

    if (
            (cur_game->get_open_a() == 0) &&
            ((cur_game->get_open_trn() == 0) ||
             (cur_game->get_open_bmar() == 0))) {
        cur_game->set_open_a();
    }

    if (cur_game->get_open_a()) {
        std::cout << YELLOW << mess[4];
    }

    if (cur_game->get_open_hp()) {
        std::cout << YELLOW << mess[2];
    }

    if (cur_game->get_open_d()) {
        std::cout << YELLOW << mess[3];
    }

    if (
            (cur_game->open_raid) &&
            (main_hero->station == 4)) {
        std::cout << YELLOW << mess[9];
    }

    std::cout << std::flush;

    // переход к новой локации
    cur_game->set_loc(4);

    return 0;
}
