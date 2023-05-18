#include <iostream>

#include <gopnik2/comm/comm.h>
#include <gopnik2/main.h>
#include <gopnik2/hero.h>
#include <gopnik2/game.h>
#include <gopnik2/utils.h>

extern game *cur_game;

int girl() {
    // объект героя
    hero *main_hero;

    // сообщения функции
    const std::string mess[] = {
            "У тебя нет девчонки\n",
            "Твоя девчонка живёт не в этом районе\n",
            "Ну не пойдёшь же ты, как последняя сволочь, без ничего?\n",
            "Ты расслабился, отдохнул и можешь снова творить свои гоповские дела\n",
    };

    main_hero = cur_game->main_hero;

    if (cur_game->open_girl == 0) {
        std::cout << RED << mess[0] << std::flush;

        return 0;
    }

    if (main_hero->station != (cur_game->open_girl - 1)) {
        std::cout << YELLOW << mess[1] << std::flush;

        return 0;
    }

    if (main_hero->inv[game::search_inv(main_hero, "Цветы и конфеты")].have) {
        main_hero->add_health(main_hero->get_max_health() - main_hero->get_health());
        main_hero->broken_foot = false;
        main_hero->broken_jaw = false;

        main_hero->inv[game::search_inv(main_hero, "Цветы и конфеты")].have--;

        std::cout << GREEN << mess[3] << std::flush;
    } else {
        std::cout << RED << mess[2] << std::flush;
    }

    return 0;
}
