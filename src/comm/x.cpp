#include <iostream>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int x() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const std::string mess[] = {
            "Барыги тебе дали денег за хлам\n",
            "У тебя нет хлама\n",
    };

    float
    // коэффициент
    k;

    main_hero = cur_game->main_hero;

    k = (main_hero->station) ? (0.8) : (0.5);

    if (main_hero->get_stuff() > 0) {
        main_hero->add_money((int) ((float) main_hero->get_stuff() * k) + 1);

        main_hero->sub_stuff(main_hero->get_stuff());

        std::cout << GREEN << mess[0] << std::flush;
    } else {
        std::cout << RED << mess[1] << std::flush;
    }

    return 0;
}
