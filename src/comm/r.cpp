#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

#include <iostream>

extern game *cur_game;

int r() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const std::string mess[] = {
            "Ты занял у пацанов 4 рубля. Твоя понтовость понизилась на 10\n",
            "Ты не можешь занять денег, так как у тебя слишком низкая понтовость\n",
    };

    main_hero = cur_game->main_hero;

    if (main_hero->get_att() > 0) {
        main_hero->sub_att(10);
        main_hero->add_money(4);

        std::cout << YELLOW << mess[0] << std::flush;
    } else {
        std::cout << RED << mess[1] << std::flush;
    }

    return 0;
}
