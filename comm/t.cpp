#include <cstdlib>

#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"

extern game *cur_game;

int t() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const char *mess[3] = {
            "Ты надыбал %i руб.\n",
            "Тебя запалили! Это %s %i уровня\n",
            "-Отдай кошелёк, урод!\n"};

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
            money = GETRANDOM(0, 20 + 20 * main_hero->district);
            main_hero->add_money(money);

            settextattr(GREEN);
            PRINTF(mess[0], money);
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

        settextattr(YELLOW);
        PRINTF(mess[1], cur_game->ht[ht_index].type, level);

        settextattr(RED);
        PRINTF("%s", mess[2]);

        cur_game->gen_enemy_obj(ht_index, level);

        // переход к новой локации
        cur_game->set_loc(1);
    }

    return 0;
}
