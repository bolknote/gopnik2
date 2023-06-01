#include <algorithm>
#include <iostream>

#include <fmt/format.h>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int run() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const std::string mess[] = {
            "Э, ты куда, козёл!\n",
            "Э, ты куда, трусливый засранец!\n",
            "Тебе удалось съебаться.\n",
            "Тебе не удалось съебаться.\n",
            "Ты не можешь убежать на сломаной ноге..\n",
            "Братва спалила, что ты дал по съёбам, твоя понтовость в притоне понизилась до {}ю\n",
            "Братва спалила, что ты пытался съебать, твоя понтовость в притоне понизилась до {}.\n",
            "Братва спалила, что ты дал по съёбам, твоя понтовость в притоне упала до нуля.\n",
            "Братва спалила, что ты пытался съебать, твоя понтовость в притоне упала до нуля.\n",
    };

    main_hero = cur_game->main_hero;

    if (main_hero->get_level_of_complexity() != 0) {
        return 0;
    }

    if (main_hero->broken_foot) {
        std::cout << YELLOW << mess[4];
    } else {
        // шансы убежать
        bool run = CHANCE(50 + std::max(main_hero->get_luck(), 25), 100);

        // если уже дрались, надо запретить соваться на локацию
        if (run) {
            // борьба на рынке
            if (cur_game->get_stay_mar() == -1) {
                cur_game->set_stay_mar(20);
            }

            // борьба в клубе
            if (cur_game->get_stay_kl() == -1) {
                cur_game->set_stay_kl(40);
            }

            // борьба в метро
            if (cur_game->stay_met == -1) {
                cur_game->stay_met = 10;
            }
        }

        // это у нас стрелка?
        if (cur_game->open_str != 0) {
            int att = std::min(main_hero->get_att() - 20, 0);
            main_hero->set_att(att);

            std::cout << YELLOW << fmt::format(mess[(att == 0 ? 8 : 6) - (int) run], att);

            // убежал со стрелки
            if (run) {
                cur_game->open_str = 0;
                cur_game->stay_str = 0;

                if (cur_game->str_enemy_amount) {
                    delete[] cur_game->str_hero;
                    cur_game->str_enemy_amount = 0;
                }

                if (cur_game->str_enemy_amount) {
                    delete[] cur_game->str_enemy;
                    cur_game->str_hero_amount = 0;
                }

                cur_game->set_loc(0);
            }
        }

        if (run) {
            std::cout
                << RED << mess[getRandom(-1, 1)]
                << YELLOW << mess[2];

            cur_game->set_loc(0);
        } else {
            std::cout << YELLOW << mess[3];
            // не удалось сбежать, надо биться
            return k(true);
        }
    }

    std::cout << std::flush;

    return 0;
}
