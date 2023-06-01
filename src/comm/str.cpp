#include <iostream>

#include <fmt/format.h>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int str() {
    hero **str_hero;
    hero **str_enemy;

    // сообщения функции
    const std::string mess[] = {
            "Ваша басота\n",
            "Их басота\n",
            " (это ты)",
            "{} {} уровня",
            "Ты пришёл на пустырь. Пацаны с общаги уже были там.\n",
            "Через пару минут подошли ублюдки из наехавшей на вас банды. Один из них\nвышел вперёд и, разинув ебало, начал что-то вещать, как вдруг чувак\nиз вашей басоты оборвал его, дав с ноги в живот. Ты просёк, что простым\nбазаром тут уже не отделаешься, и что сейчас будет нехилый махач...\n",
    };

    int
            level,
            ht_index;

    int i, flag;

    if (
            (cur_game->open_str == 0) ||
            (cur_game->main_hero->station != 0)) {
        return 0;
    }

    std::cout << YELLOW << mess[4] << std::flush;

    get_key(false);

    std::cout << mess[5] << std::flush;

    get_key(false);

    str_hero = new hero *[STR_AMOUNT];
    str_enemy = new hero *[STR_AMOUNT];

    str_hero[0] = cur_game->main_hero;
    str_hero[0]->kick_count = 1;
    cur_game->str_hero_amount++;

    flag = 1;
    i = 1;

    while (i < STR_AMOUNT) {
        ht_index = getRandom(-1, 3);
        level = getRandom(str_hero[0]->get_level() + 5, str_hero[0]->get_level() + 15);

        // генерируем объект противника
        cur_game->gen_enemy_obj(ht_index, level, 0);
        cur_game->enemy_init = 0;

        cur_game->enemy->kick_count = 1;
        /*
            cur_game->enemy = tmp;
            sv ();
            get_key ();
        */
        if (flag) {
            str_hero[i] = cur_game->enemy;

            cur_game->str_hero_amount++;
        } else {
            str_enemy[i] = cur_game->enemy;

            cur_game->str_enemy_amount++;
        }

        i++;

        if (
                (flag) &&
                (i == STR_AMOUNT)) {
            flag = 0;
            i = 0;
        }
    }

    cur_game->str_hero = str_hero;
    cur_game->str_enemy = str_enemy;

    // вывод списка героев

    std::cout
        << WHITE << mess[0]
        << GREEN << fmt::format(mess[3], str_hero[0]->get_type(), str_hero[0]->get_level())
        << mess[2] << "\n";

    for (i = 1; i < STR_AMOUNT; i++) {
        std::cout
            << fmt::format(mess[3], str_hero[i]->get_type(), str_hero[i]->get_level())
            << "\n";
    }

    std::cout
        << WHITE << mess[1]
        << RED;

    for (i = 0; i < STR_AMOUNT; i++) {
        std::cout
            << fmt::format(mess[3], str_enemy[i]->get_type(), str_enemy[i]->get_level())
            << "\n";
    }

    cur_game->enemy = nullptr; // str_enemy [getRandom (-1, STR_AMOUNT - 1)];

    cur_game->open_str = 2;

    // переход к новой локации
    cur_game->set_loc(12);

    /*
      enemy->set_name ("Противник");
      enemy->add_exp (get_min_exp_for_level (level));
    */

    // сообщения функции
    // char *mess [] = {};

    return 0;
}
