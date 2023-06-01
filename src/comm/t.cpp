#include <iostream>

#include <fmt/format.h>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int t() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const std::string mess[] = {
            "Ты надыбал {} руб.\n",
            "Тебя запалили! Это {} {} уровня\n",
            "-Отдай кошелёк, урод!\n",
    };

    int
    // сгенерированное кол-во денег
    money,
    // индекс генерируемого типа героя
    ht_index;

    int
    // уровень генерируемого героя
    level,
    // кол-во событий для вероятности наезда
    events,
            flag;

    main_hero = cur_game->main_hero;

    events = main_hero->get_luck() + 1 - cur_game->num_t;
    flag = 0;

    if (events > 1) {
        if (CHANCE(1, events)) {
            flag = 1;
        } else {
            money = getRandom(0, 20 + 20 * main_hero->district);
            main_hero->add_money(money);

            std::cout << GREEN << fmt::format(mess[0], money);
        }

        cur_game->num_t++;
    } else {
        flag = 1;
        cur_game->num_t = 0;
    }

    if (flag) {
        cur_game->set_stay_mar(-1);

        do {
            level = cur_game->gen_enemy(&ht_index);
        } while (level == -1);

        level += 2;

        std::cout
            << YELLOW << fmt::format(mess[1], cur_game->ht[ht_index].type, level)
            << RED << mess[2];

        cur_game->gen_enemy_obj(ht_index, level);

        // переход к новой локации
        cur_game->set_loc(1);
    }

    std::cout << std::flush;

    return 0;
}
