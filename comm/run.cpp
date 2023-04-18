#include <cstdlib>
#include <algorithm>

#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"

extern game *cur_game;

int run() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const char *mess[] = {
            "Э, ты куда, козёл!\n",
            "Э, ты куда, трусливый засранец!\n",
            "Тебе удалось съебаться.\n",
            "Тебе не удалось съебаться.\n",
            "Ты не можешь убежать на сломаной ноге..\n",
            "Братва спалила, что ты дал по съёбам, твоя понтовость в притоне понизилась до %iю\n",
            "Братва спалила, что ты пытался съебать, твоя понтовость в притоне понизилась до %i.\n",
            "Братва спалила, что ты дал по съёбам, твоя понтовость в притоне упала до нуля.\n",
            "Братва спалила, что ты пытался съебать, твоя понтовость в притоне упала до нуля.\n",
    };

    main_hero = cur_game->main_hero;

    if (main_hero->get_level_of_complexity() != 0) {
        return 0;
    }

    if (main_hero->broken_foot) {
        settextattr(YELLOW);
        PRINTF("%s", mess[4]);
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

            settextattr(YELLOW);
            PRINTF(mess[(att == 0 ? 8 : 6) - (int) run], att);

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
            settextattr(RED);
            PRINTF("%s", mess[GETRANDOM(-1, 1)]);
            settextattr(YELLOW);
            PRINTF("%s", mess[2]);

            cur_game->set_loc(0);
        } else {
            settextattr(YELLOW);
            PRINTF("%s", mess[3]);
            // не удалось сбежать, надо биться
            return k(true);
        }
    }

    return 0;
}
