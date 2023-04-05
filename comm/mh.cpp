#include <cstring>

#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

int mh() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const char *mess[6] = {
            "Пиво прибавляет %iз. Здоровье: %i/%i. Осталось %d бутылок пива\n",
            "Пива нету\n",
            "Чувак, у тебя и так дохрена здоровья\n",
            "Ты не можешь пить из-за сломанной челюсти\n",
            "Ты выпил слишком много пива за раз и опьянел. Лв -1\n",
            "Куда те ещё пить? И так пьяный!\n"};

    int
    // кол-во пива, которое должно быть использовано
    d;

    int
            i,
            j;

    main_hero = cur_game->main_hero;

    if (main_hero->get_health() < main_hero->get_max_health()) {
        if (main_hero->broken_jaw) {
            settextattr(RED);
            PRINTF("%s", mess[3]);
        } else {
            if (main_hero->get_beer() > 0) {
                if (cur_game->stay_mh > 0) {
                    settextattr(YELLOW);
                    PRINTF("%s", mess[5]);
                } else {
                    if (strcmp(cur_game->active_cmd, "mh") == 0) {
                        d = main_hero->get_beer();
                    } else {
                        d = 1;
                    }

                    if ((d * 5) >= (main_hero->get_max_health() - main_hero->get_health())) {
                        i = main_hero->get_max_health() - main_hero->get_health();
                        j = i;

                        while ((j % 5) != 0) {
                            j++;
                        }

                        main_hero->sub_beer(d = j / 5);
                        main_hero->add_health(main_hero->get_max_health() - main_hero->get_health());
                    } else {
                        i = d * 5;

                        main_hero->sub_beer(d);
                        main_hero->add_health(i);
                    }

                    settextattr(GREEN);
                    PRINTF(mess[0], i, main_hero->get_health(), main_hero->get_max_health(), main_hero->get_beer());

                    // больше лимита опьянения
                    if (d >= ((main_hero->district + 1))) {
                        cur_game->stay_mh = 10;
                        main_hero->drunk = 1;

                        settextattr(YELLOW);
                        PRINTF("%s", mess[4]);
                    }
                }
            } else {
                settextattr(RED);
                PRINTF("%s", mess[1]);
            }
        }
    } else {
        settextattr(YELLOW);
        PRINTF("%s", mess[2]);
    }

    return 0;
}
