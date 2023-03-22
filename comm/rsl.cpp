#include <cstdlib>

#include "comm.h"
#include "../main.h"
#include "../list.h"
#include "../hero.h"
#include "../game.h"
#include "../utils.h"

extern game *cur_game;

int rsl(
        int index) {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const char *mess[9] = {
            "Ты слэмишься",
            "С диким рёвом ты кидаешься в толпу, расталкивая всех плечами\n",
            "В диком угаре тебе кто-то заезжает по челюсти\n",
            "Размахивая кулаками ты скачешь среди обезумевших людей\n",
            "Перед самым месивом ты прыгаешь в центр круга и, едва\nудержавшись под напором тел, продолжаешь меситься со всеми\n",
            "На этот раз твой заход был неудачным - тебя свалила толпа, сломав тебе ногу\n",
            "От мощного столкновения тебя беспорядочно проносит по всему партеру\n",
            "Столкновение было не самым лучшим и ты сломал всё, что только можно\n",
            "Тебя вынесло из слэма\n"};

    int
    // количество прибавляемой ловкость
    smart;

    main_hero = cur_game->main_hero;

    if (
            (index < 0) ||
            (index >= 4)) {
        return 0;
    }

    smart = 0;

    switch (index) {
        // лёгкий слэм
        case 0:
            if (chance(2, 3)) {
                settextattr(YELLOW);
                printf("%s", mess[1]);

                smart = 1;
            } else {
                settextattr(RED);
                printf("%s", mess[2]);

                main_hero->broken_jaw = 1;
            }
            break;

            // агрессивный слэм
        case 1:
            if (chance(1, 3)) {
                settextattr(YELLOW);
                printf("%s", mess[3]);

                smart = 2;
            } else {
                settextattr(RED);
                printf("%s", mess[2]);

                main_hero->broken_jaw = 1;
            }
            break;

            // прыжок в центр круга
        case 2:
            if (chance(2, 5)) {
                settextattr(YELLOW);
                printf("%s", mess[4]);

                smart = 3;
            } else {
                settextattr(RED);
                printf("%s", mess[5]);

                main_hero->broken_foot = 1;
            }
            break;

            // стенка на стенку
        case 3:
            if (chance(1, 5)) {
                settextattr(YELLOW);
                printf("%s", mess[6]);

                smart = 4;
            } else {
                settextattr(RED);
                printf("%s", mess[7]);

                main_hero->broken_foot = 1;
                main_hero->broken_jaw = 1;
            }
            break;
    }

    if (smart) {
        if (main_hero->add_smart()) {
            settextattr(WHITE);
            printf("%s", mess[8]);

            // переход к новой локации
            cur_game->set_loc(8);
        } else {
            settextattr(GREEN);
            printf("%s", mess[0]);

            settextattr(BLUE);
            main_hero->add_smart(smart);

            printf("%s", "\n");
        }
    } else {
        sl();
    }

    return 0;
}
