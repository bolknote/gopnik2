#include <iostream>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int p() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const std::string mess[] = {
            "Ты угостил пацанов пивом. Твоя понтовость повысилась на 5\n",
            "у тебя нету пива\n",
    };

    main_hero = cur_game->main_hero;

    if (main_hero->get_beer() > 0) {
        main_hero->sub_beer(1);
        main_hero->add_att(5);

        std::cout << GREEN << mess[0] << std::flush;
    } else {
        std::cout << RED << mess[1] << std::flush;
    }

    return 0;
}
