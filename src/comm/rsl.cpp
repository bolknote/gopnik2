#include <iostream>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int rsl(
        int index) {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const std::string mess[] = {
            "Ты слэмишься",
            "С диким рёвом ты кидаешься в толпу, расталкивая всех плечами\n",
            "В диком угаре тебе кто-то заезжает по челюсти\n",
            "Размахивая кулаками ты скачешь среди обезумевших людей\n",
            "Перед самым месивом ты прыгаешь в центр круга и, едва\nудержавшись под напором тел, продолжаешь меситься со всеми\n",
            "На этот раз твой заход был неудачным - тебя свалила толпа, сломав тебе ногу\n",
            "От мощного столкновения тебя беспорядочно проносит по всему партеру\n",
            "Столкновение было не самым лучшим и ты сломал всё, что только можно\n",
            "Тебя вынесло из слэма\n"
    };

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
            if (CHANCE(2, 3)) {
                std::cout << YELLOW << mess[1];

                smart = 1;
            } else {
                std::cout << RED << mess[2];

                main_hero->broken_jaw = true;
            }
            break;

            // агрессивный слэм
        case 1:
            if (CHANCE(1, 3)) {
                std::cout << YELLOW << mess[3];

                smart = 2;
            } else {
                std::cout << RED << mess[2];

                main_hero->broken_jaw = true;
            }
            break;

            // прыжок в центр круга
        case 2:
            if (CHANCE(2, 5)) {
                std::cout << YELLOW << mess[4];

                smart = 3;
            } else {
                std::cout << RED << mess[5];

                main_hero->broken_foot = true;
            }
            break;

            // стенка на стенку
        case 3:
            if (CHANCE(1, 5)) {
                std::cout << YELLOW << mess[6];

                smart = 4;
            } else {
                std::cout << RED << mess[7];

                main_hero->broken_foot = true;
                main_hero->broken_jaw = true;
            }
            break;
    }

    if (smart) {
        if (main_hero->add_smart()) {
            std::cout << WHITE << mess[8];

            // переход к новой локации
            cur_game->set_loc(8);
        } else {
            std::cout << GREEN << mess[0] << BLUE;
            main_hero->add_smart(smart);

            std::cout << "\n";
        }
    } else {
        sl();
    }

    std::cout << std::flush;

    return 0;
}
